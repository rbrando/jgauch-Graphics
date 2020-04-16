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
