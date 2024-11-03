#include "renderer.hpp"
#include "defines.hpp"
#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int Renderer::init() {
   window = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE, NULL, NULL); 
   if(window == NULL) {
      std::cout << "GLFW Window konnte nicht erstellt werden!" << std::endl;
      return 0;
   }
   
   glfwMakeContextCurrent(window);
   return 1;
}

unsigned int vbo, vao;
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  
void Renderer::post_init() {
   glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);

   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);

   glBindVertexArray(vao);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
}

void Renderer::render() {
   glfwSwapBuffers(window);

   glBindVertexArray(vao);


   glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
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

