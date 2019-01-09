
#include <stdio.h>
#include <unistd.h>


#include "include/gfx.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>

#include "../include/neuralNetwork.h"


using namespace std;









int main()
{
	srand(time(0));

	uint32_t myFloat[1];
	myFloat[0] = 1;

	uint32_t myFloat2[1];
	myFloat2[0] = 0xFFFFFF;

	cout << (float)Math::mixBits(myFloat,myFloat2, 16) << endl;

	NeuralNetwork nn = NeuralNetwork();

	Matrix X { {0,0},{0,1},{1,0},{1,1}};
	Matrix Y { {0},{1},{1},{0}};

	for(int i=0; i<2; i++){
		nn.trainGenetic(X,Y);
	}

	return 0;
	/////////// XOR  test sintetico

	// Creamos los datos de entrada
	/*Matrix X { {0,0},{0,1},{1,0},{1,1}};
	Matrix Y { {0},{1},{1},{0}};

    srand (time(0));
	


	
	NeuralNetwrk nn = NeuralNetwork();*/

	try {
	int w = 40000;
	while(w--){
		cout << "------"<< w << "------" << endl;
	int rIndex = rand() % X.size();

	Matrix x_rand = Matrix();
			x_rand.push_back(X[rIndex]);

	Matrix y_rand = Matrix();
			y_rand.push_back(Y[rIndex]);



		nn.train(x_rand,y_rand);
	}	


	} catch (const std::exception& e) { // reference to the base of a polymorphic object
		std::cout << e.what(); // information from length_error printed
	}

	cout << "predict {0,0} -> 0 | " << nn.predict({ {0,0}}) << endl;
	cout << "predict {0,1} -> 1 | " << nn.predict({ {0,1}}) << endl;
	cout << "predict {1,0} -> 1 | " << nn.predict({ {1,0}}) << endl;
	cout << "predict {1,1} -> 0 | " << nn.predict({ {1,1}}) << endl;



	return 0;
}



