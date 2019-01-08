#pragma once

#include "SDL/SDL.h"
#include <fstream>      // std::ofstream

#include <iostream>
#include <string>
class ScreenWrapper  {
private:

public:


Uint8 *keystate;

  //  ScreenWrapper();
    void handleSDLEvent(){
            
        keystate = SDL_GetKeyState(NULL);
        if ( keystate[SDLK_ESCAPE] )  exit(0);
    }




    // Escribir entrada teclado
    void guardar_teclado(uint8_t *ram){

        std::ofstream data("salida.csv",std::ofstream::out | std::fstream::app);
        if (!data.is_open()) {
            std::cout << "failed to open " << "salida.csv" << '\n';
        } else {
           // std::cout <<  "Escribir en el fichero" << std::endl;

            data   << (bool)keystate[SDLK_LEFT] << "," 
            << (bool)keystate[SDLK_RIGHT] << "," << (bool)keystate[SDLK_SPACE] << ","  << (int)*(ram + 0x15) << 
             "," << (int)*(ram + 0x07) <<  "," << (int)*(ram + 0x08) <<  "," << (int)*(ram + 0x09) << "," << "0" <<"\n";
            
            
        }

    }







};
