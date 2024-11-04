#pragma once

#include "renderable.hpp"

class Cube : Renderable {
   public:
      void init() override;
      void render() override;

   private: 
      static float vertices[24];
      static unsigned int indices[36];
};

