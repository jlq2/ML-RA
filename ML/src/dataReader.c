#include "../include/dataReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

dataReader::dataReader(string dataSet){

    Matrix X_Dirty;

    std::ifstream xFile;
    xFile.open(dataSet.c_str());

    if (xFile.is_open()){
        
        std::vector<float> v;

        std::string line;
        std::string token;

    //Rellenamos el array con los valores de juego de datos.csv
        while (std::getline(xFile, line) )
        {
            std::stringstream ss(line);
            
            v.push_back(1);

            while (getline(ss,token, ','))
            {
                v.push_back(std::stof(token));
            }

             X_Dirty.push_back(v); 
             v.clear();
        }
            
    }else{
        std::cout << "No encuentra " << dataSet << std::endl;
    }

    int nFeactures = X_Dirty[0].size();

    cout  << "\n\n\nNumero de feactures " << nFeactures << endl;
    for(int i = 0; i < X_Dirty.size(); i++){
        _X.push_back(vector<float>() );
        _Y.push_back(vector<int>() );

        for(int j = 0; j < nFeactures - 1 ; j++){
           _X[i].push_back(X_Dirty[i][j]);  
        }

        if(X_Dirty[i][nFeactures - 1] == 0){
            _Y[0].push_back(0);

        }else{
            _Y[0].push_back(1);

        }

     //   for(int i = 0; i < _Y.size(); i++){
   //     cout << _Y[0][i] << endl;//}
    }

    cout << "*** Terminando de leer el archivo: " << dataSet << endl;
}


dataReader::dataReader(string fileX, string fileY, bool equi, int SIDE){

    _equi = equi;

    Matrix X_Dirty;
    vector<vector<int>> Y_Dirty  = vector<vector<int>>(2);


    std::ifstream xFile;
    xFile.open(fileX.c_str());

    if (xFile.is_open()){
        
        std::vector<float> v;

        std::string line;
        std::string token;

    //Rellenamos el array con los valores de juego de datos.csv
        while (std::getline(xFile, line) )
        {
            std::stringstream ss(line);
            
            v.push_back(1);

            while (getline(ss,token, ','))
            {
                v.push_back(std::stof(token));
            }

             X_Dirty.push_back(v); 
             v.clear();
        }
            
    }else{
        std::cout << "No encuentra " << fileX << std::endl;
    }


    std::ifstream yFile;
    yFile.open(fileY.c_str());

    if (yFile.is_open()){
        
        std::vector<int> v;

        std::string line;
        std::string token;

    //Rellenamos el array con los valores de juego de datos.csv
        while (std::getline(yFile, line) )
        {
            std::stringstream ss(line);

           int it = 0;

           //FIX ME CONST CHANGE TO VAR 2


            while (getline(ss,token, ','))
            {
                
                Y_Dirty[it].push_back(std::stof(token));
                it++;
               // v.push_back();
            }

            // Y_Dirty.push_back(v); 
            // v.clear();
        }
            
    }else{
        std::cout << "No encuentra " << fileY << std::endl;
    }

    if(_equi){
       // srand(time(NULL));

        // cantida de datos, izq 
        int IZQ = 0;

            _Y = vector<vector<int>>( 2 ) ;
        int cantidadSide = 0;
        for(int i = 0; i<Y_Dirty[SIDE].size(); i++){
            if(Y_Dirty[SIDE][i] == 1){
                cantidadSide++;
                _X.push_back( X_Dirty[i] ); 
                _Y[SIDE].push_back( Y_Dirty[SIDE][i] );

            }
        }

        cout << "Cantidad de entradas" << Y_Dirty.size() << "\n";
        cout << "Cantidad de SIDE " << cantidadSide << endl;


        int random;
        
        //Metemos la misma canditda dde los otros RANDOM
        while(cantidadSide){
            random = rand()%X_Dirty.size();
            if(Y_Dirty[SIDE][random] == 0){
                cantidadSide--;
                _X.push_back( X_Dirty[random] ); 
                _Y[SIDE].push_back( Y_Dirty[SIDE][random] );

            }
        }

    }else{
         _Y = Y_Dirty;
        _X = X_Dirty;
    }   

}

