#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <utility>      // std::pair, std::make_pair
#include <unordered_map>
#include "../include/Math.h"


using namespace std;




template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{ 
    os << "["; 
    for (int i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    os << "]"; 
    return os; 
} 
  


float operator*(const vector<float>& v1, const vector<float>& v2)
{
    float sum = 0;
    if(v1.size() != v2.size()){
        sum;
    }

    for(int i= 0; i < v1.size(); i++){
        sum += v1[i] * v2[i];
    }

    return sum;
}



vector<float> operator*(const vector<float>& v1, const float constNumber)
{
    vector<float> ret(v1.size());

    for(int i= 0; i < v1.size(); i++){
       ret[i] = v1[i]* constNumber;
    }

    return ret;
}

vector<float> operator+=( vector<float>& v1, const vector<float>& v2)
{

    if(v1.size() != v2.size()){
        throw 20;
        return vector<float>(0);
    }

    for(int i= 0; i < v1.size(); i++){
       v1[i] += v2[i] ;
    }

    return v1;
}





class point{
	public:
	point(int x, int y, int label){
		_x = x;
		_y = y;
		_label = label;
	}

    vector<float> toVector(){
        vector<float> vec(3);
        vec[0] = 1;
        vec[1] = _x;
        vec[2] = _y;

        return vec;
    }

	int check(int tag){
        int ret = 0;
		if(_label == tag){
			//verde
			gfx_color(0,200,100);
            ret = 1;
		}else{
			//rojo
			gfx_color(200,0,0);
		}



        if(_label == 1){
        gfx_cross(_x,_y);

        }else{
            gfx_circle(_x,_y);

        }

        return ret;
	}

	void draw(){
		if(_label == 1){
			//rojo
				gfx_color(200,0,0);
        gfx_cross(_x,_y);

		}else{
			//verde
				gfx_color(0,200,100);
		gfx_circle(_x,_y);

		}

	}
	

	float _x = 0;
	float _y = 0;

	int _label = 0;

};


class Perceptron{
    public:


        vector<float> W;
        vector<float> bestW;
            float bestError = 9999;

        
        int activation(float sum){
            return sum  >= 0 ? 1 : 0;

        }


        Perceptron(Matrix inputs){
            W = vector<float>(inputs[0].size()  );
            srand (time(0));

            W = W * 0.0f ;
            W[0] =  1;


        }


        int classify( vector<float> x){
                return activation(bestW* x);
            

        }


        void info(){
            cout << W << endl;
        }

        //devolver la tasa de error tras entrenar
        float train(Matrix inputs, vector<int> tags){

            vector<int> bad;
            std::unordered_map<int,int> last_classification;


            for(int j= 0; j < 100000; j++){


                for(int i= 0; i < inputs.size(); i++ ){
                    vector<float> x = inputs[i];

                    int classficiation = activation(W * x);

                //cout << "classficiation" << classficiation << endl;
                //cout << "tags" << tags[i] << endl;
 
                    if( classficiation != tags[i]){
                        bad.push_back(i);
                        last_classification[i] = classficiation;
                    }

                } 
                
                cout << "mal clasificados: " << bad.size() << endl;

                if (bad.size() == 0){
                    bestError = 0;
                    bestW = W;

                    break;
                } 

                float error = (float)bad.size() / (float)inputs.size();
                
                if(error < bestError){
                    bestError = error;
                    bestW = W;

                    if (bestError == 0) break;
                }


                int randomIndex = bad[rand() % bad.size()];

                W +=  inputs[randomIndex] * (tags[randomIndex]- activation(W * inputs[randomIndex] ) );


                bad.clear();
                last_classification.clear();


            }

            return bestError;



        }





};