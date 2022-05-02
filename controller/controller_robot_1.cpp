#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <iostream>
#include <cmath>

using namespace std;

ros::Publisher vel_pub;
ros::Subscriber pos_sub;
ros::Subscriber scan_sub;

double x, y, roll, pitch, yaw;
double goal_pose_x, goal_pose_y;
double range_array[360];
double obstacleAngle = 0.0;
bool flag = 0;
double new_ang_goal;
double prev_ang_goal;
double next_ang_goal;

double get_distance(double x1, double y1, double x2, double y2);
float get_orientation(int goal_pose_y, int y, int goal_pose_x, int x);

double obstacleDistance(double range_array[]){

	double obstacle_distance;
	double range_min = 100;
		// cout << "In" << endl;

	if (range_array[0] < range_min){
		obstacleAngle = 0;
		range_min = range_array[0];
		// cout << "range array 0 " << range_array[0] << endl;
	}
	else if (range_array[30] < range_min){
		obstacleAngle = 15;  // 15 deg
		range_min = range_array[15];
		// cout << "range array 30 " << range_array[30] << endl;		
	}
	else if (range_array[345] < range_min){
		obstacleAngle = -15;  //  -15 deg
		range_min = range_array[345];
		// cout << "range array -30" << range_array[330] << endl;
	}

	// cout << "range min = " << range_min << endl;
	// cout << "obstacleAngle = " << obstacleAngle << endl;
	return range_min;
}

void deviate(double range_array[], double prev_ang_goal){

	geometry_msgs::Twist velocity_message;
	ros::Rate loop_rate(30);

	if (range_array[340] > range_array[20]){
		cout << range_array[359] << " " << range_array[345] << endl;
		if ((range_array[359]*2) < range_array[345]){
			cout << "in1" << endl;
			new_ang_goal = yaw - 50*3.142/180;
			next_ang_goal = yaw + 50*3.142/180;

			flag = 1;
		}
		else{
		new_ang_goal = yaw - 75*3.142/180;
		next_ang_goal = yaw + 75*3.142/180;

		flag = 1;
		}
	}
	else{
		cout << range_array[1] << " " << range_array[15] << endl;
		if ((range_array[1]*2) < range_array[15]){
			cout << "in2" << endl;
			new_ang_goal = yaw + 50*3.142/180;
			next_ang_goal = yaw - 50*3.142/180;
			// prev_ang_goal = yaw - new_ang_goal;

			flag = 0;
		}
		else{
			new_ang_goal = yaw + 75*3.142/180;
			next_ang_goal = yaw - 75*3.142/180;
			flag= 0;
		}
	}

	cout << "Deviating" << endl;

	while(abs(new_ang_goal - yaw) > 0.2){
		// cout << "new ang goal " << abs(new_ang_goal - yaw) << endl;
		velocity_message.linear.x = 0.2;
		// cout << "Deviating " << endl;
		if (flag == 1){
			velocity_message.angular.z = - 0.4 * abs(new_ang_goal - yaw);
			// cout << "right" << endl;
		}
		else{
			velocity_message.angular.z = 0.4 * abs(new_ang_goal - yaw);
			// cout << "left" << endl;
		}
		// cout << "yaw " << yaw << endl;
		vel_pub.publish(velocity_message);	

		ros::spinOnce();
		loop_rate.sleep();
	}

	cout << "Deviation complete, correcting" << endl;
	

	while(abs(prev_ang_goal - yaw) > 0.1){
		// cout << "new ang goal " << abs(new_ang_goal - yaw) << endl;
		velocity_message.linear.x = 0.2;
		// cout << "in non deviate " << endl;

		if (flag == 1){
			velocity_message.angular.z = 0.8 * abs(prev_ang_goal - yaw);
			// cout << "right" << endl;
		}
		else{
			velocity_message.angular.z = -0.8 * abs(prev_ang_goal - yaw);
			// cout << "left" << endl;
		}
		// cout << "yaw " << yaw << endl;
		vel_pub.publish(velocity_message);	

		ros::spinOnce();
		loop_rate.sleep();

	}
	cout << "Correction completed, going straight" << range_array[60] << endl;

	if (flag == 1){

		cout << "In RIGHT straight" << endl;			

		while(range_array[60] < 3){

			// cout << "In right straight" << endl;

			velocity_message.linear.x = 0.2;
			velocity_message.angular.z = 0.0;
			vel_pub.publish(velocity_message);
			
			ros::spinOnce();
			loop_rate.sleep();
		}
	}
	else{

		cout << "In LEFT straight" << range_array[280] << endl;

		while(range_array[300] < 3){

			cout << "In left straight" << endl;

			velocity_message.linear.x = 0.2;
			velocity_message.angular.z = 0.0;
			vel_pub.publish(velocity_message);
			
			ros::spinOnce();
			loop_rate.sleep();
		}	
	}

	cout << "Straight conpleted, returning to path" << endl;

	while(abs(next_ang_goal - yaw) > 0.2){
		// cout << "new ang goal " << abs(new_ang_goal - yaw) << endl;
		velocity_message.linear.x = 0.2;
		// cout << "in non deviate " << endl;

		if (flag == 1){
			velocity_message.angular.z = 0.4 * abs(next_ang_goal - yaw);
			// cout << "right" << endl;
		}
		else{
			velocity_message.angular.z = -0.4 * abs(next_ang_goal - yaw);
			// cout << "left" << endl;
		}
		// cout << "yaw " << yaw << endl;
		vel_pub.publish(velocity_message);	

		ros::spinOnce();
		loop_rate.sleep();

	}

	cout << "obstacle avoided successfully" << endl;



}

void go_to_goal(double goal_pose_x, double goal_pose_y, double distance_error)
{
	geometry_msgs::Twist velocity_message;
	double Kp1 = 0.2;
	double Kp2 = 3;
	ros::Rate loop_rate(10);
	double distance = get_distance(x, y, goal_pose_x, goal_pose_y);

	// cout << "distance = " << distance << endl;
	while (distance > 0.3)
	{
		double obsDist = obstacleDistance(range_array);

		if (obsDist < 1){
			velocity_message.linear.x = 0.0;
			velocity_message.angular.z = 0.0;
			vel_pub.publish(velocity_message);
			// cout << "Stopping" << endl;
			prev_ang_goal = yaw;
			// cout << "prev_ang_goal " << prev_ang_goal << endl;  
			deviate(range_array, prev_ang_goal);
		}

		distance = get_distance(x, y, goal_pose_x, goal_pose_y);
		velocity_message.linear.x = 0.3;
		velocity_message.angular.z = Kp2 * (atan2(goal_pose_y - y, goal_pose_x - x) - yaw); 
		vel_pub.publish(velocity_message);
		ros::spinOnce();
		loop_rate.sleep();	
	}
	while(distance > distance_error && distance < 0.3){
		distance = get_distance(x, y, goal_pose_x, goal_pose_y);
		// cout << "distance = " << distance << endl;

		velocity_message.linear.x = Kp1 * distance;
		
		velocity_message.angular.z = Kp2 * (atan2(goal_pose_y - y, goal_pose_x - x) - yaw);
		vel_pub.publish(velocity_message);
		ros::spinOnce();
		loop_rate.sleep(); 
	
	}
		vel_pub.publish(velocity_message);
		ros::spinOnce();
		loop_rate.sleep();

	// cout << goal_pose_x << "," << goal_pose_y << endl;
	velocity_message.linear.x = 0.0;
	velocity_message.angular.z = 0.0;
	vel_pub.publish(velocity_message);
}


void orientation(int goal_pose_x, int goal_pose_y, double angle_error){

	geometry_msgs::Twist velocity_message;
	double current_angle = 0.0;
	ros::Rate loop_rate(30);
	
	while (ros::ok()){
		velocity_message.angular.z = 0.4 * (atan2(goal_pose_y - y, goal_pose_x - x) - yaw);
		vel_pub.publish(velocity_message);	

		ros::spinOnce();
		loop_rate.sleep();

		if (abs(atan2(goal_pose_y - y, goal_pose_x - x) - yaw) < 0.1)
			break;
	}
	velocity_message.angular.z = 0.0;
	vel_pub.publish(velocity_message);
}

float get_orientation(int goal_pose_y, int y, int goal_pose_x, int x){
	// cout << x << "," << y << "," << yaw;
	return (atan2(goal_pose_y - y, goal_pose_x - x) - yaw);
}


double get_distance(double x1, double y1, double x2, double y2){
	// cout << x1 << "," << y1 << endl;
	return sqrt(pow((x2 - x1),2) + pow((y2 - y1), 2));
}

void poseCallback(const nav_msgs::Odometry::ConstPtr & pose_message)
{
	x = pose_message->pose.pose.position.x;
	y = pose_message->pose.pose.position.y;
	tf::Quaternion q(
        pose_message->pose.pose.orientation.x,
        pose_message->pose.pose.orientation.y,
        pose_message->pose.pose.orientation.z,
        pose_message->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    m.getRPY(roll, pitch, yaw);
    // cout << yaw << endl;
}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr & scan_message){
	
	for(int i=0; i<=360; i++){
		range_array[i] = scan_message->ranges[i];
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "controller_robot_1");
	ros::NodeHandle nh;
	vel_pub = nh.advertise<geometry_msgs::Twist>("/robot1/cmd_vel", 100);
	pos_sub = nh.subscribe("/robot1/odom", 10, poseCallback);
	scan_sub = nh.subscribe("/robot1/scan", 10, scanCallback);

	// float goals[9][3] = {{0,4,1}, {1,4,1}, {1,0,1}, {2,0,1}, {2,4,1}, {3,4,1}, {3,0,1}, {4,0,1}, {4,4,1}};
	float goals[1][3] = {{0,4,1}};
	for(int i=0;i<1;i++){

		goal_pose_x = goals[i][0];
		goal_pose_y = goals[i][1];

		cout << goal_pose_x << "," << goal_pose_y << endl;

		orientation(goal_pose_x, goal_pose_y, 0.03);

		cout << "Orintation done" << endl;

		go_to_goal(goal_pose_x, goal_pose_y, 0.15);		

		cout << "go_to_goal done" << endl;
	}

	ros::Rate rate(10);
	rate.sleep();
	ros::spin();
	return 0;
}
