#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <math.h>       /* tanh, log, pow*/
#include <stdexcept>
#include <string>
#include <iostream>
using namespace std;



typedef vector<vector<float>> Matrix ;


class Math{

    public:
    
    //Get cero Matrix
     static Matrix createMatrix(int row, int col) {


        Matrix a =  Matrix(row, std::vector<float>(col, 0));

        return a;
    }

    //Get random Matrix
     static Matrix createRandMatrix(int row, int col) {

        //srand (time(0));

        Matrix a =  Matrix(row, std::vector<float>(col ));

        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < a[i].size(); j++) {
                a[i][j] = float(float(rand() % 100)) / 100;
            }
        }

        return a;
    }



    //Get the Transpose of a matrix
    static Matrix T(Matrix a) {
        int m = a.size();
        int n = a[0].size();
        Matrix b = createMatrix(n,m);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                b[j][i] = a[i][j];
            }
        }
        return b;
    }

    //Sumar dos matrices
    static Matrix add(Matrix a,Matrix b) {
        int m = a.size();
        int n = a[0].size();
        Matrix c = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = a[i][j] + b[i][j] ;
            }
        }
        return c;
    }


    //Sumar dos matrices
    static Matrix sub(Matrix a,Matrix b) {
        int m = a.size();
        int n = a[0].size();
        Matrix c = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = a[i][j] - b[i][j] ;
            }
        }
        return c;
    }


    //Sumar dos matrices
    static Matrix sub(float a,Matrix b) {
        int m = b.size();
        int n = b[0].size();
        Matrix c = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = a - b[i][j] ;
            }
        }
        return c;
    }


    // dot product // scalar product 
    static Matrix dot(Matrix a, Matrix b) {
        int m1 = a.size();
        int n1 = a[0].size();
        int m2 = b.size();
        int n2 = b[0].size();
        if (n1 != m2) {
            cout<<  "dot exception: a[0].size(): " <<  n1 <<  " b.size(): " <<  m2 << endl;
            cout << flush;
            throw std::invalid_argument(  "dot exception" + n1);

        }
        Matrix c = createMatrix(m1,n2); //new double[m1][n2];
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                for (int k = 0; k < n1; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }

     /**
     * 
     * @return sigmoid of matrix a
     */
     static Matrix sigmoid(Matrix a) {
        int m = a.size();
        int n = a[0].size();
        Matrix z = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                z[i][j] = (1.0 / (1 + exp(-a[i][j])));
            }
        }
        return z;
    }


    //Divide Matrix
     static Matrix divide(Matrix x, int a) {
        int m = x.size();
        int n = x[0].size();
        Matrix z = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                z[i][j] = (x[i][j] / a);
            }
        }
        return z;
    }


    static Matrix multiply(Matrix a,Matrix b) {
        int m = a.size();
        int n = a[0].size();
        Matrix c = createMatrix(m,n);

        if (b.size() != m || b[0].size() != n) {
            throw std::invalid_argument( "multiply" );
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = a[i][j] * b[i][j] ;
            }
        }
        return c;
    }



    static Matrix multiply(float a,Matrix b) {
        int m = b.size();
        int n = b[0].size();
        Matrix c = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] =  b[i][j] * a ;
            }
        }
        return c;
    }





    //power elements of a  Matrix
     static Matrix power(Matrix x, int a) {
        int m = x.size();
        int n = x[0].size();
        Matrix z = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                z[i][j] = (float) pow(x[i][j] , (float)a);
            }
        }
        return z;
    }

     static float mixBits(uint32_t n1[], uint32_t n2[], int point);


     static float cross_entropy(int batch_size, Matrix Y, Matrix A) {
        int m = A.size();
        int n = A[0].size();
        Matrix z = createMatrix(m,n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                z[i][j] = (Y[i][j] * log(A[i][j])) + ((1 - Y[i][j]) * log(1 - A[i][j]));
            }
        }

        float sum = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum += z[i][j];
            }
        }
        return -sum / batch_size;
    }



};







