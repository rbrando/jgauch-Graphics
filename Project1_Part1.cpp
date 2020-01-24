/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int max_x = 0;
int max_y = 0;
int height;
int width;

// Draw function options
int LINE_WIDTH = 3;
string COLOR = "BLACK";

vector<int> getInput()
{
    string input;
    int count_points;
    int index;
    int max_point = 0;
    
    //Array to store plot points
    vector<int> points;

    
    printf("Please enter the file that contains your data point.\n");
    //getline(cin,input);
    
    input = "2 3 5 8 13 21 34 42 42 42";
    
    //Parse input string
    istringstream iss(input);

    index = 0;
    int new_point;

    do {
        iss >> new_point;
        
        points.insert(points.end(),new_point);
        
        //Used for validation:
        cout << "The vector elements are: "; 
        for (auto it = points.begin(); it != points.end(); ++it) 
            cout << *it << " ";         
        cout << "\n";
        
        max_point = max(max_point, points[index]); 
        
        index++;
        
    } while(iss);
    
    cout << "- Max Point: " << max_point << "\n";
    
    return points;
}

void column_chart()
{
    printf("Column");
}

void point_chart()
{
    printf("Point");
}

void line_chart()
{
    printf("Line");
}

void area_chart()
{
    printf("Area");
}

void base_chart()
{
    //Y-Axis
    cout << "draw_line " << LINE_WIDTH << " 0 0 0 " << height << endl;
    
    //X-Axis
    cout << "draw_line " << LINE_WIDTH << "0 0 " << width << " 0" << endl;
    
}

int printMenu(vector<int> points)
{
    int chart_type;
    
    printf("Please choose which type of graph you wish to plot:\n");
    printf("1) Column Chart\n");
    printf("2) Point Chart\n");
    printf("3) Line Chart\n");
    printf("4) Area Chart\n");
    printf(":");
    
    cin >> chart_type;
    
    base_chart();
    
    switch (chart_type)
    {
        case 1 :
            column_chart();
            break;
            
        case 2 : 
            point_chart();
            break;
        
        case 3 :
            line_chart();
            break;
            
        case 4 : 
            area_chart();
            break;
        
        default : 
            printf("Invalid option try again.\n");
    }
    return chart_type;
}


int main()
{
    vector<int> input = getInput();
    int chart_type = printMenu(input);

    cout << chart_type << "\n";

    return 0;
}











