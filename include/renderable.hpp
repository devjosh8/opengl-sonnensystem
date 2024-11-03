#pragma once

class Renderable {
   
   public:
      virtual void init() = 0;
      virtual void render() = 0;

   
      unsigned int vao, vbo, ebo;
};
