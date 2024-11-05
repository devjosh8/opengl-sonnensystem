#pragma once

#include "defines.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer.hpp"
#include <GLFW/glfw3.h>


class Game {

   public:
      int init();
      void run();
      void terminate();
   private:
      Renderer renderer;

      void processInput(double delta);
      static void mouse_callback(GLFWwindow* window, double xpos, double ypos);


      glm::vec3 camera_position;
      glm::vec3 camera_front;
      glm::vec3 camera_up;


};
