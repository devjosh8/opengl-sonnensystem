#pragma once

#include "renderable.hpp"

class Cube : Renderable {
   public:
      void init();
      void render();

   private: 
      static float vertices[24];
      static unsigned int indices[36];
};

