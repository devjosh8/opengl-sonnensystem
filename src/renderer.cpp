#include "renderer.hpp"
#include "glm/ext/vector_float3.hpp"
#include "planet.hpp"
#include "defines.hpp"
#include "glad/glad.h"
#include "shader.hpp"

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
   glDepthFunc(GL_LESS);
   glEnable(GL_STENCIL_TEST);
   glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
   glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   defaultShader.init("res/vertexshader.txt", "res/fragmentshader.txt");
   outlineShader.init("res/outlinevertex.txt", "res/outlinefragment.txt"); 
   sunShader.init("res/sunvertexshader.txt", "res/sunfragmentshader.txt");
   // Planet; Color, Radius, Rotation-Speed, Bahn-Radius, Eigen-Rotation 
   sun.init(glm::vec3(1.0f, 1.0f, 0.0f), 2.0f, 0.0f, 0.0f, 50.0f);
   earth.init(glm::vec3(0.0f, 1.0f, 0.0f), 0.5f, 5.0f, 5.0f, 120.0f);
}

void Renderer::render(glm::mat4 view) {
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   

   glStencilFunc(GL_ALWAYS, 1, 0xFF);
   glStencilMask(0xFF);

   sunShader.use();
   update_matrices(view, &sunShader);
   sun.render(&sunShader);
   defaultShader.use();
   update_matrices(view, &defaultShader);
   earth.render(&defaultShader);

   glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
   glStencilMask(0x00);
   glDisable(GL_DEPTH_TEST);

   outlineShader.use(); 
   update_matrices(view, &outlineShader); 
   sun.render_scale(&outlineShader, 1.02f);
   earth.render_scale(&outlineShader, 1.05f);
   

   glStencilMask(0xFF);
   glStencilFunc(GL_ALWAYS, 0, 0xFF);
   glEnable(GL_DEPTH_TEST);


   glfwSwapBuffers(window);
}

void Renderer::update_matrices(glm::mat4 view, ShaderProgram* program_to_update) {
   glm::mat4 projection = glm::mat4(1.0f);

   projection = glm::perspective(glm::radians(CAM_FOV), (float)game_width / (float)game_height, 0.1f, 100.0f);
   
   glUniform3f(program_to_update->getLocation("light_pos"), 0.0f, 0.0f, 0.0f);
   unsigned int viewLoc = program_to_update->getLocation("view");
   glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
   unsigned int projectionLoc = program_to_update->getLocation("projection");
   glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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

Renderer::~Renderer() {
   glfwDestroyWindow(window);
}
