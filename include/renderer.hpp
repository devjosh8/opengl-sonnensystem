#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
   
   public:
      int init();
      void render();
      void post_init();
      bool windowShouldClose();
      bool key_pressed(int key);


      void closeWindow();

   private:
      GLFWwindow* window;
};
