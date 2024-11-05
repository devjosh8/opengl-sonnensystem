#pragma once

#include "renderable.hpp"

class Quad : Renderable {
   public:
      void init();
      void render();

   private: 
      static float vertices[12];
      static unsigned int indices[6];
};
