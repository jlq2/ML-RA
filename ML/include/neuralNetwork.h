#include <vector>

#include "../include/Math.h"



//std::vector <std::vector<float> > vec2D(5, std::vector<int>(4, 1));



class NeuralNetwork{
    public:
        NeuralNetwork(unsigned n_layers, unsigned *values);
        void train(Matrix inputs, std::vector<int> tags);
    private:

    // numero de capas
    unsigned _nLayers;

    //los distintos pesos de la red neuronal
    std::vector<Matrix> _weights;

    // la cantidad de neuronas que tiene cada capa
    std::vector<unsigned> _d; 

};