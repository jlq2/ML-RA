
#include <stdio.h>
#include <unistd.h>


#include "include/gfx.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <Perceptron.h>
#include <vector>
using namespace std;









int f(int x){
	return (2*x)-150;
}


int solution(int x,vector<float> W){
	return  - (W[1]/W[2] )*x -W[0]/W[2] ;
}





int main()
{


  srand (time(NULL));
 // srand (5);
	int ysize = 400;
	int xsize = 400;
	int x1 = 0;
	int x2 = 400;
	// Open a new window for drawing.


	gfx_open(xsize,ysize,"Perceptron");
	gfx_color(0,0,250);
	// Set the current drawing color to green.

	vector<point> D;
	//generateDAtaSET

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


/*
for(int j=0; j< D.size(); j++){

	cout << inputs[j][0] << " "; 
	cout << inputs[j][1] << " ";
	cout << inputs[j][2] << " ";
	cout << tags[j] << endl;
}
*/






Perceptron test(inputs);
int contador = 100;

	while(contador--){
		usleep(300);
		gfx_clear();
		test.info();

		cout << "Tasa de Error: " <<  test.train(inputs, tags) << endl;
		gfx_line(x1,solution(x1,test.bestW),x2,solution(x2,test.bestW));

		//cout << solution(x1,test.bestW) << " 	" << solution(x2,test.bestW) << endl;

		int TotalOkey = 0;
		for(int i= 0; i < D.size(); i++){
			TotalOkey += D[i].check(test.classify(D[i].toVector()));

		}


		cout << "BIEN CLASIFICADOS: " << TotalOkey <<endl;

		gfx_color(0,0,250);
		gfx_line(x1,f(x1),x2,f(x2));
		gfx_color(0,250,0);

		test.info();
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



