#include "game.hpp"
#include "defines.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

bool first_mouse = true;
      float last_mouse_x;
      float last_mouse_y;
      float yaw, pitch;

int Game::init() {
   std::cout << "Sonnensystem wird gestartet!" << std::endl; 

   if(glfwInit() == GLFW_FALSE) {
      std::cout << "GLFW konnte nicht initialisiert werden!" << std::endl;
      return 0;
   }
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_STENCIL_BITS, 8);
   
   if(!renderer.init()) {
      std::cout << "Der Renderer konnte nicht initialisiert werden!" << std::endl;
      return 0;
   }

   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "GLAD konnte nicht initialisiert werden!" << std::endl;
      return 0;
   }

   renderer.post_init();
   renderer.set_mouse_callback(Game::mouse_callback);

   camera_position = glm::vec3(0.0f, 0.0f, 3.0f);
   camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
   camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
   last_mouse_x = GAME_WIDTH / 2.0f;
   last_mouse_y = GAME_HEIGHT / 2.0f;
   yaw = -90.0f;
   pitch = 0.0f;
   return 1;
}

void Game::run() {
   double current_time = glfwGetTime(); 
   while(!renderer.windowShouldClose()) {
      double delta = glfwGetTime() - current_time;
      current_time = glfwGetTime();

      processInput(delta);
   
      glm::mat4 view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
      glm::vec3 direction;
      direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
      direction.y = sin(glm::radians(pitch));
      direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
      camera_front = glm::normalize(direction);

      renderer.render(view);
      glfwPollEvents();
   }
}

void Game::processInput(double delta) {
   if(renderer.key_pressed(GLFW_KEY_ESCAPE)) {
      renderer.closeWindow(); 
   }
   float deltaf = (float)delta;
   if(renderer.key_pressed(GLFW_KEY_W)) {
      camera_position += camera_front * CAM_SPEED * deltaf;
   }
   if(renderer.key_pressed(GLFW_KEY_S)) {
      camera_position -= camera_front * CAM_SPEED * deltaf;
   }
   if(renderer.key_pressed(GLFW_KEY_A)) {
      camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * CAM_SPEED * deltaf;
   }
   if(renderer.key_pressed(GLFW_KEY_D)) {
      camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * CAM_SPEED * deltaf;
   }
   if(renderer.key_pressed(GLFW_KEY_SPACE)) {
      camera_position += camera_up * CAM_SPEED * deltaf;
   }
   if(renderer.key_pressed(GLFW_KEY_LEFT_SHIFT)) {
      camera_position -= camera_up * CAM_SPEED * deltaf;
   }
}

void Game::terminate() {
   glfwTerminate();   
}

void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
   if(first_mouse) {
      first_mouse = false;
      last_mouse_x = xpos;
      last_mouse_y = ypos;
   }
   float xoffset = xpos - last_mouse_x;
   float yoffset = last_mouse_y - ypos;

   last_mouse_x = xpos;
   last_mouse_y = ypos;

   yoffset *= CAM_SENSITIVITY;
   xoffset *= CAM_SENSITIVITY;

   yaw += xoffset;
   pitch += yoffset;

   if(pitch > 89.0f) pitch = 89.0f;
   if(pitch < -89.0f) pitch = -89.0f;
}

