//---------------------------------------
// Program: cube3.cpp
// Purpose: Demonstrate use of depth buffer
//          when displaying 3D cubes.
// Author:  John Gauch
// Date:    September 2008
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define MIN_X_VIEW -50
#define MAX_X_VIEW 50
#define MIN_Y_VIEW -50
#define MAX_Y_VIEW 50
#define MIN_Z_VIEW -50
#define MAX_Z_VIEW 50

using namespace std;

float xpos = 0.0;
float ypos = 0.0;
float zpos = 0.0;
float size = 0.2;
int counter = 0;
float rotate = 0.0;
float origin_x_trans = 0.0;
float origin_y_trans = 0.0;
GLenum mode = GL_POLYGON;


//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(30.0, 1.0, 1.0, 1.0);
   glEnable(GL_DEPTH_TEST);
}

//---------------------------------------
// Function to draw 3D cube
//---------------------------------------
void cube(float midx, float midy, float midz)
{
   // Define 8 vertices
   float ax = midx - size / 2;
   float ay = midy - size / 2;
   float az = midz + size / 2;
   float bx = midx + size / 2;
   float by = midy - size / 2;
   float bz = midz + size / 2;
   float cx = midx + size / 2;
   float cy = midy + size / 2;
   float cz = midz + size / 2;
   float dx = midx - size / 2;
   float dy = midy + size / 2;
   float dz = midz + size / 2;
   float ex = midx - size / 2;
   float ey = midy - size / 2;
   float ez = midz - size / 2;
   float fx = midx + size / 2;
   float fy = midy - size / 2;
   float fz = midz - size / 2;
   float gx = midx + size / 2;
   float gy = midy + size / 2;
   float gz = midz - size / 2;
   float hx = midx - size / 2;
   float hy = midy + size / 2;
   float hz = midz - size / 2;

   // Draw 6 faces
   glBegin(mode);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(mode);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(mode);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{

   // Handle mouse down
   static int xdown, ydown;
   if (state == GLUT_DOWN)
   {
      xpos = ((2.0*x)/500.0)-1.0;
      ypos = ((-2.0*y)/500.0)+1.0;

      cout << "\nX Down: " << xpos << "\nY Down: " << ypos << endl;

      glutPostRedisplay();
   }
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{

  //Clear screen
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  //Draw first cube
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();




  origin_x_trans = (1.0 * xpos);
  origin_y_trans = (1.0 * ypos);
  rotate = rotate + 0.2;

  //Rotate the cube along all axis
  glTranslatef(origin_x_trans, origin_y_trans, 0.0);
  glRotatef(rotate, 1.0, 1.0 , 1.0);
  cube(0.0, 0.0, 0.0);
  glTranslatef(xpos, ypos, 0.0);



  glFlush();
}

//---------------------------------------
// Motion callback for OpenGL
//---------------------------------------
void motion(int x, int y)
{
   xpos = ((2.0*x)/500.0)-1.0;
   ypos = ((-2.0*y)/500.0)+1.0;
   glutPostRedisplay();
}

void idle()
{
  // cout << "idle" << counter++ << endl;
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
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Angry Bricks");
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutIdleFunc(idle);
   init();
   glutMainLoop();
   return 0;
}
