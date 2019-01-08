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

        std::ofstream inputs("inputs.csv",std::ofstream::out | std::fstream::app);
        std::ofstream tags("tags.csv",std::ofstream::out | std::fstream::app);

        if (!inputs.is_open() || !tags.is_open()) {
            std::cout << "failed to open " << "salida.csv" << '\n';
        } else {
           // std::cout <<  "Escribir en el fichero" << std::endl;

            
            int player_x = (int)*(ram + 72);
            int ball_x = (int)*(ram + 99);
            int ball_y = (int)*(ram + 101); 
            int diff = ball_x - player_x;

            if(ball_x == 80 || ball_x == 0){
                return;
            }
            //inputs  << player_x <<  "," << ball_x <<  "," << ball_y <<  "," << diff << "\n";
            inputs  << diff <<  "\n";
            tags   << (bool)keystate[SDLK_LEFT] << ","  << (bool)keystate[SDLK_RIGHT] << "\n";

            // inputs << Player_X  << Ball_X << Ball_y << diff = Ball_x - Player_X 
            
        }

    }







};
