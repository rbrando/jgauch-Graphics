//---------------------------------------
// Program: surface2.cpp
// Purpose: Generate and place random building
//          building models on fractal surface.
// Author:  John Gauch
// Date:    September 2008
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables 
int xangle = 0;
int yangle = 0;
int zangle = 0;

// Surface and normals
#define SIZE 32
float Px[SIZE][SIZE];
float Py[SIZE][SIZE];
float Pz[SIZE][SIZE];
float Nx[SIZE][SIZE];
float Ny[SIZE][SIZE];
float Nz[SIZE][SIZE];

// House locations
#define MIN_DIST 0.02
#define MAX_DIST 10
#define MODE GL_POLYGON
#define COUNT 15
float Hx[COUNT];
float Hy[COUNT];
float Hz[COUNT];

//---------------------------------------
// Calculate random value between [-R..R]
//---------------------------------------
float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

//---------------------------------------
// Recursive function to split surface
//---------------------------------------
void split(int xlow, int xhigh, int ylow, int yhigh, float radius)
{
   // Check terminating condition
   if ((xhigh > xlow+1) || (yhigh > ylow+1))
   {
      // Calculate length of diagonal
      int xmid = (xhigh + xlow) / 2;
      int ymid = (yhigh + ylow) / 2;
      float dx = Px[xhigh][yhigh] - Px[xlow][ylow];
      float dy = Py[xhigh][yhigh] - Py[xlow][ylow];
      float dz = Pz[xhigh][yhigh] - Pz[xlow][ylow];
      float length = sqrt(dx * dx + dy * dy + dz * dz) / radius;

      // Generate five midpoints with random displacements
      Px[xlow][ymid] = (Px[xlow][ylow] + Px[xlow][yhigh]) / 2 + myrand(length);
      Py[xlow][ymid] = (Py[xlow][ylow] + Py[xlow][yhigh]) / 2 + myrand(length);
      Pz[xlow][ymid] = (Pz[xlow][ylow] + Pz[xlow][yhigh]) / 2 + myrand(length);

      Px[xhigh][ymid] = (Px[xhigh][ylow] + Px[xhigh][yhigh]) / 2 + myrand(length);
      Py[xhigh][ymid] = (Py[xhigh][ylow] + Py[xhigh][yhigh]) / 2 + myrand(length);
      Pz[xhigh][ymid] = (Pz[xhigh][ylow] + Pz[xhigh][yhigh]) / 2 + myrand(length);

      Px[xmid][ylow] = (Px[xlow][ylow] + Px[xhigh][ylow]) / 2 + myrand(length);
      Py[xmid][ylow] = (Py[xlow][ylow] + Py[xhigh][ylow]) / 2 + myrand(length);
      Pz[xmid][ylow] = (Pz[xlow][ylow] + Pz[xhigh][ylow]) / 2 + myrand(length);

      Px[xmid][yhigh] = (Px[xlow][yhigh] + Px[xhigh][yhigh]) / 2 + myrand(length);
      Py[xmid][yhigh] = (Py[xlow][yhigh] + Py[xhigh][yhigh]) / 2 + myrand(length);
      Pz[xmid][yhigh] = (Pz[xlow][yhigh] + Pz[xhigh][yhigh]) / 2 + myrand(length);

      Px[xmid][ymid] = (Px[xlow][ylow] + Px[xhigh][yhigh]) / 2 + myrand(length);
      Py[xmid][ymid] = (Py[xlow][ylow] + Py[xhigh][yhigh]) / 2 + myrand(length);
      Pz[xmid][ymid] = (Pz[xlow][ylow] + Pz[xhigh][yhigh]) / 2 + myrand(length);

      // Perform recursive calls
      split(xlow, xmid, ylow, ymid, radius);
      split(xmid, xhigh, ylow, ymid, radius);
      split(xlow, xmid, ymid, yhigh, radius);
      split(xmid, xhigh, ymid, yhigh, radius);
   }
}

//---------------------------------------
// Initialize random surface 
//---------------------------------------
void init_surface()
{
   // Initialize surface points
   Px[0][0] = -1.0;
   Py[0][0] = -1.0;
   Pz[0][0] = 0.0;
   Px[0][SIZE-1] = -1.0;
   Py[0][SIZE-1] = 1.0;
   Pz[0][SIZE-1] = 0.0;
   Px[SIZE-1][0] = 1.0;
   Py[SIZE-1][0] = -1.0;
   Pz[SIZE-1][0] = 0.0;
   Px[SIZE-1][SIZE-1] = 1.0;
   Py[SIZE-1][SIZE-1] = 1.0;
   Pz[SIZE-1][SIZE-1] = 0.0;
   split(0, SIZE-1, 0, SIZE-1, 20);

   // Smooth surface points
   for (int i=1; i<SIZE-1; i++)
   for (int j=1; j<SIZE-1; j++)
   {
      Px[i][j] = (Px[i][j] + Px[i-1][j] + Px[i+1][j] + Px[i][j-1] + Px[i][j+1] ) / 5; 
      Py[i][j] = (Py[i][j] + Py[i-1][j] + Py[i+1][j] + Py[i][j-1] + Py[i][j+1] ) / 5; 
      Pz[i][j] = (Pz[i][j] + Pz[i-1][j] + Pz[i+1][j] + Pz[i][j-1] + Pz[i][j+1] ) / 5; 
   }
}

//---------------------------------------
// Initialize surface normals
//---------------------------------------
void init_normals()
{
   // Initialize surface normals
   for (int i=0; i<SIZE-1; i++)
   for (int j=0; j<SIZE-1; j++)
   {
      // Get tangents S and T
      float Sx = Px[i+1][j] - Px[i][j];
      float Sy = Py[i+1][j] - Py[i][j];
      float Sz = Pz[i+1][j] - Pz[i][j];
      float Tx = Px[i][j+1] - Px[i][j];
      float Ty = Py[i][j+1] - Py[i][j];
      float Tz = Pz[i][j+1] - Pz[i][j];
      
      // Calculate N = S cross T
      Nx[i][j] = Sy*Tz - Sz*Ty;
      Ny[i][j] = Sz*Tx - Sx*Tz;
      Nz[i][j] = Sx*Ty - Sy*Tx;

      // Make unit vector
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

   // Handle last row and column
   for (int i=0; i<SIZE; i++)
   {
      Nx[i][SIZE-1] = Nx[i][SIZE-2];
      Ny[i][SIZE-1] = Ny[i][SIZE-2];
      Nz[i][SIZE-1] = Nz[i][SIZE-2];
      Nx[SIZE-1][i] = Nx[SIZE-2][i];
      Ny[SIZE-1][i] = Ny[SIZE-2][i];
      Nz[SIZE-1][i] = Nz[SIZE-2][i];
   }
}

//---------------------------------------
// Initialize house locations
//---------------------------------------
void init_house()
{
   // Position houses at random locations on surface
   int count = 0;
   while (count < COUNT)
   {
      // Generate random house location
      int i = rand() % SIZE;
      int j = rand() % SIZE;
      float hx = Px[i][j];
      float hy = Py[i][j];
      float hz = Pz[i][j];

      // Compare to all other house locations
      float min_dist = MAX_DIST;
      for (i = 0; i<count; i++)
      {
         float dist = (hx-Hx[i])*(hx-Hx[i]) 
                    + (hy-Hy[i])*(hy-Hy[i]) 
                    + (hz-Hz[i])*(hz-Hz[i]);
         if (min_dist > dist)
            min_dist = dist;
      }

      // Save house location
      if (min_dist > MIN_DIST)
      {
         // printf("%d %4.2f %4.2f %4.2f\n", count, hx, hy, hz);
         Hx[count] = hx;
         Hy[count] = hy;
         Hz[count] = hz;
         count++;
      }
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
   glEnable(GL_DEPTH_TEST);
}
  

//---------------------------------------
// Draw the house at specified location
//---------------------------------------
void draw_house(float x, float y, float z)
{
   float x_size = 0.12;
   float x_min = x - x_size/2;
   float x_max = x + x_size/2;
   float y_size = 0.12;
   float y_min = y - y_size/2;
   float y_max = y + y_size/2;
   float z_size = 0.15;
   float z_min = z;
   float z_mid = z + z_size * 0.75;
   float z_max = z + z_size;

   // Draw roof and door
   glColor3f(1.0, 0.0, 1.0);
   glBegin(MODE);
   glVertex3f(x, y_min, z_max);
   glVertex3f(x, y_max, z_max);
   glVertex3f(x_min, y_max, z_mid);
   glVertex3f(x_min, y_min, z_mid);
   glEnd();
   glBegin(MODE);
   glVertex3f(x, y_min, z_max);
   glVertex3f(x, y_max, z_max);
   glVertex3f(x_max, y_max, z_mid);
   glVertex3f(x_max, y_min, z_mid);
   glEnd();
   glBegin(MODE);
   glVertex3f(x-x_size/6, y_min-0.001, z_min);
   glVertex3f(x-x_size/6, y_min-0.001, z_min+z_size/2);
   glVertex3f(x+x_size/6, y_min-0.001, z_min+z_size/2);
   glVertex3f(x+x_size/6, y_min-0.001, z_min);
   glEnd();

   // Draw four walls and floor
   glColor3f(0.0, 0.0, 1.0);
   glBegin(MODE);
   glVertex3f(x_min, y_min, z_min);
   glVertex3f(x_min, y_min, z_mid);
   glVertex3f(x, y_min, z_max);
   glVertex3f(x_max, y_min, z_mid);
   glVertex3f(x_max, y_min, z_min);
   glEnd();
   glBegin(MODE);
   glVertex3f(x_min, y_max, z_min);
   glVertex3f(x_min, y_max, z_mid);
   glVertex3f(x, y_max, z_max);
   glVertex3f(x_max, y_max, z_mid);
   glVertex3f(x_max, y_max, z_min);
   glEnd();
   glBegin(MODE);
   glVertex3f(x_min, y_min, z_min);
   glVertex3f(x_min, y_min, z_mid);
   glVertex3f(x_min, y_max, z_mid);
   glVertex3f(x_min, y_max, z_min);
   glEnd();
   glBegin(MODE);
   glVertex3f(x_max, y_min, z_min);
   glVertex3f(x_max, y_min, z_mid);
   glVertex3f(x_max, y_max, z_mid);
   glVertex3f(x_max, y_max, z_min);
   glEnd();
   glBegin(MODE);
   glVertex3f(x_min, y_min, z_min);
   glVertex3f(x_min, y_max, z_min);
   glVertex3f(x_max, y_max, z_min);
   glVertex3f(x_max, y_min, z_min);
   glEnd();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);
   int i, j;

#define SURFACE
#ifdef SURFACE
   // Draw the surface
   glColor3f(1.0, 0.0, 0.0);
   for (i = 0; i < SIZE; i++)
   {
      glBegin(GL_LINE_STRIP);
      for (j = 0; j < SIZE; j++)
	 glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
      glEnd();
   }
   glColor3f(0.0, 1.0, 0.0);
   for (j = 0; j < SIZE; j++)
   {
      glBegin(GL_LINE_STRIP);
      for (i = 0; i < SIZE; i++)
	 glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
      glEnd();
   }
#endif

#define NO_NORMALS
#ifdef NORMALS
   // Draw the normals
   glColor3f(0.0, 0.0, 1.0);
   for (i = 0; i < SIZE; i++)
   for (j = 0; j < SIZE; j++)
   {
      glBegin(GL_LINE_STRIP); 
      glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
      glVertex3f(Px[i][j]+0.05*Nx[i][j], 
                 Py[i][j]+0.05*Ny[i][j], 
                 Pz[i][j]+0.05*Nz[i][j]);
      glEnd();
   }
#endif

#define HOUSE
#ifdef HOUSE
   // Draw the houses
   for (i = 0; i < COUNT; i++)
      draw_house(Hx[i], Hy[i], Hz[i]);
#endif
   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Update angles
   if (key == 'x')
      xangle -= 5;
   else if (key == 'y')
      yangle -= 5;
   else if (key == 'z')
      zangle -= 5;
   else if (key == 'X')
      xangle += 5;
   else if (key == 'Y')
      yangle += 5;
   else if (key == 'Z')
      zangle += 5;

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
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Surface");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init();
   init_surface();
   init_normals();
   init_house();
    printf("Keyboard commands:\n");
    printf("   'x' - rotate x-axis -5 degrees\n");
    printf("   'X' - rotate x-axis +5 degrees\n");
    printf("   'y' - rotate y-axis -5 degrees\n");
    printf("   'Y' - rotate y-axis +5 degrees\n");
    printf("   'z' - rotate z-axis -5 degrees\n");
    printf("   'Z' - rotate z-axis +5 degrees\n");
   glutMainLoop();
   return 0;
}
