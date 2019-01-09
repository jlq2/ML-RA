
////////////////////////////////////////////////////
////////////////////////////////////////////////////
// TEST SINTÉTICO PARA EL PERCEPTRON
////////////////////////////////////////////////////
////////////////////////////////////////////////////

#include <unistd.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <Perceptron.h>
#include "../include/gfx.h"

using namespace std;


////////////////////
const int NUM_DATOS = 500;
// Alto y ancho de la ventana gfx
const int ysize = 400;
const int xsize = 400;

/////////////////////////////////////////////////////////
// Recta para generar el DataSet a ambos las de la recta
/////////////////////////////////////////////////////////
int f(int x){
	return (2*x)-150;
}
/////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////
int solution(int x,vector<float> W){
	return  - (W[1]/W[2] )*x -W[0]/W[2] ;
}


/////////////////////////////////////////////////////////
//  Test Sintético Perceptron
/////////////////////////////////////////////////////////
int main()
{
	srand (time(NULL));

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Perceptron");
	// Set the current drawing color to green.
	gfx_color(0,0,250);

	// DataSet
	vector<point> D;
	// Generar el DataSet
	cout << "\n\n**** Generando DataSet *** \n\n" << endl;
	
	// Coordenadas del punto
	int x = 0;
	int y = 0;
	// Clasificación
	int label = 0;
	for(int i = 0; i < NUM_DATOS; i++){
		// calcular X e Y del punto
		x = rand() % 400 + 1;
  		y  = rand() % 400 + 1;
		// Asignar clasificación
		if(f(x) < y ){
		 	label = 0;
		}else{
			label = 1;
		}
		D.push_back(point(x,y, label));
	} 

	// Dibujar los puntos del DataSet
	for(int i= 0; i < D.size(); i++){
		D[i].draw();
	}


	vector<vector<float>> inputs(D.size());
	vector<int> tags;
	int nBadPoints = 40;

	// Generamos unos puntos bien clasificados
	for(int j=0; j< D.size() - nBadPoints; j++){
		inputs[j].push_back(1 )  ;
		inputs[j].push_back(D[j]._x );
		inputs[j].push_back(D[j]._y );
		tags.push_back(D[j]._label);
	}

	// A continuacion generamos ruido para ver como se comporta el perceptron
	for(int j=D.size() - nBadPoints; j < D.size(); j++){
		inputs[j].push_back(1)  ;
		inputs[j].push_back(D[j]._x );
		inputs[j].push_back(D[j]._y );
		(bool)D[j]._label ? D[j]._label  = 0: D[j]._label = 1 ; 
		tags.push_back(D[j]._label) ;
	}

	int x1 = 0;
	int x2 = 400;

	Perceptron test(inputs);
	
	std::cout << "==============================" << endl;
	std::cout << "=  TEST SINTETICO PERCEPTRON =" << endl;
	std::cout << "==============================" << endl;

	std::cout << "Puntos a clasificar : " << NUM_DATOS << endl;
	std::cout << "Función Solucion F  : (2*x)-150" << endl;
	std::cout << "Ancho en pixels 	  :" << xsize << endl;
	std::cout << "Alto en pixels  	  :" << ysize << "\n\n";

	std::cout << "%% Pulsa una tecla para empezar a entrenar... %%";
	std::cin.get();

	int contador = 100;
	while(contador--){
		usleep(600);
		gfx_clear();

		cout << "Train ==> 		" << 100 - contador << endl;
		cout << "Tasa de Error: " <<  test.train(inputs, tags) << endl;
		gfx_line(x1,solution(x1,test._bestW),x2,solution(x2,test._bestW));

		//cout << solution(x1,test.bestW) << " 	" << solution(x2,test.bestW) << endl;

		int TotalOkey = 0;
		for(int i= 0; i < D.size(); i++){
			TotalOkey += D[i].check(test.classify(D[i].toVector()));
		}

		cout << "BIEN CLASIFICADOS: " << TotalOkey << endl;
		test.info();
		std::cout << "\n";

		gfx_color(0,0,250);
		gfx_line(x1,f(x1),x2,f(x2));
		gfx_color(0,250,0);
	}

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



