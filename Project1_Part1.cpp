/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int max_x = 0;
int max_y = 0;
float max_point;

// Draw function options
string LINE_WIDTH = "1";
string COLOR = "BLACK";
int height = 500;
int width = 500;
int index;

void writeFile(string logIt)
{
  ofstream output;
  output.open("chart.txt", ios::app);
  output << logIt;
  output.close();
}

float convertNum(float before)
{
  if (before == max_point)
    return 0.90;
  else if (before == 0)
    return -0.88;
  else
  {
    //Since our origin point would be at (-0.9,-0.9) we can use this to find the ratio of points
    //The ratio is found by assuming the max_point is the top of the graph.
    float after = -0.89 + ((before/max_point)*1.8);
    cout << "After: " << after << endl;
    return after;
  }
}

void clearFile()
{
  ofstream output;
  output.open("chart.txt");
  output.close();
}

vector<float> getInput()
{
    string input;
    string filename;
    max_point = 0;

    //Array to store plot points
    vector<float> points;


    printf("Please enter the file that contains your data point.\n:");
    //cin >> filename;
    filename = "input.txt";

    ifstream inputFile;
    inputFile.open(filename.c_str());
    getline(inputFile,input);

    //Parse input string
    istringstream iss(input);

    index = 0;
    int new_point;

    do {
        iss >> new_point;

        points.insert(points.end(),new_point);

        //Used for validation:
        //cout << "The vector elements are: ";
        //for (vector<float>::iterator it = points.begin(); it != points.end(); ++it)
        //    cout << *it << " ";
        //    cout << "\n";

        max_point = max(max_point, points[index]);

        index++;

    } while(iss);

    index --;

    return points;
}

void column_chart()
{
    printf("Column");
}

void point_chart(vector<float> points)
{
    //Chart origin at x:-0.9 y:-0.9
    //Chart ends at x:0.9, y:0.9
    string point_size = "7";
    ostringstream x_string;
    ostringstream y_string;

    writeFile("set_color 1 0.5 0.5\n");

    float xtick = -0.88;
    float tick_dist = (0.9 - (-0.88))/index;
    printf("Point\n\n");
    for (vector<float>::iterator it = points.begin(); it != points.end(); ++it)
    {
        xtick = xtick + tick_dist;
        x_string << xtick;
        y_string << convertNum(*it);

        writeFile("draw_point " + point_size + " " + x_string.str() + " " + y_string.str() + "\n");
        x_string.str("");
        y_string.str("");
    }
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
    float xtick = -0.88;
    float tick_dist = (0.9 - (-0.88))/index;
    float ytick = -0.88;
    float ytick_dist = 0.178;

    ostringstream y_string;
    ostringstream x_string;
    //Set color to white
    writeFile("set_color 1 1 1\n");
    writeFile("draw_line " + LINE_WIDTH + " -0.88 0.9 -0.88 -0.9\n");
    writeFile("draw_line " + LINE_WIDTH + " -0.9 -0.88 0.9 -0.88\n");

    //Y-Axis
    writeFile("draw_line " + LINE_WIDTH + " -0.88 0.9 -0.88 -0.9\n");

    //X-Axis
    writeFile("draw_line " + LINE_WIDTH + " -0.9 -0.88 0.9 -0.88\n");

    //Draw tick marks
    for(int i = 0; i < index; i++)
    {
	     xtick = xtick + tick_dist;
       x_string << xtick;
	     writeFile("draw_line " + LINE_WIDTH + " " + x_string.str() +  " -0.88 " + x_string.str() + " -0.905\n");
       x_string.str("");
    }

    //Draw lies across the x-axis
    for (int i = 0; i < 10; i++)
    {
	     ytick = ytick + ytick_dist;
       y_string << ytick;
	     writeFile("draw_line " + LINE_WIDTH + " -0.9 " + y_string.str() + " 0.9 " + y_string.str() + "\n");
       y_string.str("");
    }

}

int printMenu(vector<float> points)
{
    int chart_type;

    printf("Please choose which type of graph you wish to plot:\n");
    printf("1) Column Chart\n");
    printf("2) Point Chart\n");
    printf("3) Line Chart\n");
    printf("4) Area Chart\n");
    printf(":");

    // cin >> chart_type;
    cout << "\n\n";
    chart_type = 2;

    base_chart();

    switch (chart_type)
    {
        case 1 :
            column_chart();
            break;

        case 2 :
            point_chart(points);
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
    clearFile();
    vector<float> input = getInput();
    int chart_type = printMenu(input);

    cout << chart_type << "\n";

    return 0;
}
