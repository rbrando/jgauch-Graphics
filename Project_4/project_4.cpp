//---------------------------------------
// Program: image.cpp
// Purpose: Read and print pixels values.
// Author:  John Gauch
// Date:    February 2020
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <fstream>
#include <iostream>
#include <sstream>
#include "shading.cpp"
using namespace std;

//Taken from Gauch source code surface4.cpp
// Surface variables
#define SIZE 499
#define STEP 0.1
#define XMIN -1.0
#define XMAX 1.0
#define YMIN -1.0
#define YMAX 1.0
#define ZMIN -0.5
#define ZMAX 0.5
#define COLORMIN 0.0
#define COLORMAX 1.0
int MODE = 1;

// X-Y-Z Points
float Px[SIZE + 1][SIZE + 1];
float Py[SIZE + 1][SIZE + 1];
float Pz[SIZE + 1][SIZE + 1];

//Surface Normals
float Nx[SIZE + 1][SIZE + 1];
float Ny[SIZE + 1][SIZE + 1];
float Nz[SIZE + 1][SIZE + 1];

// RGB Values
float R[SIZE + 1][SIZE + 1];
float G[SIZE + 1][SIZE + 1];
float B[SIZE + 1][SIZE + 1];

int xangle = 0;
int yangle = 0;
int zangle = 270;

void read_file_color()
{
  string line;
  ifstream infile("penny-image.txt");

  while(getline(infile,line))
  {
    istringstream iss(line);
    int rgb_val;
    while (iss >> rgb_val)
    // Initialize (x,y,z) coordinates of surface
    for (int i = 0; i <= SIZE; i++)
      for (int j = 0; j <= SIZE; j++)
      {
        //Set RGB Value
        iss >> rgb_val;
        B[i][j] = rgb_val;
        iss >> rgb_val;
        G[i][j] = rgb_val;
        iss >> rgb_val;
        R[i][j] = rgb_val;
      }

  }
}

void read_file_depth()
{
  string line;
  ifstream infile("penny-depth.txt");

  while(getline(infile,line))
  {
    istringstream iss(line);
    float depth;
    while (iss >> depth)
    // Initialize (x,y,z) coordinates of surface
    for (int i = 0; i <= SIZE; i++)
      for (int j = 0; j <= SIZE; j++)
      {
        Px[i][j] = XMIN + i * (XMAX - XMIN) / SIZE;

        Py[i][j] = YMIN + j * (YMAX - YMIN) / SIZE;

        // Set depth
        iss >> depth;
        Pz[i][j] = ZMIN + (depth * 0.1) * (ZMAX - ZMIN) / SIZE;
      }

  }
}

//---------------------------------------
// Initialize surface normals
// Taken from Gauch/surface4.cpp
//---------------------------------------
void init_normals()
{
   // Initialize surface normals
   for (int i=0; i<=SIZE; i++)
   for (int j=0; j<=SIZE; j++)
   {
      // Get tangents S and T
      float Sx = (i<SIZE) ? Px[i+1][j] - Px[i][j] : Px[i][j] - Px[i-1][j];
      float Sy = (i<SIZE) ? Py[i+1][j] - Py[i][j] : Py[i][j] - Py[i-1][j];
      float Sz = (i<SIZE) ? Pz[i+1][j] - Pz[i][j] : Pz[i][j] - Pz[i-1][j];
      float Tx = (j<SIZE) ? Px[i][j+1] - Px[i][j] : Px[i][j] - Px[i][j-1];
      float Ty = (j<SIZE) ? Py[i][j+1] - Py[i][j] : Py[i][j] - Py[i][j-1];
      float Tz = (j<SIZE) ? Pz[i][j+1] - Pz[i][j] : Pz[i][j] - Pz[i][j-1];

      // Calculate N = S cross T
      Nx[i][j] = Sy*Tz - Sz*Ty;
      Ny[i][j] = Sz*Tx - Sx*Tz;
      Nz[i][j] = Sx*Ty - Sy*Tx;
      float length = sqrt(Nx[i][j]*Nx[i][j]
                   + Ny[i][j]*Ny[i][j]
                   + Nz[i][j]*Nz[i][j]);
      if (length > 0)
      {
         Nx[i][j] /= length;
         Ny[i][j] /= length;
         Nz[i][j] /= length;
      }
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glEnable(GL_DEPTH_TEST);

   read_file_depth();
   read_file_color();
   init_normals();
}

float calculate_avg(float first, float second)
{

  float sum = (first + second);
  return (sum/2.0);
}

void poly_display()
{
  init();
  glShadeModel(GL_FLAT);
  glDisable(GL_LIGHTING);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(xangle, 1.0, 0.0, 0.0);
  glRotatef(yangle, 0.0, 1.0, 0.0);
  glRotatef(zangle, 0.0, 0.0, 1.0);

  // Draw the surface
  int i, j;
  float red, green, blue;
  for (i = 0; i < SIZE; i++)
     for (j = 0; j < SIZE; j++)
     {
       red = 0;
       green = 0;
       blue = 0;

       if (MODE == 1)
          glBegin(GL_LINE_LOOP);
       else
          glBegin(GL_POLYGON);


       red = (R[i][j] + R[i+1][j] + R[i+1][j+1] + R[i][j+1])/4;
       green = (G[i][j] + G[i+1][j] + G[i+1][j+1] + G[i][j+1])/4;
       blue = (B[i][j] + B[i+1][j] + B[i+1][j+1] + B[i][j+1])/4;

       red = red/255;
       green = green/255;
       blue =  blue/255;



       glColor3f(red, green, blue);
       glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
       glColor3f(red, green, blue);
       glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);
       glColor3f(red, green, blue);
       glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);
       glColor3f(red, green, blue);
       glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
       glEnd();
     }
  glFlush();
}


void phong_display()
{
  // // Initialize smooth shading
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);

  init_light(GL_LIGHT0, -1, 1, 1, 0.964, 0.592, 0.219);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(xangle, 1.0, 0.0, 0.0);
  glRotatef(yangle, 0.0, 1.0, 0.0);
  glRotatef(zangle, 0.0, 0.0, 1.0);

  // Initialize material properties
  init_material(Ka, Kd, Ks, 100 * Kp, 0.5, 0.5, 0.8);

  // Draw the surface
  int i, j;
  float red, green, blue;
  for (i = 0; i < SIZE; i++)
     for (j = 0; j < SIZE; j++)
     {
       red = 0;
       green = 0;
       blue = 0;
       glBegin(GL_POLYGON);

       red = (R[i][j] + R[i+1][j] + R[i+1][j+1] + R[i][j+1])/4;
       green = (G[i][j] + G[i+1][j] + G[i+1][j+1] + G[i][j+1])/4;
       blue = (B[i][j] + B[i+1][j] + B[i+1][j+1] + B[i][j+1])/4;

       red = red/255;
       green = green/255;
       blue =  blue/255;



       glNormal3f(Nx[i][j], Ny[i][j], Nz[i][j]);
       glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);

       glNormal3f(Nx[i + 1][j], Ny[i + 1][j], Nz[i + 1][j]);
       glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);

       glNormal3f(Nx[i + 1][j + 1], Ny[i + 1][j + 1], Nz[i + 1][j + 1]);
       glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);

       glNormal3f(Nx[i][j + 1], Ny[i][j + 1], Nz[i][j + 1]);
       glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
       glEnd();
     }
  glFlush();
}

void display()
{
  init();
  if (MODE == 3)
    phong_display();
  else
    poly_display();
}

//---------------------------------------
// Keyboard callback for OpenGL
// Taken from Gauch\office2.cpp
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
      // Update angles
      if (key == 'x')
         xangle -= 5;
      else if (key == 'y')
         yangle -= 5;
      else if (key == 'X')
         xangle += 5;
      else if (key == 'Y')
         yangle += 5;
      else if (key == 'Z')
         zangle += 5;
      else if (key == 'z')
         zangle -= 5;

      // Handle material properties
      if (key == 'a')
        Ka -= STEP;
      if (key == 'd')
        Kd -= STEP;
      if (key == 's')
        Ks -= STEP;
      if (key == 'p')
        Kp -= STEP;
      if (key == 'A')
        Ka += STEP;
      if (key == 'D')
        Kd += STEP;
      if (key == 'S')
        Ks += STEP;
      if (key == 'P')
        Kp += STEP;

      //Change Mode
      if (key == '1')
        MODE = 1;
      if (key == '2')
        MODE = 2;
      if (key == '3')
        MODE = 3;

      // Redraw objects
      glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(250, 250);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Phong Shading");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();

   return 0;
}
