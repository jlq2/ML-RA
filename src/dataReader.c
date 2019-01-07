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

    cout  << "Numero de feactures " << nFeactures << endl;
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


        for(int i = 0; i < _Y.size(); i++){
        cout << _Y[0][i] << endl;


        }
    }

cout << "FIN" << endl;
}


dataReader::dataReader(string fileX, string fileY, bool equi){

    _equi = equi;

    Matrix X_Dirty;
    vector<vector<int>> Y_Dirty;

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

           
            while (getline(ss,token, ','))
            {
                v.push_back(std::stof(token));
            }

             Y_Dirty.push_back(v); 
             v.clear();
        }
            
    }else{
        std::cout << "No encuentra " << fileY << std::endl;
    }




    if(_equi){
        srand(time(NULL));

        // cantida de datos, izq 
        int IZQ = 0;


        int cantidadSide = 0;
        for(int i = 0; i<Y_Dirty.size(); i++){
            if(Y_Dirty[i][IZQ] == 1){
                cantidadSide++;
                _Y.push_back(Y_Dirty[i]);
                _X.push_back( X_Dirty[i] ); 

            }
        }

        cout << "Cantidad de entradas" << Y_Dirty.size() << "\n";
        cout << "Cantidad de SIDE " << cantidadSide << endl;


        int random;
        //Metemos la misma canditda dde los otros RANDOM
        for(int i = 0; i < cantidadSide; i++ ){
            random = rand()%X_Dirty.size();
            _Y.push_back(Y_Dirty[random]);
            _X.push_back( X_Dirty[random] ); 
        }

    }

}

