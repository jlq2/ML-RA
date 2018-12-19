
#include <stdio.h>
#include "include/gfx.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>


using namespace std;


class point{
	public:
	point(int x, int y, int label){
		_x = x;
		_y = y;
		_label = label;
	}

	void draw(){
		if(_label == 1){
			//rojo
				gfx_color(200,0,0);

		}else{
			//verde
				gfx_color(0,200,100);

		}

		gfx_circle(_x,_y);
	}
	

	float _x = 0;
	float _y = 0;

	int _label = 0;

};









int main()
{

 // srand (time(NULL));
  srand (5);
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

		int label = -1;
		if(x  > y+100){
			label = 1;
		}
		D.push_back(point(x,y, label));
	} 

	//Draw DataSet





	gfx_line(0,0,50,300);






	gfx_color(0,0,250);
	int xx = 200;
	int yy = 10;



	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}



	return 0;
}



