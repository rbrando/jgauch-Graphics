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
#include "libim/im_color.h"
#include <fstream>
#include <iostream>
using namespace std;

//---------------------------------------
// Read color and depth images
//---------------------------------------
void read_images(string color_name, im_color & color_image,
                 string depth_name, im_float & depth_image)
{
   // ----------------
   // Read color image
   // ----------------
   cout << "input file = " << color_name << endl;
   color_image.ReadJpg(color_name);

   // Create output file name
   int pos = color_name.find(".jpg");
   color_name.erase(pos, 4);
   color_name += ".txt";
   cout << "output file = " << color_name << endl;

   // Open output file
   ofstream dout;
   dout.open(color_name);

   // Get image dimensions
   int xdim = color_image.R.Xdim;
   int ydim = color_image.R.Ydim;
   cout << "xdim = " << xdim << endl;
   cout << "ydim = " << ydim << endl;

   // Print color values
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         dout << color_image.R.Data2D[y][x] << " "
              << color_image.B.Data2D[y][x] << " "
              << color_image.G.Data2D[y][x] << endl;
      }

   // Close output file
   dout.close();

   // ----------------
   // Read depth image
   // ----------------
   cout << "input file = " << depth_name << endl;
   depth_image.ReadJpg(depth_name);

   // Create output file name
   pos = depth_name.find(".jpg");
   depth_name.erase(pos, 4);
   depth_name += ".txt";
   cout << "output file = " << depth_name << endl;

   // Open output file
   dout.open(depth_name);

   // Get image dimensions
   xdim = depth_image.Xdim;
   ydim = depth_image.Ydim;
   cout << "xdim = " << xdim << endl;
   cout << "ydim = " << ydim << endl;

   // Print depth values
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
         dout << depth_image.Data2D[y][x] << " ";

   // Close output file
   dout << endl;
   dout.close();

}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   im_color color;
   im_float depth;
   read_images("penny-image.jpg", color,
               "penny-depth.jpg", depth);
   return 0;
}
