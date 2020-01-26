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
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void set_color(float red, float green, float blue)
{
    //cout << "Set Color - R: " << red << " G: " << green << " B: " << blue << endl;
    glColor3f(red, green, blue);
}

void draw_line(int size, float x1, float y1, float x2, float y2)
{
    //cout << "Line - Size: " << line_size << " (x1,y1)=(" << point_x1 << "," << point_y1 << ") - (x2,y2)=(" << point_x2 << "," << point_y2 << ")" << endl;
    glLineWidth(size);
    glBegin(GL_LINES);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glEnd();
}

void draw_point(int size, float x, float y)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(x, y, 0);
    glEnd();
}

void draw_polygon(vector<float> coordinates)
{
    glBegin(GL_POLYGON);

    int j = 1;
    float x;


    for (vector<float>::iterator it = coordinates.begin(); it != coordinates.end(); it++)
    {
        if (j % 2 == 1)
            x = *it;
        else
        {
          glVertex3f(x,*it,0);
        }
        j++;
    }
    glEnd();

}

void getInput()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Variables for set_color:
    float red;
    float blue;
    float green;

    //Variables for draw_line/draw_point:
    float line_size;
    float point_x1;
    float point_x2;
    float point_y1;
    float point_y2;

    //variables for draw_polygon:
    int num_sides;
    //vector<float> coordinates;



    //General Purpose variables
    string input;
    string filename;

    filename = "chart.txt";

    ifstream inputFile;
    inputFile.open(filename.c_str());
//    getline(inputFile,input);

  do {
    vector<float> coordinates;
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
            float new_coordinates = 0;
            for (int i=0; i < (2*num_sides);i++)
            {
                new_coordinates = 0;
                iss >> new_coordinates;
                coordinates.insert(coordinates.end(),new_coordinates);
            }
            draw_polygon(coordinates);
            index++;
         }


    } while(iss);
  } while(getline(inputFile,input));

    glFlush();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Chart");
   glutDisplayFunc(getInput);
   init();
   glutMainLoop();

   return 0;
}
