#pragma once

#include "renderable.hpp"
#include <vector>

class Sphere : Renderable {
   public:
      void init(float radius);
      void render();

   private: 
      std::vector<float> vertices;
      std::vector<unsigned int> indices;
      std::vector<float> normals;
};

