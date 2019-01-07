#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <math.h>       /* tanh, log */

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

        srand (time(0));
        rand();

        Matrix a =  Matrix(row, std::vector<float>(col, (rand() % 100) / 100));

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


    // dot product // scalar product 
    static Matrix dot(Matrix a, Matrix b) {
        int m1 = a.size();
        int n1 = a[0].size();
        int m2 = b.size();
        int n2 = b[0].size();
        if (n1 != m2) {
            throw "dot error";
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



};