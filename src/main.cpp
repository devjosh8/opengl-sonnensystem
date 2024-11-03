#include "game.hpp"


int main() {
   Game game;

   if(game.init()) {
      game.run();
   }

   game.terminate();

   return 0;
}
