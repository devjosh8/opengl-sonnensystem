#include "renderer.hpp"
#include "cube.hpp"
#include "defines.hpp"
#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "quad.hpp"
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
   return 1;
}


Cube cube;

void Renderer::post_init() {
   glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);
   glEnable(GL_DEPTH_TEST);

   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


   shader_program.init("res/vertexshader.txt", "res/fragmentshader.txt");

   cube.init();
}

void Renderer::render() {
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   shader_program.use();

   glm::mat4 model      = glm::mat4(1.0f);
   glm::mat4 view       = glm::mat4(1.0f);
   glm::mat4 projection = glm::mat4(1.0f);

   model = glm::rotate(model, glm::radians(50.0f) * (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
   view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
   projection = glm::perspective(glm::radians(45.0f), (float)game_width / (float)game_height, 0.1f, 100.0f);
   
   unsigned int modelLoc = shader_program.getLocation("model");
   glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
   unsigned int viewLoc = shader_program.getLocation("view");
   glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
   unsigned int projectionLoc = shader_program.getLocation("projection");
   glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

   cube.render();

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

