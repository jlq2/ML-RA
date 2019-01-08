
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
#include "./include/TEntrenar.h"
#include "./include/TEstado.h"
#include "./include/dataReader.h"

#define SIDE 0 // 0 izquieda	1 derecha


int main()
{
	dataReader data("inputs.csv", "tags.csv", false);

	//dataReader data("Sonar.csv");

	cout  << data._X << endl;
	cout  << data._Y << endl;

	Perceptron perceptron(data._X);
	int contador = 200;

	
//	cout  <<  data._Y[SIDE] << endl;

    cout << "--------------------------------------------------------" << endl;



	while(contador--){
		perceptron.info();
						
		float tasaError = perceptron.train(data._X, data._Y[SIDE])		;
											// IZQUIERDA


		cout << "Tasa de Error: " << tasaError  << endl;
		int TotalOkey = 0;
		for(int i= 0; i < data._X.size(); i++){
		//	cout << "claisifcando " << endl;
													// IZQUIERDA
			if(perceptron.classify( data._X[i]) == data._Y[SIDE][i]){
				TotalOkey++;

			}


		}


		cout << "BIEN CLASIFICADOS: " << TotalOkey <<endl;


		perceptron.info();
	}

	return 0;
}



