#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int argc, char **argv) {

   if (argc<4) { 
       cout << "Usage: " << argv[0] << " <number of rowes> <number of columns> <output file name>" << endl;
       return -1;
      }

   string matrix_file;
   unsigned int N = atoi(argv[1]);
   unsigned int M = atoi(argv[2]);
   matrix_file = argv[3];
   unsigned int n;
   signed int nn;
   unsigned int t, t_max, var, var2, var3;

   cout << "Enter 1 to simulate Conway's game of life or 2 to simulate a 2D sand mass, 3 to simulate a 3D sand mass: ";
   cin >> var3;


   if (var3 == 1) {
       cout<< "Enter the value of n, and the number of iterations to be done t: ";
       cin >> n >> t_max;
   }

   if (var3 == 2 || var3 == 3) {
       cout << "Enter the value of n, and the number of dropped sand: ";
       cin >> nn >> t_max;
   }

   if (var3 == 1){
   cout << "Enter 1 for opened bounds, 2 for periodic bounds, 3 for more options: ";
   cin >> var;
   }

   if (var == 3 && var3 == 1) {
       cout << "Enter 3 for living bounds, 4 for random bounds: ";
       cin >> var;
   }

   int matrix[M+1][N+1];
   int temp_matrix[M+1][N+1];

   if (var3 == 1 && var >= 1) {
   cout << "Enter 1 to fill the starting sctructure manually or 2 to generate random values: ";
   cin >> var2;
   }

   if (var2 == 1 && var3 == 1) {
   cout << "Enter elements of starting structure:" << endl;
    for (unsigned int j = 1; j < (M+1); j++) {
        for (unsigned int i = 1; i < (N+1); i++) {
            cout << "Enter element start" << j << i << ": ";
            cin >> matrix[j][i];
            }
        }
      }

    if (var2 == 2) {
        srand(time(NULL));
        for (unsigned int j = 1; j < (N+1); j++) {
            for (unsigned int i = 1; i < (N+1); i++) {
                matrix[j][i] = rand() % 2;
            }
        }
    }

    if (var3 == 2 || var3 == 3) {
        for (unsigned int j = 0; j < (M+2); j++) {
            for (unsigned int i = 0; i < (N+2); i++) {
                matrix[j][i] = 0;
            }
        }
    }

    clock_t tStart = clock();

    ostringstream m_file;

    if (var3 == 2 || var3 == 3) {
    for (unsigned int m = 0; m < (M+2); m++) {
        for (unsigned int n = 0; n < (N+2); n++) { 
            temp_matrix[m][n] = matrix[m][n];
            }
        }
    m_file << matrix_file << ".data";
    ofstream start(m_file.str().c_str());
    for (unsigned int m = 1; m < (M+1); m++) {
              for (unsigned int n = 1; n < (N+1); n++) {
                  start << temp_matrix[m][n] << "\t";
                  matrix[m][n] = temp_matrix[m][n];
                  }
                  start << endl;
               }
    }

    if (var3 == 1) {
        for (unsigned int m = 1; m < (M+1); m++) {
            for (unsigned int n = 1; n < (N+1); n++) { 
                temp_matrix[m][n] = matrix[m][n];
            }
        }

    m_file << matrix_file << ".data";
    ofstream start(m_file.str().c_str());
    for (unsigned int m = 1; m < (M+1); m++) {
              for (unsigned int n = 1; n < (N+1); n++) {
                  start << temp_matrix[m][n] << "\t";
                  matrix[m][n] = temp_matrix[m][n];
                  }
                  start << endl;
               }
    }

   unsigned int neighbours;
   //periodic bounds
   if (var == 2 && var3 == 1) {
   while (t < t_max) {
       ostringstream file;
       file << matrix_file << t << ".data";
       ofstream result(file.str().c_str());
       for (unsigned int k=1; k<(M+1); k++) {
           for (unsigned int j=1; j<(N+1); j++) {
               
               if (k == 1 && j == 1) {
                   neighbours = matrix[k][j+1]+matrix[k+1][j+1]+matrix[k+1][j] + matrix[M][2]+matrix[M][1]+matrix[M][N]+matrix[1][N]+matrix[2][N];
               }

               else if (k == M && j == 1) {
                   neighbours = matrix[k-1][j]+matrix[k-1][j+1]+matrix[k][j+1] + matrix[M-1][N]+matrix[M][N]+matrix[1][N]+matrix[1][1]+matrix[1][2];
               }

               else if (k == 1 && j == N) {
                   neighbours = matrix[k+1][j]+matrix[k+1][j-1]+matrix[k][j-1] + matrix[M][N-1]+matrix[M][N]+matrix[M][1]+matrix[1][1]+matrix[2][1];
               }

               else if (k == M && j == N) {
                   neighbours = matrix[k-1][j]+matrix[k-1][j-1]+matrix[k][j-1] + matrix[M-1][1]+matrix[M][1]+matrix[1][1]+matrix[1][N]+matrix[1][N-1];
               }

               else if (j == 1 && (k != 1 || k != M)) {
                   neighbours = matrix[k-1][j]+matrix[k-1][j+1]+matrix[k][j+1]+matrix[k+1][j+1]+matrix[k+1][j] + matrix[k-1][N]+matrix[k][N]+matrix[k+1][N];
               }

               else if (k == 1 && (j != 1 || j != N)) {
                   neighbours = matrix[k][j+1]+matrix[k+1][j+1]+matrix[k+1][j]+matrix[k+1][j-1]+matrix[k][j-1] + matrix[M][j-1]+matrix[M][j]+matrix[M][j+1];
               }

               else if (j == N && (k != 1 || k != M)) {
                   neighbours = matrix[k-1][j]+matrix[k-1][j-1]+matrix[k][j-1]+matrix[k+1][j-1]+matrix[k+1][j] + matrix[k-1][1]+matrix[k][1]+matrix[k+1][1];
               }

               else if (k == M && (j != 1 || j != N)) {
                   neighbours = matrix[k][j+1]+matrix[k-1][j+1]+matrix[k-1][j]+matrix[k-1][j-1]+matrix[k][j-1] + matrix[1][j-1]+matrix[1][j]+matrix[1][j+1];
               }
               else {
                   neighbours = matrix[k-1][j-1]+matrix[k][j-1]+matrix[k+1][j-1]+matrix[k-1][j]+matrix[k+1][j]+matrix[k-1][j+1]+matrix[k][j+1]+matrix[k+1][j+1];
               }

                  if(neighbours == (n+1) && matrix[k][j] == 0)
                     temp_matrix[k][j] = 1;
                  if((neighbours == (n+1) || neighbours == n) && matrix[k][j] == 1)
                     temp_matrix[k][j] = matrix[k][j];
                  if(neighbours > (n+1) || neighbours < n)
                     temp_matrix[k][j] = 0;
                }
            }
           for (unsigned int m = 1; m < (M+1); m++) {
              for (unsigned int n = 1; n < (N+1); n++) {
                  result << temp_matrix[m][n] << "\t";
                  matrix[m][n] = temp_matrix[m][n];
                  }
                  result << endl;
               }
           t++;
        }
   }
   //random bounds
   if (var == 4) {
       srand(time(NULL));
       for (unsigned int k = 0; k < (M+2); k++) {
           matrix[k][0] == rand() % 2;
           matrix[k][M+1] == rand() % 2;
       }
       for (unsigned int j = 0; j < (N+2); j++) {
           matrix[0][j] == rand() % 2;
           matrix[N+1][j] == rand() %2;
       }
   while (t < t_max) {
       ostringstream file;
       file << matrix_file << t << ".data";
       ofstream result(file.str().c_str());
       for (unsigned int k = 1; k < (M+1); k++) {
           for (unsigned int j = 1; j < (N+1); j++) {               
                  neighbours = matrix[k-1][j-1]+matrix[k][j-1]+matrix[k+1][j-1]+matrix[k-1][j]+matrix[k+1][j]+matrix[k-1][j+1]+matrix[k][j+1]+matrix[k+1][j+1];

                  if(neighbours == (n+1) && matrix[k][j] == 0)
                     temp_matrix[k][j] = 1;
                  if((neighbours == (n+1) || neighbours == n) && matrix[k][j] == 1)
                     temp_matrix[k][j] = matrix[k][j];
                  if(neighbours > (n+1) || neighbours < n)
                     temp_matrix[k][j] = 0;
                }
            }
           for (unsigned int m = 1; m < (M+1); m++) {
              for (unsigned int n = 1; n < (N+1); n++) {
                  result << temp_matrix[m][n] << "\t";
                  matrix[m][n] = temp_matrix[m][n];
                  }
                  result << endl;
               }
           t++;
        }
   }
   //living bounds
   if (var == 3) {
       for (unsigned int k = 0; k < (M+2); k++) {
           matrix[k][0] = 1;
           matrix[k][M+1] = 1;
       }
       for (unsigned int j = 0; j < (N+2); j++) {
           matrix[0][j] = 1;
           matrix[N+1][j] = 1;
       }
   while (t < t_max) {
       ostringstream file;
       file << matrix_file << t << ".data";
       ofstream result(file.str().c_str());
       for (unsigned int k = 1; k < (M+1); k++) {
           for (unsigned int j = 1; j < (N+1); j++) {               
                  neighbours = matrix[k-1][j-1]+matrix[k][j-1]+matrix[k+1][j-1]+matrix[k-1][j]+matrix[k+1][j]+matrix[k-1][j+1]+matrix[k][j+1]+matrix[k+1][j+1];

                  if(neighbours == (n+1) && matrix[k][j] == 0)
                     temp_matrix[k][j] = 1;
                  if((neighbours == (n+1) || neighbours == n) && matrix[k][j] == 1)
                     temp_matrix[k][j] = matrix[k][j];
                  if(neighbours > (n+1) || neighbours < n)
                     temp_matrix[k][j] = 0;
                }
            }
           for (unsigned int m = 1; m < (M+1); m++) {
              for (unsigned int n = 1; n < (N+1); n++) {
                  result << temp_matrix[m][n] << "\t";
                  matrix[m][n] = temp_matrix[m][n];
                  }
                  result << endl;
               }
           t++;
        }
   }

   //open bounds
   if (var == 1 && var3 == 1) {
       for (unsigned int k = 0; k < (M+2); k++) {
           matrix[k][0] = 0;
           matrix[k][M+1] = 0;
       }
       for (unsigned int j = 0; j < (N+2); j++) {
           matrix[0][j] = 0;
           matrix[N+1][j] = 0;
       }
   while (t < t_max) {
       ostringstream file;
       file << matrix_file << t << ".data";
       ofstream result(file.str().c_str());
       for (unsigned int k = 1; k < (M+1); k++) {
           for (unsigned int j = 1; j < (N+1); j++) {               
                  neighbours = matrix[k-1][j-1]+matrix[k][j-1]+matrix[k+1][j-1]+matrix[k-1][j]+matrix[k+1][j]+matrix[k-1][j+1]+matrix[k][j+1]+matrix[k+1][j+1];

                  if(neighbours == (n+1) && matrix[k][j] == 0)
                     temp_matrix[k][j] = 1;
                  if((neighbours == (n+1) || neighbours == n) && matrix[k][j] == 1)
                     temp_matrix[k][j] = matrix[k][j];
                  if(neighbours > (n+1) || neighbours < n)
                     temp_matrix[k][j] = 0;
                }
            }
           for (unsigned int m = 1; m < (M+1); m++) {
              for (unsigned int n = 1; n < (N+1); n++) {
                  result << temp_matrix[m][n] << "\t";
                  matrix[m][n] = temp_matrix[m][n];
                  }
                  result << endl;
               }
           t++;
        }
   }
   //3D sand mass
   if (var3 == 3) {
       while(t < t_max) {
           unsigned int rv1 = rand() % N + 1;
           unsigned int rv2 = rand() % M + 1;

           temp_matrix[rv1][rv2] += 1;
           if (((temp_matrix[rv1][rv2] - temp_matrix[rv1-1][rv2-1]) >= nn + 1) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1-1][rv2]) >= (nn + 1)) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1-1][rv2+1]) >= (nn + 1)) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1][rv2-1]) >= (nn + 1)) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1][rv2+1]) >= (nn + 1)) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1+1][rv2-1]) >= (nn + 1)) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1+1][rv2]) >= (nn + 1)) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1+1][rv2+1]) >= (nn + 1))) {
               while (matrix[rv1][rv2] != temp_matrix[rv1][rv2]) {
                   srand(time(NULL));
                   signed int rv3 = rand() % 3 - 1;
                   signed int rv4 = rand() % 3 - 1;
                   
                   if (temp_matrix[rv1-rv3][rv2-rv4] < temp_matrix[rv1][rv2]) {
                       temp_matrix[rv1][rv2] -= 1;
                       if (rv3 == 0 && rv4 == 0) {
                           temp_matrix[rv1-1][rv2-1] += 1;
                       }
                       else {
                           temp_matrix[rv1-rv3][rv2-rv4] += 1;
                       }

                       matrix[rv1][rv2] = temp_matrix[rv1][rv2];
                       matrix[rv1-rv3][rv2-rv4] = temp_matrix[rv1-rv3][rv2-rv4];
                   }
                }
           }

           matrix[rv1][rv2] = temp_matrix[rv1][rv2];
       t++;
       }
    ofstream start(m_file.str().c_str());
    for (unsigned int m=1; m<(M+1); m++) {
              for (unsigned int n=1; n<(N+1); n++) {
                  start << temp_matrix[m][n] << "\t";
                  matrix[m][n]=temp_matrix[m][n];
                  }
                  start << endl;
               }
   }
   //2D sand mass
   if (var3 == 2) {
       while(t < t_max) {
           unsigned int rv1 = rand() % (N-1) + 1;
           unsigned int rv2 = 1;

           temp_matrix[rv1][rv2] += 1;
           if (((temp_matrix[rv1][rv2] - temp_matrix[rv1-1][rv2]) >= nn + 1) || ((temp_matrix[rv1][rv2] - temp_matrix[rv1+1][rv2]) >= (nn + 1))) {
               while (matrix[rv1][rv2] != temp_matrix[rv1][rv2]) {
                   srand(time(NULL));
                   signed int rv3 = rand() % 3 - 1;
                   
                   if (temp_matrix[rv1-rv3][rv2] < temp_matrix[rv1][rv2]) {
                       temp_matrix[rv1][rv2] -= 1;
                       temp_matrix[rv1-rv3][rv2] += 1;

                       matrix[rv1][rv2] = temp_matrix[rv1][rv2];
                       matrix[rv1-rv3][rv2] = temp_matrix[rv1-rv3][rv2];
                   }
                }
           }
           matrix[rv1][rv2] = temp_matrix[rv1][rv2];
       t++;
       }

    ofstream start(m_file.str().c_str());
    for (unsigned int m=1; m<(M+1); m++) {
              for (unsigned int n=1; n<(N+1); n++) {
                  start << temp_matrix[m][n] << "\t";
                  matrix[m][n]=temp_matrix[m][n];
                  }
                  start << endl;
               }
   }



   cout << "Time elapsed: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

   return 0;
}