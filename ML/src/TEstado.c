#include "../include/TEstado.h"

TEstado::~TEstado()
{}

TEstado::TEstado() 
{}

void TEstado::addVector(float x){
    this -> _x.push_back(x);
}