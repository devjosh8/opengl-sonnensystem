#include "game.hpp"

#include <GLFW/glfw3.h>
#include <iostream>



int Game::init() {
   std::cout << "Sonnensystem wird gestartet!" << std::endl; 

   if(glfwInit() == GLFW_FALSE) {
      std::cout << "GLFW konnte nicht initialisiert werden!" << std::endl;
      return 0;
   }
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
   if(!renderer.init()) {
      std::cout << "Der Renderer konnte nicht initialisiert werden!" << std::endl;
      return 0;
   }

   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "GLAD konnte nicht initialisiert werden!" << std::endl;
      return 0;
   }
   renderer.post_init();

   return 1;
}

void Game::run() {
   
   while(!renderer.windowShouldClose()) {
      processInput();

      renderer.render();
      glfwPollEvents();
   }
}

void Game::processInput() {
   if(renderer.key_pressed(GLFW_KEY_ESCAPE)) {
      renderer.closeWindow(); 
   }
}

void Game::terminate() {
   glfwTerminate();   
}

