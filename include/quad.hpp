#pragma once

#include "renderable.hpp"

class Quad : Renderable {
   public:
      void init() override;
      void render() override;

   private: 
      static float vertices[12];
      static unsigned int indices[6];
};
