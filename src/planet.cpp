#include "planet.hpp"
#include "glad/glad.h"
#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>

void Planet::init(glm::vec3 color, float radius, float rotation_speed, float bahn_radius, float own_rotation_speed) {
   this->color = color;
   this->radius = radius;
   this->rotation_speed = rotation_speed;
   this->bahn_radius = bahn_radius;
   this->own_rotation_speed = own_rotation_speed;
   sphere.init(radius);
}

void Planet::render_with_scaled_outline(ShaderProgram* program, float scale) {
   glm::mat4 model      = glm::mat4(1.0f);
   
   model = glm::rotate(model, glm::radians(rotation_speed) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
   model = glm::translate(model, glm::vec3(bahn_radius, 0.0f, 0.0f)); 
   model = glm::rotate(model, glm::radians(own_rotation_speed) * (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
   model = glm::scale(model, glm::vec3(1.0f + radius / scale, 1.0f + radius / scale, 1.0f + radius / scale)); 
   glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model)));

   unsigned int modelLoc = program->getLocation("model");
   glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
   sphere.render();
   //glUniform3f(program->getLocation("input_color"), color.x, color.y, color.z);
}

void Planet::render_scale(ShaderProgram* program, float scale) {
   glm::mat4 model      = glm::mat4(1.0f);
   
   model = glm::rotate(model, glm::radians(rotation_speed) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
   model = glm::translate(model, glm::vec3(bahn_radius, 0.0f, 0.0f)); 
   model = glm::rotate(model, glm::radians(own_rotation_speed) * (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
   model = glm::scale(model, glm::vec3(scale, scale, scale)); 
   glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model)));

   unsigned int modelLoc = program->getLocation("model");
   glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
   
   //unsigned int normalmodelLoc = program->getLocation("model_normal");
   //glUniformMatrix3fv(normalmodelLoc, 1, GL_FALSE, glm::value_ptr(normal_matrix));


   glUniform3f(program->getLocation("input_color"), color.x, color.y, color.z);
   sphere.render();
}

void Planet::render(ShaderProgram* program) {
   glm::mat4 model      = glm::mat4(1.0f);
   
   model = glm::rotate(model, glm::radians(rotation_speed) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
   model = glm::translate(model, glm::vec3(bahn_radius, 0.0f, 0.0f)); 
   model = glm::rotate(model, glm::radians(own_rotation_speed) * (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
   
   glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model)));

   unsigned int modelLoc = program->getLocation("model");
   glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
   
   unsigned int normalmodelLoc = program->getLocation("model_normal");
   glUniformMatrix3fv(normalmodelLoc, 1, GL_FALSE, glm::value_ptr(normal_matrix));


   glUniform3f(program->getLocation("input_color"), color.x, color.y, color.z);
   sphere.render();
}
