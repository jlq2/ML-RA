#include "../include/neuralNetwork.h"
#include <math.h>       /* tanh, log */


NeuralNetwork::NeuralNetwork(unsigned layers, unsigned *values)  {


        _nLayers = layers;
        _weights =  std::vector<Matrix>(layers) ;
        _d =     std::vector<unsigned>(layers); // cantidad de nodos


        if (layers >= 2)
        {

    
            _d[0] = values[0];

            for (unsigned l = 1; l <= _nLayers; ++l)
            {
                _d[l] = values[l];
                _weights[l] = Matrix(_d[l - 1], std::vector<float>(_d[l], 1));

                //mat(d[l - 1] + 1, d[l], fill::randn);
            }
    
        }
        
}


void NeuralNetwork::train(Matrix inputs, std::vector<int> tags){

    int nodes = 400;
    int x_n = 3;


    // Añadimos 1, a los inputs para utilizar en el producto del bias
    for(int i = 0; i < inputs.size(); i++){
        std::vector<float>::iterator it = inputs[i].begin();
        inputs[i].insert( it , 1.0 );
    }


    // foward propagation

    Matrix W1 = Math::createRandMatrix(nodes, x_n);
    Matrix W2 = Math::createRandMatrix(1, nodes);

    // la transpuesta de tags? tiene sentido?
    inputs = Math::T(inputs);

    Matrix z1 = Math::dot(W1, inputs);
    Matrix A1 =  Math::sigmoid(z1);

    Matrix z2 = Math::dot(W1, A1);
    Matrix A2 =  Math::sigmoid(z2);


    // backPropagation
    
    


}