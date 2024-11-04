#pragma once

#include <string>

class ShaderProgram {

   public:
      int init(std::string vertexShaderArg, std::string fragmentShaderArg);
      void use();
      unsigned int getLocation(const char* string);
      virtual ~ShaderProgram();

   private:
      std::string vertexShaderFile;
      std::string fragmentShaderFile;
      unsigned int fragmentShader, vertexShader;
      unsigned int shaderProgram;
};
