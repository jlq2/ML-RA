#include "../include/Math.h"

    void  SetBit( uint32_t A[],  int k )
    {
         A[k/32] |= 1 << (k%32);  // Set the bit at the k-th position in A[i]
    }


    void  ClearBit( uint32_t A[],  int k ) {
          A[k/32] &= ~(1 << (k%32));
    }

    int TestBit( uint32_t A[],  int k ){
          return ( (A[k/32] & (1 << (k%32) )) != 0 ) ;     
    }


 float Math::mixBits(uint32_t n1[], uint32_t n2[], int point){
        

        // point tiene que ser de 0 a 31, ya que los float 
        //tiene un size de 32 bits no?
        uint32_t myFloat[1];
        myFloat[0] = 0;
        for(int i= 0; i < point; i++){
            if(TestBit(n1, i ) ){
                SetBit(myFloat, i );
                cout << "1";
            }else{
                ClearBit(myFloat, i );
                cout << "0" ;
            }
        }
    cout << endl;

        for(int i= point ; i < 32; i++){
            if(TestBit(n2, i ) ){
                SetBit(myFloat, i );
                                cout << "1";

            }else{
                ClearBit(myFloat, i );
                                cout << "0" ;

            }
        }
            cout << endl;


        return myFloat[0];

    }
