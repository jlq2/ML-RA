#include <iostream>
#include <cmath>
#include "./lib/ALE/src/ale_interface.hpp"
#include "include/screen_wrapper.hpp"

#include <vector>

#include <algorithm>


using namespace std;


#define MAQ0   0
#define MAQ1   1
//#define MAQ2   2

// Global vars
const int maxSteps = 7500;
int lastLives;
float totalReward;
ALEInterface alei;

const int s_kinputs = 2; 
double vEstadoJuego[s_kinputs];



double s_w[2][s_kinputs] = {
    {67, -8}
   , {-155, 30}
};


float progress = 0.0;

inline void endian_swap(byte_t& x)
{
    x = (x>>4) | 
        (x<<4);
}


///////////////////////////////////////////////////////////////////////////////
/// PrintRam
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void printRam() {

    std::cout <<  "------------Ram------------ \n" << " %\r";
    std::cout << "*Address    *Hex dump \n";




    byte_t *ramPointer =  alei.getRAM().array();

    byte_t hero_x = *(ramPointer + 72);


   endian_swap(hero_x);
cout << hex << (int)hero_x <<endl ;


   /*                   Breakout
   POS_X_HERO = 15      Player_X = 72dec
   POS_X_ENM1 = 07      Ball_X = 99dec
   POS_X_ENM2 = 08      Ball_Y = 101dec
   POS_X_ENM3 = 09      diff
   */


   static std::vector<int> vector;

    int i = 0;

    int dirc = 0;
    printf("%02X  | ",  dirc);

   bool aux = false;

    while( i < alei.getRAM().size()){
        


       





       aux = std::find(vector.begin(), vector.end(), i) != vector.end(); 
      if(aux)
      {
         printf("\033[0;32m"); 
         printf("%02X ",  (int)(*ramPointer++)); 
         printf("\033[0m");
      }


      if(hero_x == *ramPointer){
         
         if (!aux){
            vector.push_back(i);

         }
         
         printf("%02X ",  (int)(*ramPointer++)); 
         
                 
      }else if(!aux){
         printf("\033[0;31m"); 
                 printf("%02X ",  (int)(*ramPointer++)); 
         printf("\033[0m");

      }
        i++;

        if(i%16 == 0){
            printf("\n");
            dirc += 15;
            if (dirc != 120)
                printf("%02X  | ",  dirc);
        }

    }

    
    printf("\n"); 

}




unsigned h(unsigned wn, const double* st) {
   double hval = 0;

   for(unsigned i=0; i < s_kinputs; i++)
      hval += st[i] * s_w[wn][i];

   return (hval > 0) ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////
/// Do Next Agent Step
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Print usage and exit
///////////////////////////////////////////////////////////////////////////////
void usage(char* pname) {
   std::cerr
      << "\nUSAGE:\n" 
      << "   " << pname << " <romfile>\n";
   exit(-1);
}

///////////////////////////////////////////////////////////////////////////////
/// MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
   // Check input parameter
   if (argc != 2)
      usage(argv[0]);

   // Create alei object.
   alei.setInt("random_seed", 0);
   alei.setFloat("repeat_action_probability", 0);
   alei.setBool("display_screen", true);
   alei.setBool("sound", true);
   alei.loadROM(argv[1]);

   // Init
   srand(time(NULL));
   lastLives = alei.lives();
   totalReward = .0f;




ScreenWrapper manager;
//std::cout << (ScreenWrapper*)other->getChar() << std::endl; 
   // Main loop

   
    byte_t *ram =  alei.getRAM().array();


   bool ML = true;

   bool save = false;

   int step;
   for (step = 0;  true; ++step) {

   
         if(ML){

            vEstadoJuego[0] = 1;
          //  vEstadoJuego[1] = (int)*(ram + 72);
          //  vEstadoJuego[2] = (int)*(ram + 99);
           // vEstadoJuego[3] = (int)*(ram + 101);
            vEstadoJuego[1] = (int)*(ram + 99)-(int)*(ram + 72);

            unsigned left = h(MAQ0, vEstadoJuego);
            unsigned right = h(MAQ1, vEstadoJuego);

            //unsigned fire = h(MAQ2, vEstadoJuego);

            if      ( left && !right)  alei.act(PLAYER_A_LEFT);  
            else if (!left &&  right)  alei.act(PLAYER_A_RIGHT);

            if(lastLives--){
               alei.act(PLAYER_A_FIRE);
            }


         }else{
            printf("\033c");
            printRam();


            manager.handleSDLEvent();

            if(manager.keystate[SDLK_LEFT]) { // move left
               alei.act(PLAYER_A_LEFT);
      save = true;
            }else if(manager.keystate[SDLK_RIGHT]) { // move right
               alei.act(PLAYER_A_RIGHT);
save = true;   
            }else{
               save = false;    


            }


            if(manager.keystate[SDLK_SPACE]) { // move right
               alei.act(PLAYER_A_FIRE);
               save = true;

            }


            alei.act(PLAYER_A_NOOP);

            if(lastLives == alei.lives()-1 ){
               lastLives--;
               save = false;    
               }

            if(save){
                manager.guardar_teclado(alei.getRAM().array());
            }

         }



      


   }

   

   std::cout << "Steps: " << step << std::endl;
   std::cout << "Reward: " << totalReward << std::endl;



   return 0;
}
