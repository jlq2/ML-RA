////////////////////////////////////////////////////
////////////////////////////////////////////////////
// TEST PERCEPTRON con los datos Iris.csv
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
	dataReader data("./csv/Iris.csv");

	//cout  << data._X << endl;

	Perceptron perceptron(data._X);

	std::cout << "==============================" << endl;
	std::cout << "=  TEST PERCEPTRON - Iris.csv=" << endl;
	std::cout << "==============================" << endl;

	std::cout << "Puntos a clasificar: " << data._X.size() << endl;

	std::cout << "%% Pulsa una tecla para empezar a entrenar... %%";
	std::cin.get();

	int contador = 20;
	while(contador--){
		perceptron.info();

		
		float tasaError = perceptron.train(data._X, data._Y[SIDE]);
		cout << "Train ==> 	" << 20 - contador << endl;
		cout << "Tasa de Error: " << tasaError  << endl;

		int TotalOkey = 0;
		for(int i= 0; i < data._X.size(); i++){
		//	cout << "claisifcando " << endl;
			if(perceptron.classify( data._X[i]) == data._Y[SIDE][i]){
				TotalOkey++;
			}
		}

		cout << "BIEN CLASIFICADOS: " << TotalOkey << endl;
		perceptron.info();
		std::cout << "\n";
		
	}
	
	return 0;
}



