#pragma once

#include "SDL/SDL.h"
#include "../lib/ALE/src/common/display_screen.h"
#include "../lib/ALE/src/ale_interface.hpp"

#include <iostream>

class Bot  {
private:
    SDLKey key;
    bool isKeyValid;
public:
    void checkKey(ScreenWrapper* screen){
        if(!isKeyValid = screen->keyPressed(key)){
            isKeyValid = screen->isKeyUP();
        }

    }



    void run(ALEInterface *alei){



    }



};
