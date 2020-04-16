//---------------------------------------
// Program: texture3.cpp
// Purpose: Texture map brick photograph
//          onto a cube model.
// Author:  John Gauch
// Date:    April 2011
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"
#include <time.h>
#include <iostream>
using namespace std;


// Global variables
#define ROTATE 1
#define TRANSLATE 2
int xangle = 10;
int yangle = 10;
int zangle = 10;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int xmin = -1;
int xmax = 1;
int ymin = -1;
int ymax = 1;
int zmin = -1;
int zmax = 1;

//Keep track of the image we pull textures from.
int texture_index = 0;
unsigned char * texture;
unsigned char * cat_dog_image[20];
int stim = 0;
int mode = ROTATE;

class Block
{
public:
  float Px, Py, Pz;
  float Vx, Vy, Vz;
  int Ax, Ay, Az;
  float radius;
  int xdim = 256; int ydim = 256;
  int rand_image = 0;
  float rotate = 0.0;


  Block()
  {

    Py = 0.98 - ((random(20)+(stim))/100); Pz = 0.0;
    // Vx = -0.002 + ((random(40)+(stim+Py))/100000);
    Vx = 0.0;
    Vy = -0.009 + ((random(40)+(stim+Py))/100000);
    Vz = 0.0;
    rotate = 0;
    Ax = random_float(100,1); Ay = 0; Az = 0;
    radius = 0.3-((random(40)+(stim+Px))/1000);
    rand_image = random(20);

    if (rand_image < 0)
      rand_image = rand_image * -1;

    if (radius > 0.2)
      radius = 0.2;

    if (radius < 0.05)
      radius = 0.1;

    if (Py < -1.1)
      Py = 1.0;

    if (Py > 1.1)
      Py = 1.0;

    if (Vy > 0)
      Vy = -1 * Vy;


    if (rand_image % 2 == 0)
    {
        if (random(20) % 2 == 0)
        {
            Px = -1*(random_float(100,10));
            radius += 0.02;
        }
        else
            Px = -1*(random_float(100,10));
    }
    else
    {
        if (stim % 2 == 0)
          Px = -1*(random_float(100,10));
        else
        {
          Px = 1*(random_float(100,10));
          radius += 0.1;
        }
    }

    if (Px > 0.9)
      Px = 0.9;
    if (Px < -0.9)
      Px = -0.9;
  }

  int random(int max)
  {
    srand(time(NULL));
    stim ++;
    return ((rand()*stim) % max);
  }

  float random_float(int max, int caliber)
  {
    srand(time(NULL));
    stim ++;
    return ((((rand()*stim)+(rand_image/100)) % max)/(100.0*caliber));
  }

  void draw()
  {

       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, cat_dog_image[rand_image]);
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

       glTranslatef(Px, Py, Pz);
       glRotatef(rotate, 1.0, 1.0 , 0.0);

       // texture = ;
       // Define 8 vertices
       float ax = 0.0 - radius / 2.0;
       float ay = 0.0 - radius / 2.0;
       float az = 0.0 + radius / 2.0;
       float bx = 0.0 + radius / 2.0;
       float by = 0.0 - radius / 2.0;
       float bz = 0.0 + radius / 2.0;
       float cx = 0.0 + radius / 2.0;
       float cy = 0.0 + radius / 2.0;
       float cz = 0.0 + radius / 2.0;
       float dx = 0.0 - radius / 2.0;
       float dy = 0.0 + radius / 2.0;
       float dz = 0.0 + radius / 2.0;
       float ex = 0.0 - radius / 2.0;
       float ey = 0.0 - radius / 2.0;
       float ez = 0.0 - radius / 2.0;
       float fx = 0.0 + radius / 2.0;
       float fy = 0.0 - radius / 2.0;
       float fz = 0.0 - radius / 2.0;
       float gx = 0.0 + radius / 2.0;
       float gy = 0.0 + radius / 2.0;
       float gz = 0.0 - radius / 2.0;
       float hx = 0.0 - radius / 2.0;
       float hy = 0.0 + radius / 2.0;
       float hz = 0.0 - radius / 2.0;


       // Draw 6 faces
       glBegin(GL_POLYGON);  // Max texture coord 1.0
       glTexCoord2f(0.0, 0.0);
       glVertex3f(ax, ay, az);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(bx, by, bz);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(cx, cy, cz);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(dx, dy, dz);
       glEnd();

       glBegin(GL_POLYGON);  // Max texture coord 1.0
       glTexCoord2f(0.0, 0.0);
       glVertex3f(ex, ey, ez);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(ax, ay, az);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(dx, dy, dz);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(hx, hy, hz);
       glEnd();

       glBegin(GL_POLYGON);  // Max texture coord 1.0
       glTexCoord2f(0.0, 0.0);
       glVertex3f(fx, fy, fz);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(ex, ey, ez);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(hx, hy, hz);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(gx, gy, gz);
       glEnd();

       glBegin(GL_POLYGON);  // Max texture coord 1.0
       glTexCoord2f(0.0, 0.0);
       glVertex3f(bx, by, bz);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(fx, fy, fz);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(gx, gy, gz);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(cx, cy, cz);
       glEnd();

       glBegin(GL_POLYGON);  // Max texture coord 3.0
       glTexCoord2f(0.0, 0.0);
       glVertex3f(ax, ay, az);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(ex, ey, ez);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(fx, fy, fz);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(bx, by, bz);
       glEnd();

       glBegin(GL_POLYGON);  // Max texture coord 3.0
       glTexCoord2f(0.0, 0.0);
       glVertex3f(gx, gy, gz);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(cx, cy, cz);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(dx, dy, dz);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(hx, hy, hz);
       glEnd();

       //glTranslatef(-Px, -Py, -Pz);

  }

  void update_vel()
  {
      Py += Vy;
      rotate = rotate + 0.1;
      // update_rotate();
  }



};
Block cat_dog_array[50];


//---------------------------------------
// Initialize texture image
//---------------------------------------
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   printf("Interpolating to %d by %d\n", xdim, ydim);

   // Copy image into texture array
   //texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
    cat_dog_image[texture_index] = texture;
    texture_index++;
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Init view
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
   glEnable(GL_DEPTH_TEST);

   // Init texture
   int xdim, ydim;
   unsigned char *texture;


   init_texture((char *)"cats_dogs/cat0.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat1.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat2.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat3.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat4.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat5.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat6.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat7.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat8.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/cat9.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog0.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog1.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog2.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog3.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog4.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog5.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog6.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog7.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog8.jpg", texture, xdim, ydim);
   init_texture((char *)"cats_dogs/dog9.jpg", texture, xdim, ydim);

   glEnable(GL_TEXTURE_2D);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
   // glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
   // glRotatef(xangle, 1.0, 0.0, 0.0);
   // glRotatef(yangle, 0.0, 1.0, 0.0);
   // glRotatef(zangle, 0.0, 0.0, 1.0);

   // Draw objects
   for(int i = 0; i <= 19; i++)
   {

        cat_dog_array[i].draw();

        if (cat_dog_array[i].Py < -1.10)
           cat_dog_array[i] = Block();
        else
        {
           cat_dog_array[i].update_vel();
        }

        if (cat_dog_array[i].Px < -1.10)
          cat_dog_array[i] = Block();
        if (cat_dog_array[i].Px > 1.10)
          cat_dog_array[i] = Block();
    }
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Texture");
   glutDisplayFunc(display);
   glutIdleFunc(display);

   init();
   glutMainLoop();
   return 0;
}
