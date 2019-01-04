
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






int main()
{


  srand (time(NULL));



	vector<point> D;




   TEntrenar trainData;
    trainData.LeerData("datos.csv");

	trainData.print();




vector<vector<float>> inputs(trainData.estados.size());
vector<int> tags;
int nBadPoints = 40;


int c1 = 0;

for(int i = 0; i < trainData.estados.size(); i++ ){

	//if(trainData.estados[i]._teclaAbajo != 1){
		
		inputs[i] = trainData.estados[i]._x;
		cout << inputs[i] << endl;
		tags.push_back(trainData.estados[i]._teclaArriba);

		if(tags[i] == 1){
			c1++;
		}
		cout << tags[i] << endl;
	



}


cout << "nº Total de Samples: " << tags.size() << endl;
cout << "n1: " << c1 << endl;








Perceptron test(inputs);
int contador = 20;

	while(contador--){
		test.info();

		cout << "Tasa de Error: " <<  test.train(inputs, tags) << endl;

		int TotalOkey = 0;
		for(int i= 0; i < inputs.size(); i++){
		//	cout << "claisifcando " << endl;

			if(test.classify(inputs[i]) == tags[i]){
			TotalOkey++;

			}


		}


		cout << "BIEN CLASIFICADOS: " << TotalOkey <<endl;


		test.info();
	}


	return 0;
}



