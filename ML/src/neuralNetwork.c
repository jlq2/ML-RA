#include "../include/neuralNetwork.h"
#include <math.h>       /* tanh, log */
#include <utility>      // std::pair, std::make_pair

NeuralNetwork::NeuralNetwork(int _nodes, int _batch){
        nodes = _nodes;
        m = _batch;

         population = 20;

    cout << "Creating NeuralNetwork.. " << endl;

         W1 = Math::createRandMatrix(nodes, 2);
         b1 = Math::createMatrix(nodes, m);
    //cout << "seco matrix.. " << endl;

         W2 = Math::createRandMatrix(1, nodes);
         b2 = Math::createMatrix(1, m);

   // cout << "group matrix.. " << endl;


        pop_W1 = vector<Matrix>(population); 
        pop_b1 = vector<Matrix>(population);

        pop_W2 = vector<Matrix>(population);
        pop_b2 = vector<Matrix>(population);

        for(int i= 0; i<population ; i++){
            pop_W1[i] = Math::createRandMatrix(nodes, 2);
            pop_b1[i] = Math::createRandMatrix(nodes, m);

            pop_W2[i] = Math::createRandMatrix(1, nodes);
            pop_b2[i] = Math::createRandMatrix(1, m);
        }
    //cout << "end builder.. " << endl;


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

void NeuralNetwork::train(Matrix inputs, Matrix tags,int it){
   // printM(inputs);
   // printM(tags);


    // la transpuesta de tags? tiene sentido?
    inputs = Math::T(inputs);
    tags = Math::T(tags);
    //cout << "creatin matrix.. " << endl;




  //  cout << "Start.. " << endl;
    for(int i=0; i<it; i++){
        // foward propagation
        // cout << "Foward Propagation" << endl;

        //cout << "   Layer 1" << endl;
        Matrix z1 = Math::add( Math::dot(W1, inputs),b1);
        Matrix A1 =  Math::sigmoid(z1);

        //cout << "   Layer 2" << endl;
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



            /*if (i % 19 == 0) {
                    cout << "==============" << endl;
                    cout << "Predictions = ";
                    //printM(A2);

            }*/
    }

}


void NeuralNetwork::trainGenetic(Matrix inputs, Matrix tags){

    //Algoritmo genetico

    vector<float> fitnesGroup(population);

    for(int i = 0; i < population; i++){
        fitnesGroup[i] = fitness(inputs, tags, i);
        cout << "----" << i << " " << fitnesGroup[i] << endl;
    }

    cout << "fitness end" << endl;

  std::pair <int,double> bestFit(0,99);                   
  std::pair <int,double> sbestFit(0,99);                   

    for(int i = 0; i < population; i++){

        if( fitnesGroup[i]  < sbestFit.second ){
            if(fitnesGroup[i] < bestFit.second){
                //el primero al segundo y actualizamos primero
                sbestFit =bestFit;
                bestFit =   std::pair <int,double>(i,fitnesGroup[i] );
            }else{
                 sbestFit =   std::pair <int,double>(i,fitnesGroup[i] );
        
            }

        }

    }

    cout << bestFit.first << " " <<  bestFit.second <<  endl;
    cout << sbestFit.first << " " <<  sbestFit.second << endl;

    cout << pop_W1[bestFit.first][0][0] << endl;



    vector<Matrix> parent  = {pop_W1[bestFit.first],pop_b1[bestFit.first],pop_W2[bestFit.first], pop_b2[bestFit.first] };
    vector<Matrix> parent2 = {pop_W1[sbestFit.first],pop_b1[sbestFit.first],pop_W2[sbestFit.first], pop_b2[sbestFit.first] };

pop_W1.clear();
pop_b1.clear();

pop_W2.clear();
pop_b2.clear();

    cout << "crossover" << endl;
    //crossover
        // Population veces para generar una poblacion nueva
        for(int i = 0; i < population; i++){

            vector<Matrix> child;
            //4 veces, w1 b1 ,w2 b2
            for(int j = 0; j < parent.size(); j++){

                Matrix mat(parent[j].size());
                //ancho y alto
                for(int x = 0; x < parent[j].size(); x++){
                    for(int y = 0; y < parent[j][x].size(); y++){

                        float nW ; 

                        float myFloat[1];
                        myFloat[0] = parent[j][x][y];
                        
                        float myFloat2[1];
                        myFloat2[0] = parent2[j][x][y];

                        // nW = Math::mixBits((uint32_t*)myFloat2, (uint32_t*)myFloat, rand() % 31 );

                        nW = (myFloat[0] + myFloat2[0]) + (rand() % 100) /100 ;

                        if(2 >= rand()%100){
                           //   nW = rand()%1000 - 500;

                        }
                        mat[x].push_back(nW);

                    }
                }
                
                
                //cout << "mat1 " << parent[j].size() << "x" << parent[j][0].size() << endl;
                //cout << "mat2 " << mat.size() << "x" << mat[0].size() << endl;;
                child.push_back(mat);
               // cout << "mat3 " << child[child.size() - 1].size() << "x" << child[child.size() - 1][0].size() << endl;;

            }


            pop_W1.push_back( child[0]); 
            pop_b1.push_back( child[1]); 
            pop_W2.push_back( child[2]); 
            pop_b2.push_back( child[3]); 

           // cout << "mat " <<     pop_W1[i].size() << "x" <<     pop_W1[i][0].size() << endl << endl;;


        }


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



float NeuralNetwork::fitness(Matrix inputs, Matrix tags, int index){
  // cout << "----predict" << endl;
    inputs = Math::T(inputs);
    tags = Math::T(tags);
   // cout << "creatin matrix.. " << endl;

//cout << "sizeFitnes" << index << ": "  << pop_b1[index].size() << endl;
  //    cout << "   Layer 1" << endl;
    Matrix z1 = Math::add( Math::dot(pop_W1[index], inputs),pop_b1[index]);
    Matrix A1 =  Math::sigmoid(z1);

   //  cout << "   Layer 2" << endl;
    Matrix z2 =  Math::add( Math::dot(pop_W2[index], A1),pop_b2[index]);
    Matrix A2 =  Math::sigmoid(z2);

      //  cout << "A2 " << A2[0][0] << endl;

    float cost = Math::cross_entropy(m, tags, A2);

    return cost;
}


float NeuralNetwork::classify(vector<float> m){
  
    return predict( vector<vector<float>>({m}));
}


float NeuralNetwork::predict(Matrix mat){
    //cout << "----predict" << endl;
    //printM(mat);

    mat = Math::T(mat);

        //cout << "creatin matrix.. " << endl;

    //  cout << "   Layer 1" << endl;
    Matrix z1 = Math::add( Math::dot(W1, mat),b1);
    Matrix A1 =  Math::sigmoid(z1);

    //  cout << "   Layer 2" << endl;
    Matrix z2 =  Math::add( Math::dot(W2, A1),b2);
    Matrix A2 =  Math::sigmoid(z2);


    //printM(A2);
    return A2[0][0];
}


