#include "shader.hpp"

ShaderProgram::ShaderProgram(std::string vertexShaderArg, std::string fragmentShaderArg) {
   this->vertexShaderFile = vertexShaderArg;
   this->fragmentShaderFile = fragmentShaderArg;
}

int ShaderProgram::init() {

}

ShaderProgram::~ShaderProgram() {
}
