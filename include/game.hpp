#pragma once

#include "renderer.hpp"

class Game {

   public:
      int init();
      void run();
      void terminate();
   private:
      Renderer renderer;

      void processInput();
      
};
