#include "renderer.hpp"
#include "cube.hpp"
#include "glm/ext/vector_float3.hpp"
#include "planet.hpp"
#include "defines.hpp"
#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "sphere.hpp"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static int game_width, game_height;

int Renderer::init() {
   game_width = GAME_WIDTH;
   game_height = GAME_HEIGHT;
   window = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE, NULL, NULL); 
   if(window == NULL) {
      std::cout << "GLFW Window konnte nicht erstellt werden!" << std::endl;
      return 0;
   }
   
   glfwMakeContextCurrent(window);

   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   return 1;
}

Planet sun;
Planet earth;

void Renderer::post_init() {
   glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);
   glEnable(GL_DEPTH_TEST);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   shader_program.init("res/vertexshader.txt", "res/fragmentshader.txt");
   
   sun.init(glm::vec3(1.0f, 1.0f, 0.0f), 2.0f, 0.0f, 0.0f, 50.0f);
   earth.init(glm::vec3(0.0f, 1.0f, 0.0f), 0.5f, 50.0f, 10.0f, 120.0f);
}

void Renderer::render(glm::mat4 view) {
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   shader_program.use();

   glm::mat4 model      = glm::mat4(1.0f);
   glm::mat4 projection = glm::mat4(1.0f);

   projection = glm::perspective(glm::radians(CAM_FOV), (float)game_width / (float)game_height, 0.1f, 100.0f);
   
   unsigned int viewLoc = shader_program.getLocation("view");
   glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
   unsigned int projectionLoc = shader_program.getLocation("projection");
   glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
   
   
   sun.render(&shader_program);
   earth.render(&shader_program);

   glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
   game_width = width;
   game_height = height;
}


void Renderer::closeWindow() {
   glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Renderer::windowShouldClose() {
   return glfwWindowShouldClose(window);
}

bool Renderer::key_pressed(int key) {
   return glfwGetKey(window, key);
}

void Renderer::set_mouse_callback(GLFWcursorposfun func) {
   glfwSetCursorPosCallback(window, func);
}

