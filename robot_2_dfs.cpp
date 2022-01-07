#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

const int m = 20;
const int n = 20;
int a = 1;

// check if current cell is valid or not
bool validator(int i, int j, int m, int n){

	return (i>=0 && i<m && j>=0 && j<n);
}

void write_to_csv_robot_2(int i, int j){
    ofstream to_csv;
    to_csv.open("robot_2_dfs.csv", std::ios::app);
    // to_csv << (i*50)+20 << "," << (j*50)+20 << endl;
    to_csv << i << "," << j << endl;
    to_csv.close();

}

// dfs algorithm
void dfs(int i, int j, int grid[m][n], int m, int n){

	int dx;
	int dy;

	// for visualization 
	// cout << (i*60)+30 << "," << (j*60)+30 << endl;
    // write_to_csv_robot_2(i, j);
	

	grid[i][j] = 1;

    
    // RIGHT
    if(j+1<20 && grid[i][j+1] != 1 && i>=0 && j>=0){
        // cout << "RIGHT" << endl;
        write_to_csv_robot_2(i, j);
        dfs(i, j+1, grid, m, n);
    }

    // DOWN
    if(i-1 >= 0 && grid[i-1][j] != 1 && i>=0 && j>=0){
        // cout << "DOWN" << endl;
        write_to_csv_robot_2(i, j);
        dfs(i-1, j, grid, m, n);
    }

    // LEFT
    if(j-1>=0 && grid[i][j-1] != 1 && i>=0 && j>=0){
        // cout << "LEFT" << endl;
        write_to_csv_robot_2(i, j);
        dfs(i, j-1, grid, m, n);
    }
    // UP
    if(i+1 < 20 && grid[i+1][j] != 1 && i>=0 && j>=0){
        // cout << "UP" << endl;
        write_to_csv_robot_2(i, j);
        dfs(i+1, j, grid, m, n);
    }

    // cout << "NO WAY" << endl;
    write_to_csv_robot_2(i, j);
}

int main(int argc, char **argv  ){

    int x;
    int y;
    int grid[m][n];
    vector<vector<string>> content_1;
    vector<string> row_1;
    string line_1, word_1;
    vector<vector<string>> content_3;
    vector<string> row_3;
    string line_3, word_3;

    cout << "Enter X " << endl;
    cin >> x;
    cout << "Enter Y " << endl;
    cin >> y;

    cout << "Unvisited cells - 0 " << endl;
    cout << "Obstacle/visited cells -1 " << endl;
    cout << endl;

    // mark cells as unvisited

    for(int i=0;i<m;i++){

        for(int j=0;j<n;j++){
            grid[i][j] = 0;

        }
    }

    fstream file_1 ("robot_1_vor.csv", ios::in);
    if(file_1.is_open())
    {
        while(getline(file_1, line_1))
        {
            row_1.clear();
 
            stringstream str(line_1);
 
            while(getline(str, word_1, ','))
                row_1.push_back(word_1);
            content_1.push_back(row_1);
        }
    }
    else
        cout<<"Could not open the file\n";

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){

            for(int k=0; k<content_1.size(); k++){

                // cout << content[k][0] << " " << content[k][1] << endl;
                if(i == stoi(content_1[k][0]) && j == stoi(content_1[k][1])){
                    grid[i][j] = 1;
                    // cout << i << " " << j << endl;
                }
                // else
                //    grid[i][j] = 0;
            }
        }
    }

    fstream file_3 ("robot_3_vor.csv", ios::in);
    if(file_3.is_open())
    {
        while(getline(file_3, line_3))
        {
            row_3.clear();
 
            stringstream str(line_3);
 
            while(getline(str, word_3, ','))
                row_3.push_back(word_3);
            content_3.push_back(row_3);
        }
    }
    else
        cout<<"Could not open the file\n";

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){

            for(int k=0; k<content_3.size(); k++){

                // cout << content[k][0] << " " << content[k][1] << endl;
                if(i == stoi(content_3[k][0]) && j == stoi(content_3[k][1])){
                    grid[i][j] = 1;
                    // cout << i << " " << j << endl;
                }
                // else
                //    grid[i][j] = 0;
            }
        }
    }

    // obstacles
    for(int i=11;i<16;i++){

        for(int j=4;j<8;j++){
            grid[i][j] = 1; 
        }
        cout << endl;
    }
    cout << endl;

    for(int i=3;i<7;i++){

        for(int j=14;j<19;j++){
            grid[i][j] = 1; 
        }
        cout << endl;
    }
    cout << endl;

    for(int i=0;i<m;i++){

        for(int j=0;j<n;j++){
            cout << grid[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;
     
    dfs(x, y, grid, m, n);

    for(int i=0;i<m;i++){

        for(int j=0;j<n;j++){
            cout << grid[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;


    return 0;
}