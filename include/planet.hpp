#include "glm/ext/vector_float3.hpp"
#include "shader.hpp"
#include <sphere.hpp>


class Planet {

   public:
      void init(glm::vec3 color, float radius, float rotation_speed, float bahn_radius, float own_rotation_speed);
      void render(ShaderProgram* program);
      void render_scale(ShaderProgram* program, float scale);
      void render_with_scaled_outline(ShaderProgram* program, float scale);
      

   private:
      glm::vec3 color;
      float radius;
      float rotation_speed;
      float bahn_radius;
      float own_rotation_speed;
      Sphere sphere;
};
