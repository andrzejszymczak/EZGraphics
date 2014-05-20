#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  /** a simple triangle mesh class */
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
    /** Constructor: read a mesh from a .t file.
	The first two number in the file are triangle count (T) and vertex count (V). Vertices are labelled with integers between 0 and N-1. Next part of the file is the triangle table, i.e. a collection of triples of integer IDs; each triple defines a mesh triangle. FInally, the vertex coordinates are listed (as 3 floats per vertex). All numbers are assumed to be separated by white spaces.
	\param name is the file name */
    Mesh ( const char *name );

    /** destructor... */
    ~Mesh();

    /** \return the triangle table, as an array of uvec3's; the size of the array is T */
    const glm::uvec3 *getTriangleTable();

    /** \return the vertex table, an array of V vec3's */
    const glm::vec3 *getVertexTable();

    /** \return the triangle normals, an array of T vec3's */
    const glm::vec3 *getTriangleNormals();

    /** \return area-weighted vertex normals, an array of V vec3's */
    const glm::vec3 *getVertexNormals();

    /** \return Adjacency table, an array of T ivec3's. If the i-th entry of the triangle table is a_0 a_1 a_2 (i.e. vertices of triangle #i have labels a_0 a_1 a_2) and A is the return value then A[i][j] is the ID of the triangle adjacent to triangle #i opposite to vertex a_j if there is exactly one such triangle; otherwise, it is -1 */
    const glm::ivec3 *getAdjacencyTable();

    /** \return a vec3 with each coordinate equal to the maximum value of that coordinate over all mesh vertices */
    glm::vec3 getUpperCorner();

    /** \return a vec3 with each coordinate equal to the minimum value of that coordinate over all mesh vertices */
    glm::vec3 getLowerCorner();

    /** \return 0.5*(getLowerCorner()+getUpperCorner()), i.e. the center of the axis-oriented bounding box */ 
    glm::vec3 getCenter();

    /** \return the diameter of the bounding box, or distance between getLowerCorner() and getUpperCorner() */
    float getDiameter();

    /** \return maximum dimension of the bounding box,i.e. the maximum coordinate of getUpperCorner()-getLowerCorner() */
    float getMaxDim();

    /** \return the number of triangles */
    int getTriangleCount();

    /** \return the number of vertices */
    int getVertexCount();
    
  };
  
  /* ------------------------------------------- */
  
};
