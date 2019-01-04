#pragma once

#include <vector>
#include "TEstado.h"

class TEntrenar
{

public:
    
    std::vector<TEstado> estados;

public:

    TEntrenar();
    ~TEntrenar();

    bool LeerData(string filename);
    void print();

};