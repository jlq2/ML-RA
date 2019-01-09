#pragma once


#include <vector>
#include <iostream>

using namespace std;

#include "../include/Math.h"


//std::vector <std::vector<float> > vec2D(5, std::vector<int>(4, 1));



class NeuralNetwork{
    public:
        NeuralNetwork(unsigned n_layers, unsigned *values);
        NeuralNetwork(int nodes, int batch);
        void train(Matrix inputs, Matrix tags, int it);
        void trainGenetic(Matrix inputs, Matrix tags);

        float predict(Matrix m);
        float classify(vector<float> m);

        float fitness(Matrix inputs, Matrix tags, int index);

    public:
        int p_mut = 0.1;
        int nodes ;
        int m ;

        Matrix W1;
        Matrix b1;

        Matrix W2;
        Matrix b2;



        int population = 20;
        vector<Matrix> pop_W1; 
        vector<Matrix> pop_b1;

        vector<Matrix> pop_W2; 
        vector<Matrix> pop_b2;


    // numero de capas
    unsigned _nLayers;

    //los distintos pesos de la red neuronal
    std::vector<Matrix> _weights;

    // la cantidad de neuronas que tiene cada capa
    std::vector<unsigned> _d; 

};