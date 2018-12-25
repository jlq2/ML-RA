#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <utility>      // std::pair, std::make_pair
#include <unordered_map>


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
    os << "]\n"; 
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
        return vector<float>(0);
    }

    for(int i= 0; i < v1.size(); i++){
       v1[i] += v2[i];
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
		gfx_circle(_x,_y);

        return ret;
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


class Perceptron{
    public:


        vector<float> W;
        vector<float> bestW;
            float bestError = 9999;

        
        int activation(float sum){
            return sum  < 0 ? 0 : 1;

        }


        Perceptron(vector<vector<float>> inputs){
            W = vector<float>(inputs[0].size()  );
                                      srand (time(0));

            W[0] =  rand() % 400 - 400;
            W[1] = 0;
            W[2] = 0;

        }


        int classify(point p){
            if(bestW.size() != 0){
            float total;

            float r1 = bestW[1] * p._x;
            float r2 = bestW[2] * p._y;

            total = r1 + r2 + bestW[0] ;
            return activation(total);

            }

            return -2; 

        }


        void info(){
            

            cout << W << endl;

        }

        //devolver la tasa de error tras entrenar
        float train(vector<vector<float>> inputs, vector<int> tags){
            vector<int> bad;
            vector<int> badTags;
          //  vector<int> last_classification;
            std::unordered_map<int,int> last_classification;


            for(int j= 0; j < 10000; j++){


                for(int i= 0; i < inputs.size(); i++ ){
                    vector<float> x = inputs[i];

                    int classficiation = activation(W * x);

                    if( classficiation != tags[i]){
                        bad.push_back(i);
                        last_classification[i] = classficiation;
                    }

                } 
                
                cout << "mal clasificados: " << bad.size() << endl;

                if (bad.size() == 0) break;

                float error = (float)bad.size() / (float)inputs.size();
                
                if(error < bestError){
                    bestError = error;
                    bestW = W;

                    if (bestError == 0) break;
                }


                int randomIndex = rand() % bad.size();
                randomIndex = bad[randomIndex];
                    //cout <<  tags[randomIndex] << endl;

                    W += inputs[randomIndex] * (tags[randomIndex]-last_classification[randomIndex]);


                    //W[1] += inputs_mult_tag[1];
                   // W[2] += inputs_mult_tag[2];
                   // W[0] += inputs_mult_tag[0];

                    //W[1] +=  inputs[randomIndex][1] * (tags[randomIndex]-last_classification[randomIndex]) ;
                    //W[2] +=  inputs[randomIndex][2] * (tags[randomIndex]-last_classification[randomIndex]) ;
                    //W[0] +=  inputs[randomIndex][0] * (tags[randomIndex]-last_classification[randomIndex]) ;


                bad.clear();
                last_classification.clear();

            }

            return bestError;



        }





};