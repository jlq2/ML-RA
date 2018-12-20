
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
	// f(x) = x
	// y = 2*x +150
	return (2*x)-150;
}


int solution(int x,vector<float> W){
	// f(x) = x
	// y = 2*x +150
	return  - (W[1]/W[2] )*x -W[0]/W[2] ;
}


int main()
{

  srand (time(NULL));
 // srand (5);
	int ysize = 400;
	int xsize = 400;

	char c;
	// Open a new window for drawing.


	gfx_open(xsize,ysize,"Perceptron");

	// Set the current drawing color to green.

	vector<point> D;
	//generateDAtaSET

	cout << "GEnerando DAtaSet" << endl;
	for(int i = 0; i < 400; i++){
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


/**********/
	int x1 = 0;
	int x2 = 400;
	gfx_line(x1,f(x1),x2,f(x2));


				gfx_color(0,0,250);
	//gfx_line(x1,solution(x1),x2,solution(x2));




vector<vector<float>> inputs(D.size());

vector<int> tags;



for(int j=0; j< D.size(); j++){

	inputs[j].push_back(1 *  0.5)  ;
	inputs[j].push_back(D[j]._x * 0.5);
	inputs[j].push_back(D[j]._y * 0.5);
	tags.push_back(D[j]._label);


}


for(int j=0; j< D.size(); j++){

	cout << inputs[j][0] << " "; 
	cout << inputs[j][1] << " ";
	cout << inputs[j][2] << " ";
	cout << tags[j] << endl;
}



Perceptron test(inputs);




int contador = 100;

while(contador--){
	
		// Wait for the user to press a character.
		//c = gfx_wait();



usleep(300);
gfx_clear();
test.info();

cout << "Tasa de Error: " <<  test.train(inputs, tags) << endl;
gfx_line(x1,solution(x1,test.bestW),x2,solution(x2,test.bestW));

cout << solution(x1,test.bestW) << " 	" << solution(x2,test.bestW) << endl;

int TotalOkey = 0;
	for(int i= 0; i < D.size(); i++){
		TotalOkey += D[i].check(test.classify(D[i]));

	}


cout << "BIEN CLASIFICADOS: " << TotalOkey <<endl;
	gfx_line(x1,f(x1),x2,f(x2));

test.info();



}




//		gfx_circle(390,100);

	while(1) {
		gfx_flush();
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}



	return 0;
}



