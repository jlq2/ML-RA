#ifndef __TESTADO_H_
#define __TESTADO_H_
#include <vector>

class TEstado
{
    public:
        std::vector<float> _x;
    float _teclaArriba;
    float _teclaAbajo;
    public:
        TEstado();
        ~TEstado();

        void addVector(float);
        
};


#endif