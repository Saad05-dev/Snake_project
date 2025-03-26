#include "Game.h"

int main()
{
    // Init Game engine
   Game game;

   // Game loop
   while (game.running())
   {
        //update
        game.update();

        //render
        game.render();
   }
   
    return 0;
}
