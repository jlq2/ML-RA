#include "../include/neuralNetwork.h"
#include <math.h>       /* tanh, log */

NeuralNetwork::NeuralNetwork(){
         nodes = 8;
         m = 4;

         population = 20;



    cout << "creatin matrix.. " << endl;

         W1 = Math::createRandMatrix(nodes, 2);
         b1 = Math::createMatrix(nodes, m);
    cout << "seco matrix.. " << endl;

         W2 = Math::createRandMatrix(1, nodes);
         b2 = Math::createMatrix(1, m);

        vector<Matrix> pop_W1(population); 
        vector<Matrix> pop_b1(population);

        vector<Matrix> pop_W2(population); 
        vector<Matrix> pop_b2(population);

        for(int i= 0; i<population ; i++){
            pop_W1[i] = Math::createRandMatrix(nodes, 2);
            pop_b1[i] = Math::createMatrix(nodes, m);

            pop_W2[i] = Math::createRandMatrix(1, nodes);
            pop_b2[i] = Math::createMatrix(1, m);
        }


}


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


void printM(Matrix &mat){
        for(int j=0; j< mat.size(); j++){
            cout << "[ ";
            for(int w=0; w< mat[j].size(); w++){
                cout << mat[j][w] << " "  ;
            }  
            cout << "] " <<  endl;
        }
}

void NeuralNetwork::train(Matrix inputs, Matrix tags){
    printM(inputs);
    printM(tags);


    // la transpuesta de tags? tiene sentido?
    inputs = Math::T(inputs);
    tags = Math::T(tags);
    //cout << "creatin matrix.. " << endl;




  //  cout << "Start.. " << endl;
    for(int i=0; i<20; i++){
        // foward propagation
        // cout << "Foward Propagation" << endl;

        //    cout << "   Layer 1" << endl;
        Matrix z1 = Math::add( Math::dot(W1, inputs),b1);
        Matrix A1 =  Math::sigmoid(z1);

     //   cout << "   Layer 2" << endl;
        Matrix z2 =  Math::add( Math::dot(W2, A1),b2);
        Matrix A2 =  Math::sigmoid(z2);


        // backPropagation
        
        //Layer 2
        Matrix dZ2 = Math::sub(A2, tags);
        Matrix dW2 = Math::divide(Math::dot(dZ2, Math::T(A1) ), m );
        Matrix db2 = Math::divide(dZ2, m );

        //Layer 1
        Matrix dZ1 = Math::multiply(
            Math::dot( Math::T(W2), dZ2 ),
            Math::sub(1.0, Math::power(A1,2))
        );
        
        Matrix dW1 = Math::divide(Math::dot(dZ1, Math::T(inputs) ), m );
        Matrix db1 = Math::divide(dZ1, m );



        //Gradient desce
        W1 = Math::sub(W1, Math::multiply(0.01, dW1));
        b1 = Math::sub(b1, Math::multiply(0.01, db1));

        W2 = Math::sub(W2, Math::multiply(0.01, dW2));
        b2 = Math::sub(b2, Math::multiply(0.01, db2));



            if (i % 19 == 0) {
                    cout << "==============" << endl;
                    cout << "Predictions = ";
                    printM(A2);

            }
    }

}


void NeuralNetwork::trainGenetic(Matrix inputs, Matrix tags){

    //Algoritmo genetico

    

    //Create population
    //Loop
        //Evulate fitness of NN (with W_t)
        //create a nuew population
            //Pick parents, on fitness scores 
            // crossover
            //mutate


    //Input, samples to evalute fittnes of NN

    // W and bias are the population;


   /* printM(inputs);
    printM(tags);


    // la transpuesta de tags? tiene sentido?
    inputs = Math::T(inputs);
    tags = Math::T(tags);
    //cout << "creatin matrix.. " << endl;




  //  cout << "Start.. " << endl;
    for(int i=0; i<20; i++){
        // foward propagation
        // cout << "Foward Propagation" << endl;

        //    cout << "   Layer 1" << endl;
        Matrix z1 = Math::add( Math::dot(W1, inputs),b1);
        Matrix A1 =  Math::sigmoid(z1);

     //   cout << "   Layer 2" << endl;
        Matrix z2 =  Math::add( Math::dot(W2, A1),b2);
        Matrix A2 =  Math::sigmoid(z2);


        // backPropagation
        
        //Layer 2
        Matrix dZ2 = Math::sub(A2, tags);
        Matrix dW2 = Math::divide(Math::dot(dZ2, Math::T(A1) ), m );
        Matrix db2 = Math::divide(dZ2, m );

        //Layer 1
        Matrix dZ1 = Math::multiply(
            Math::dot( Math::T(W2), dZ2 ),
            Math::sub(1.0, Math::power(A1,2))
        );
        
        Matrix dW1 = Math::divide(Math::dot(dZ1, Math::T(inputs) ), m );
        Matrix db1 = Math::divide(dZ1, m );



        //Gradient desce
        W1 = Math::sub(W1, Math::multiply(0.01, dW1));
        b1 = Math::sub(b1, Math::multiply(0.01, db1));

        W2 = Math::sub(W2, Math::multiply(0.01, dW2));
        b2 = Math::sub(b2, Math::multiply(0.01, db2));



            if (i % 19 == 0) {
                    cout << "==============" << endl;
                    cout << "Predictions = ";
                    printM(A2);

            }
    }
*/
}



float NeuralNetwork::fitness(Matrix mat){
    //cout << "----predict" << endl;
    mat = Math::T(mat);

        //cout << "creatin matrix.. " << endl;

    //  cout << "   Layer 1" << endl;
    Matrix z1 = Math::add( Math::dot(W1, mat),b1);
    Matrix A1 =  Math::sigmoid(z1);

    //  cout << "   Layer 2" << endl;
    Matrix z2 =  Math::add( Math::dot(W2, A1),b2);
    Matrix A2 =  Math::sigmoid(z2);


    printM(A2);
    return A2[0][0];
}




float NeuralNetwork::predict(Matrix mat){
    //cout << "----predict" << endl;
    mat = Math::T(mat);

        //cout << "creatin matrix.. " << endl;

    //  cout << "   Layer 1" << endl;
    Matrix z1 = Math::add( Math::dot(W1, mat),b1);
    Matrix A1 =  Math::sigmoid(z1);

    //  cout << "   Layer 2" << endl;
    Matrix z2 =  Math::add( Math::dot(W2, A1),b2);
    Matrix A2 =  Math::sigmoid(z2);


    printM(A2);
    return A2[0][0];
}
