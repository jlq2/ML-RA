
#include <stdio.h>
#include <unistd.h>


#include "include/gfx.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <Perceptron.h>
#include <vector>

#include "../include/neuralNetwork.h"


using namespace std;


int main()
{
	/////////// XOR  test sintetico

	// Creamos los datos de entrada
	Matrix X { {0,0},{0,1},{1,0},{1,1}};
	Matrix Y { {0},{1},{1},{0}};

	std::cout << "\n\n";
	std::cout << "====================================" << endl;
	std::cout << "=  TEST SINTETICO RED NEURONAL_XOR =" << endl;
	std::cout << "====================================" << endl;

	std::cout << "\n%% Pulsa una tecla para empezar a entrenar... %%";
	std::cin.get();

    srand (time(0));

	NeuralNetwork nn = NeuralNetwork(16,1);

	cout << "Training..." << endl;
	try {
		int w = 2000;
		while(w--){
		int rIndex = rand() % X.size();

		Matrix x_rand = Matrix();
		x_rand.push_back(X[rIndex]);

		Matrix y_rand = Matrix();
		y_rand.push_back(Y[rIndex]);

		nn.train(x_rand,y_rand,20);
	}	


	} catch (const std::exception& e) { // reference to the base of a polymorphic object
		std::cout << e.what(); // information from length_error printed
	}


	cout << "Test:" << endl;

	cout << "{0 xor 0} = 0  predict->| " << nn.predict({ {0,0}}) << endl;
	cout << "{0 xor 1} = 1  predict->| " << nn.predict({ {0,1}}) << endl;
	cout << "{1 xor 0} = 1  predict->| " << nn.predict({ {1,0}}) << endl;
	cout << "{1 xor 1} = 0  predict->| " << nn.predict({ {1,1}}) << endl;


	return 0;
}



