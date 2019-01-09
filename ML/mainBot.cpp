////////////////////////////////////////////////////
////////////////////////////////////////////////////
// TEST BOT ALE
////////////////////////////////////////////////////
////////////////////////////////////////////////////


//C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//C++
#include <vector>
#include <iostream>
using namespace std;


#include "include/gfx.h"
#include "./include/Perceptron.h"
#include "./include/dataReader.h"

#define SIDE 0 // 0 izquieda	1 derecha


int main()
{
	dataReader data("csv/inputs.csv", "csv/tags.csv", false, SIDE);

	Perceptron perceptron(data._X);
	int contador = 20;

	std::cout << "\n\n";
	std::cout << "====================================" << endl;
	std::cout << "=  BOT ALE                         =" << endl;
	std::cout << "====================================" << endl;

	std::cout << "\n%% Pulsa una tecla para empezar a entrenar... %%";
	std::cin.get();

	while(contador--){
						
		float tasaError = perceptron.train(data._X, data._Y[SIDE]);

		cout << "Tasa de Error: " << tasaError  << endl;
		int TotalOkey = 0;
		for(int i= 0; i < data._X.size(); i++){
			if(perceptron.classify( data._X[i]) == data._Y[SIDE][i]){
				TotalOkey++;
			}
		}

		cout << "BIEN CLASIFICADOS: " << TotalOkey <<endl;

		perceptron.info();

		cout << endl;
	}

	return 0;
}