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
   
   activate_mouse(false);

   return 1;
}

Planet sun;
Planet mercury;
Planet venus;
Planet earth;
Planet mars;
Planet jupiter;
Planet saturn;
Planet uranus;
Planet neptune;

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


   float rot_speed_scale = 1.0f;
   float sun_distance = 0.0f;

   // Planet; Color,                         Radius,        Rotation-Speed,   Bahn-Radius, Eigen-Rotation 
   sun.    init(glm::vec3(1.0f, 1.0f, 0.0f),    2.5f,    0.000f * rot_speed_scale, 0.0f + sun_distance,      4.0f);
   mercury.init(glm::vec3(0.64f, 0.66f, 0.64f), 0.19f,   4.140f * rot_speed_scale, 5.8f + sun_distance,      120.0f);
   venus.  init(glm::vec3(1.0f, 1.0f, 0.94f),   0.475f,  1.620f * rot_speed_scale, 10.8f + sun_distance,     120.0f);
   earth.  init(glm::vec3(0.09f, 0.57f, 0.61f), 0.5f,    1.000f * rot_speed_scale, 15.0f + sun_distance,     100.0f);
   mars.   init(glm::vec3(0.69f, 0.36f, 0.12f), 0.26f,   0.530f * rot_speed_scale, 22.8f + sun_distance,     100.0f);
   jupiter.init(glm::vec3(0.5f, 0.35f, 0.14f),  5.5f,    0.083f * rot_speed_scale, 77.9f + sun_distance,     100.0f);
   saturn .init(glm::vec3(0.58f, 0.56f, 0.0f),  4.58f,   0.034f * rot_speed_scale, 143.0f + sun_distance,    100.0f);
   uranus .init(glm::vec3(0.83f, 0.98f, 1.0f),  1.82f,   0.012f * rot_speed_scale, 280.0f + sun_distance,    100.0f);
   neptune.init(glm::vec3(0.38f, 0.62f, 0.91f), 1.78f,   0.006f * rot_speed_scale, 451.5f + sun_distance,    100.0f);

   // Rotationsspeed: 5.0f = 365 Tage
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
   mercury.render(&defaultShader);
   venus.render(&defaultShader);
   mars.render(&defaultShader);
   jupiter.render(&defaultShader);
   saturn.render(&defaultShader);
   uranus.render(&defaultShader);
   neptune.render(&defaultShader);

   glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
   glStencilMask(0x00);
   // glDisable(GL_DEPTH_TEST);
   
   glClear(GL_DEPTH_BUFFER_BIT);

   outlineShader.use(); 
   update_matrices(view, &outlineShader); 
   sun.render_scale(&outlineShader, 1.02f);
   earth.render_scale(&outlineShader, 1.06f);
   mercury.render_scale(&outlineShader, 1.08f);
   venus.render_scale(&outlineShader, 1.05f);
   mars.render_scale(&outlineShader, 1.08f);
   jupiter.render_scale(&outlineShader, 1.02f);
   saturn.render_scale(&outlineShader, 1.025f);
   uranus.render_scale(&outlineShader, 1.03f);
   neptune.render_scale(&outlineShader, 1.03f);
   

   glStencilMask(0xFF);
   glStencilFunc(GL_ALWAYS, 0, 0xFF);
   // glEnable(GL_DEPTH_TEST);


   glfwSwapBuffers(window);
}

void Renderer::update_matrices(glm::mat4 view, ShaderProgram* program_to_update) {
   glm::mat4 projection = glm::mat4(1.0f);

   projection = glm::perspective(glm::radians(CAM_FOV), (float)game_width / (float)game_height, 0.1f, 1000.0f);
   
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

void Renderer::activate_mouse(bool activate) {
   glfwSetInputMode(window, GLFW_CURSOR, activate ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
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

