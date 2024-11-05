#include "sphere.hpp"
#include "glad/glad.h"
#include "glm/ext/vector_float3.hpp"
#include <cmath>
#include <math.h>


void Sphere::init(float radius) {
   int sectorCount = 36;
   int stackCount = 18;
   float PI = M_PI; 
   float x, y, z, xy;                              // vertex position
   float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal

   float sectorStep = 2 * PI / sectorCount;
   float stackStep = PI / stackCount;
   float sectorAngle, stackAngle;

   for(int i = 0; i <= stackCount; ++i)
   {
       stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
       xy = radius * cosf(stackAngle);             // r * cos(u)
       z = radius * sinf(stackAngle);              // r * sin(u)

       // add (sectorCount+1) vertices per stack
       // first and last vertices have same position and normal, but different tex coords
       for(int j = 0; j <= sectorCount; ++j)
       {
           sectorAngle = j * sectorStep;           // starting from 0 to 2pi

           // vertex position (x, y, z)
           x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
           y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
           vertices.push_back(x);
           vertices.push_back(y);
           vertices.push_back(z);
            
           nx = x * lengthInv;
           ny = y * lengthInv;
           nz = z * lengthInv;


           vertices.push_back(nx);
           vertices.push_back(ny);
           vertices.push_back(nz);
       }
   }

   int k1, k2;
   for(int i = 0; i < stackCount; ++i)
   {
       k1 = i * (sectorCount + 1);     // beginning of current stack
       k2 = k1 + sectorCount + 1;      // beginning of next stack

       for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
       {
           // 2 triangles per sector excluding first and last stacks
           // k1 => k2 => k1+1
           if(i != 0)
           {
               indices.push_back(k1);
               indices.push_back(k2);
               indices.push_back(k1 + 1);
           }

           // k1+1 => k2 => k2+1
           if(i != (stackCount-1))
           {
               indices.push_back(k1 + 1);
               indices.push_back(k2);
               indices.push_back(k2 + 1);
           }
       }
   }


   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glGenBuffers(1, &ebo);

   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sphere::render() {
   glBindVertexArray(vao);
   glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
}
