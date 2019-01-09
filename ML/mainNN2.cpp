
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <iostream>
#include <vector>

#include "include/gfx.h"
#include <Perceptron.h>
#include <neuralNetwork.h>

using namespace std;



// "Ancho" de la parábola
float f_a = 0.01f;
// Centro de la parábola
int f_h = 200;
// y = ax2 + bx + c
int f(int x){
	return 0.01 * (x-f_h)*(x-f_h);
}

void dibujar_parabola(const vector<point>& p_parabola)
{
	gfx_color(255, 255, 0);
	for (auto &p : p_parabola){
		gfx_cross(p._x,p._y);
	}
}

int solution(int x,vector<float> W){
	return  - (W[1]/W[2] )*x -W[0]/W[2] ;
}

int main()
{
	srand (time(NULL));
	int ysize = 400;
	int xsize = 400;
	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Perceptron");

	 
	/////////////////////////////////////////////////////////
	vector<point> parabola;
	int aux_x = 0;
	int aux_y = 0;

	// Dar f_h puntos de la parábola
	for (int i = 0; i < f_h; ++i)
	{
		// Punto a la derecha de la parabola
		aux_x = f_h+i+1;
		aux_y = f(aux_x);
		parabola.push_back(point(aux_x, aux_y, -99));
		// Punto a la izquierda de la parabola
		aux_x = f_h-i;
		aux_y = f(aux_x);
		parabola.push_back(point(aux_x, aux_y, -99));
	}

	// Dibujar los puntos de la parabola
	dibujar_parabola(parabola);
	/////////////////////////////////////////////////////////

	//generateDAtaSET
	vector<point> D;

	cout << "GEnerando DAtaSet" << endl;
	for(int i = 0; i < 440; i++){
		int x = rand() % 400 + 1;
  		int y  = rand() % 400 + 1;
		int label = 0;
		if(f(x) < y ){
		 	label = 0;

		}else{
			label = 1;

		}
		D.push_back(point(x,y, label));
	} 

	//Draw DataSet
	for(int i= 0; i < D.size(); i++){
		D[i].draw();
	}


	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	vector<vector<int>> etiquetas;
	vector<vector<float>> datos;
	for (point p : D)
	{
		etiquetas.push_back({p._label});
		datos.push_back({p._x,p._y});
	}

	//Matrix X {{0,0},{0,1},{1,0},{1,1}};
	Matrix X(datos);
	//Matrix Y {{0},{1},{1},{0}};
	Matrix Y(etiquetas);
	
    srand (time(0));

	NeuralNetwork nn = NeuralNetwork();

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
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	char c;
	while(1) {
		gfx_flush();
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}

	return 0;
}



