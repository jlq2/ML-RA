

#pragma once

#include <vector>

#include "../include/Math.h"

using namespace std;



class NeuralNetwork{
    public:
        NeuralNetwork(unsigned n_layers, unsigned *values);
        NeuralNetwork();

        void train(Matrix inputs, Matrix tags);
        void trainGenetic(Matrix inputs, Matrix tags);

        float predict(Matrix m);
        float fitness(Matrix inputs, Matrix tags, int index);

    private:
        int p_mut = 2;
        int nodes = 400;
        int m = 4;

        Matrix W1, W2;
        Matrix b1, b2;
        
        int population = 20;
        vector<Matrix> pop_W1, pop_W2; 
        vector<Matrix> pop_b1, pop_b2;

        // numero de capas
        unsigned _nLayers;

        //los distintos pesos de la red neuronal
        std::vector<Matrix> _weights;

        // la cantidad de neuronas que tiene cada capa
        std::vector<unsigned> _d; 

};