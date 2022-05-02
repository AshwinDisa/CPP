#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  float goals[11][3] = {{0,8,1}, {0,7,1}, {1,7,1}, {1,0,1}, {2,0,1}, {2,6,1}, {2,5,1}, {3,5,1}, {3,0,1}, {4,0,1}, {4,4,1}};
  for(int i=0;i<11;i++){

  goal.target_pose.pose.position.x = goals[i][0];
  goal.target_pose.pose.position.y = goals[i][1];
  goal.target_pose.pose.orientation.w = goals[i][2];


  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  ros::Duration(1.0).sleep();
}

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

  return 0;
}