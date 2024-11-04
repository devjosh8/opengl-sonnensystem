#include "shader.hpp"
#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <iostream>

static std::string read_file(std::string filename) {
   std::ifstream to_read(filename);
   if(to_read.fail()) {
      std::cout << "ERROR: Ressourcen Datei für Shader " << filename << " konnte nicht gefunden werden!" << std::endl;
      return "";
   }
   std::stringstream buffer;
   buffer << to_read.rdbuf();
   return buffer.str();
}

static void get_shader_error(int id) {
   int success;
   char infoLog[512];
   glGetShaderiv(id, GL_COMPILE_STATUS, &success);
   if(!success) {
      glGetShaderInfoLog(id, 512, NULL, infoLog);
      std::cout << "SHADER COMPILATION ERROR:\n" << infoLog << std::endl;
   }
}

static void get_program_error(int id) {
   int success;
   char infoLog[512];
   glGetProgramiv(id, GL_COMPILE_STATUS, &success);
   if(!success) {
      glGetProgramInfoLog(id, 512, NULL, infoLog);
      std::cout << "SHADER-PROGRAM COMPILATION ERROR:\n" << infoLog << std::endl;
   }
}

int ShaderProgram::init(std::string vertexShaderArg, std::string fragmentShaderArg) {
   
   vertexShaderFile = vertexShaderArg;
   fragmentShaderFile = fragmentShaderArg;

   std::string vertex_shader_source = read_file(vertexShaderFile);
   std::string fragment_shader_source = read_file(fragmentShaderFile);

   const char* vertex_shader_source_c = vertex_shader_source.c_str();
   const char* fragment_shader_source_c = fragment_shader_source.c_str();

   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertex_shader_source_c, NULL);
   glCompileShader(vertexShader);
   get_shader_error(vertexShader);

   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragment_shader_source_c, NULL);
   glCompileShader(fragmentShader);
   get_shader_error(fragmentShader);

   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);
   get_program_error(shaderProgram);

   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   
   return 1;
}

void ShaderProgram::use() {
   glUseProgram(shaderProgram);
}

unsigned int ShaderProgram::getLocation(const char* string) {
   return glGetUniformLocation(shaderProgram, string);
}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(shaderProgram);
}
