#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int m = 20;
const int n = 20;
int a = 1;
float dist_1 = 0.0;
float dist_2 = 0.0;
float dist_3 = 0.0;

float distance(int x1, int y1, int x2, int y2){

	return sqrt(pow((x2-x1),2) + pow((y2-y1),2));

}

void write_to_csv_robot_1(int i, int j){

	ofstream to_csv;
	to_csv.open("robot_1_vor.csv", ios::app);
	// to_csv << (i*60)+30 << "," << (j*60)+30 << endl;
	to_csv << i << "," << j << endl;
	to_csv.close();

}

void write_to_csv_robot_2(int i, int j){
	ofstream to_csv;
	to_csv.open("robot_2_vor.csv", std::ios::app);
	// to_csv << (i*60)+30 << "," << (j*60)+30 << endl;
	to_csv << i << "," << j << endl;
	to_csv.close();

}

void write_to_csv_robot_3(int i, int j){
	ofstream to_csv;
	to_csv.open("robot_3_vor.csv", std::ios::app);
	// to_csv << (i*60)+30 << "," << (j*60)+30 << endl;
	to_csv << i << "," << j << endl;
	to_csv.close();
}

void voronoi(int x, int y, int u, int v, int o, int p, int grid[m][n], int m, int n){

	for (int i=0; i<m; i++){

		for (int j=0; j<n;j++){
		
			dist_1 = distance(x, y, i, j);
			dist_2 = distance(u, v, i, j);
			dist_3 = distance(o, p, i, j);

			if (dist_1 < dist_2 && dist_1 < dist_3)
			    write_to_csv_robot_1(i, j);

			else if (dist_2 < dist_3)
				write_to_csv_robot_2(i, j);

			else
				write_to_csv_robot_3(i, j);				
		}
	}

}

int main(){

    int x;
    int y;
    int u;
    int v;
    int o;
    int p;
    int grid[m][n];

    cout << "Enter X for robot 1 " << endl;
    cin >> x;
    cout << "Enter Y for robot 1" << endl;
    cin >> y;

    cout << "Enter X for robot 2 " << endl;
    cin >> u;
    cout << "Enter Y for robot 2" << endl;
    cin >> v;

    cout << "Enter X for robot 3 " << endl;
    cin >> o;
    cout << "Enter Y for robot 3" << endl;
    cin >> p;

    voronoi(x, y, u, v, o, p, grid, m, n);
}