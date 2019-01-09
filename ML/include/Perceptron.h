
#pragma once

#include <vector>
#include <iostream>
#include "../include/Math.h"

using namespace std;




////////////////////////////////////////////////////
// Sobre Carga de Operadores
////////////////////////////////////////////////////
template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v);

float operator*(const vector<float>& v1, const vector<float>& v2);

vector<float> operator*(const vector<float>& v1, const float constNumber);

vector<float> operator+=( vector<float>& v1, const vector<float>& v2);


// Número de iteraciones a durante el entrenamiento
static const int CONST_ITERACIONES = 1000;

class point{
public:
    float _x = 0;
	float _y = 0;
	int _label = 0;

	point(int x, int y, int label);

    vector<float> toVector();
	
    int check(int tag);
	
    void draw();
};

class Perceptron{
public:
    vector<float> _W;
    vector<float> _bestW;
    float _bestError = 9999;

    Perceptron(Matrix inputs);

    int classify( vector<float> x);
    int activation(float sum);

    void info();

    //devolver la tasa de error tras entrenar
    float train(Matrix inputs, vector<int> tags);
};