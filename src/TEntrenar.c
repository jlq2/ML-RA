#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
#include "../include/TEntrenar.h"



TEntrenar::~TEntrenar()
{}
TEntrenar::TEntrenar() 
{}

/*void TEntrenar::Add(TEstado x){

}*/



void TEntrenar::print(){
    for(int j=0; j< estados.size(); j++){
    cout << "_teclaArriba: " << estados[j]._teclaArriba << "_teclaAbajo" << estados[j]._teclaAbajo << endl;

        for(int i=0; i< estados[j]._x.size(); i++) {
            cout << "x"<< i<<": " << estados[j]._x[i] << " ";
        }

        cout << endl << endl;
    }

}



bool 
TEntrenar::LeerData(string filename)
{
    typedef enum {
        s_jugadorVY = 0,
        s_enemigoYRel,
        s_enemigoVY,
        s_pelotaXRel,
        s_pelotaYRel,
        s_pelotaVX, 
        s_pelotaVY,
        s_teclaArriba, // Salida
        s_teclaAbajo,  // Salida
        s_N_EstadosJuego
} SEstadoJuego;

    float vEstadoJuego[s_N_EstadosJuego];
    std::ifstream file;
    file.open(filename.c_str());

    if (file)
    {

        std::vector<float> v;

        std::string line;
        std::string token;


    //Rellenamos el array con los valores de juego de datos.csv
        while (std::getline(file, line) )
        {
            std::stringstream ss(line);

            while (getline(ss,token, ';'))
            {
                v.push_back(std::stof(token));
            }
        }
        
    //Vamos a calcular el estado de juego para un tiempo definido

        cout << "nº de tokens = " << v.size() << endl;
        for(int i=0; i<v.size(); i++){
            TEstado x;

            //Cantidad de elementos del estado. 7 + 2
                         x.addVector(1);

            for(int j=0; j<s_N_EstadosJuego-2; j++){
                //cout << v[i+j] << endl;
                 x.addVector(v[i+j]);
            }
            x._teclaArriba = v[i + s_N_EstadosJuego-2];
            x._teclaAbajo = v[i + s_N_EstadosJuego-2 + 1];

            if(x._teclaArriba == 0 && x._teclaAbajo == 0){
                //continue;
            }

            estados.push_back(x);
            i += s_N_EstadosJuego-1;
        }

            print();


        std::cout << "Total de slots" << estados.size() << std::endl;
    
    }else
    {
        std::cout << "No encuentra datos.csv" << std::endl;
    }

    return false;
}