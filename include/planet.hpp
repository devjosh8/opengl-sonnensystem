#include "glm/ext/vector_float3.hpp"
#include "shader.hpp"
#include <sphere.hpp>


class Planet {

   public:
      void init(glm::vec3 color, float radius, float rotation_speed, float bahn_radius, float own_rotation_speed);
      void render(ShaderProgram* program);

   private:
      glm::vec3 color;
      float radius;
      float rotation_speed;
      float bahn_radius;
      float own_rotation_speed;
      Sphere sphere;
};
