/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// void init()
// {
//   glClearColor(0.0, 0.0, 0.0, 1.0);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
// }

void set_color(float red, float green, float blue)
{
    //cout << "Set Color - R: " << red << " G: " << green << " B: " << blue << endl;
    cout << "glColor3f(" << red << "," << green << "," << blue << ");\n";
}

void draw_line(int size, int x1, int y1, int x2, int y2)
{
    //cout << "Line - Size: " << line_size << " (x1,y1)=(" << point_x1 << "," << point_y1 << ") - (x2,y2)=(" << point_x2 << "," << point_y2 << ")" << endl; 
    cout << "glLineWidth(" << size <<");\n";
    cout << "glBegin(GL_LINES);\n";
    cout << "glVertex3f(" << x1 << "," << y1 << ", 0);\n";
    cout << "glVertex3f(" << x2 << "," << y2 << ", 0);\n";
    cout << "glEnd();\n";
}

void draw_point(int size, int x, int y)
{
    cout << "glPointSize(size);\n";
    cout << "glBegin(GL_POINTS);\n";
    cout << "glVertex3f(x, y, 0);\n";
    cout << "glEnd();\n";
}

void draw_polygon(vector<int> coordinates)
{
    cout << "glBegin(GL_POLYGON);" << endl;
    
    int j = 1;
    for (vector<int>::iterator it = coordinates.begin(); it != coordinates.end(); it++) 
    {
        if (j % 2 == 1)
            cout << "glVertex3f(" << *it << ",";         
        else
            cout << *it << ",0);" << endl;
        j++;
    }
    cout << "glEnd();" << endl;

}

int getInput()
{
    //Variables for set_color:
    float red;
    float blue;
    float green;
    
    //Variables for draw_line/draw_point:
    int line_size;
    int point_x1;
    int point_x2;
    int point_y1;
    int point_y2;
    
    //variables for draw_polygon:
    int num_sides;
    vector<int> coordinates;

    

    //General Purpose variables
    string input;
    int count_points;
    int max_point = 0;

    
    printf("Please enter the file that contains your data point.\n");
    //getline(cin,input);
    
    input = "set_color 1 1 1 \ndraw_line 3 0 0 0 500 \ndraw_line 3 0 0 500 0\ndraw_point 10 10 100\ndraw_polygon 3 1 2 3 4 5 6";
    
    //Parse input string
    istringstream iss(input);
    string new_command;
    int index = 0;
    
    do {
         iss >> new_command;

         if (new_command.compare("set_color") == 0) 
         {
            iss >> red;
            iss >> green;
            iss >> blue;
            set_color(red,green,blue);
            index++;
         }
         
         else if (new_command.compare("draw_line") == 0) 
         {
            iss >> line_size;
            iss >> point_x1;
            iss >> point_y1;
            iss >> point_x2;
            iss >> point_y2;
            draw_line(line_size, point_x1, point_y1, point_x2, point_y2);
            index++;
         }
         
         else if (new_command.compare("draw_point") == 0) 
         {
            iss >> line_size;
            iss >> point_x1;
            iss >> point_y1;
            draw_point(line_size, point_x1, point_y1);
            index++;
         }
         
         else if (new_command.compare("draw_polygon") == 0) 
         {
            iss >> num_sides;
            int new_coordinates;
            for (int i=0; i < (2*num_sides);i++)
            {   
                new_coordinates = 0;
                iss >> new_coordinates;
                coordinates.insert(coordinates.end(),new_coordinates);
            }
            index++;
            draw_polygon(coordinates);
         }
         
         else
            cout << "Invalid command given" << endl;
            
        
    } while(iss);
    
    cout << "index: " << index << endl;
    
    return 0;
}

int main()
{
    getInput();    

    return 0;
}






