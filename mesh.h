
#include <glm/glm.hpp>

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  class Mesh {

    int vertices, triangles;
    glm::uvec3 *ttable;
    glm::vec3* vtable;
    glm::vec3 *tnormals;
    glm::vec3 *vnormals;
    glm::ivec3 *atable;
    glm::vec3 bbox[2];
    glm::vec3 center;
    float bboxdiam;
    float bboxmaxdim;

  public:
  
    Mesh ( const char *name );
    ~Mesh();

    const glm::uvec3 *getTriangleTable();
    const glm::vec3 *getVertexTable();
    const glm::vec3 *getTriangleNormals();
    const glm::vec3 *getVertexNormals();
    const glm::ivec3 *getAdjacencyTable();

    glm::vec3 getUpperCorner();
    glm::vec3 getLowerCorner();
    glm::vec3 getCenter();
    float getDiameter();
    float getMaxDim();
    int getTriangleCount();
    int getVertexCount();
    
  };
  
  /* ------------------------------------------- */
  
};
