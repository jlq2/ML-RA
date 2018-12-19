#ifndef __TESTADO_H_
#define __TESTADO_H_
#include <vector>

class TEstado
{
    public:
    std::vector<double> _x;
    double _kLeft;
    double _kRight;
    double _kFire;

    public:
        TEstado();
        ~TEstado();

        void addVector(double);
        
};


#endif