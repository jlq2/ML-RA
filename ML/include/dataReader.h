#pragma once


#include <string>
#include <vector>
#include "../include/Math.h"

using namespace std;

class dataReader{
    public:
        Matrix _X;
        vector<vector<int>> _Y;
        bool _equi;
    
    public:
        dataReader(string fileX, string fileY, bool equi,int SIDE); 
        dataReader(string dataSet); 

};