#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
   
   public:
      int init();
      void render(glm::mat4 view);
      void post_init();
      bool windowShouldClose();
      bool key_pressed(int key);
      void set_mouse_callback(GLFWcursorposfun func);

      void closeWindow();

   private:
      GLFWwindow* window;
      ShaderProgram shader_program;
};
