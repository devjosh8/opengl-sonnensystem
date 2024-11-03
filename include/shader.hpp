#pragma once

#include <string>

class ShaderProgram {

   public:
      ShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile);
      int init();
      void use();
      virtual ~ShaderProgram();

   private:
      std::string vertexShaderFile;
      std::string fragmentShaderFile;
};
