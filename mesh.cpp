/*
 * EZGraphics: OpenGL object wrappers, GLUT tools and mesh data structures 
 * designed to simplify basic OpenGL programming
 * Copyright (c) 2014  Andrzej Szymczak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * ANDRZEJ SZYMCZAK BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 *
*/
#define GLM_FORCE_RADIANS
#include <mesh.h>
#include <fstream>
#include <glm/glm.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace glm;

namespace EZGraphics {

/* ------------------------------------------- */

Mesh::Mesh ( const char *name )
{
  ifstream ifs(name);
  if (!ifs)
    {
      cout << "Can't open file: " << name << endl;
      exit(1);
    }

  ifs >> triangles >> vertices;

  ttable = new uvec3[triangles];

  for ( int i=0; i<triangles; i++ )
    ifs >> ttable[i][0] >> ttable[i][1] >> ttable[i][2];

  vtable = new vec3 [vertices];

  for ( int i=0; i<vertices; i++ )
    {
      ifs >> vtable[i][0] >> vtable[i][1] >> vtable[i][2];
      if (!i)
	bbox[0] = bbox[1] = vtable[0];
      else
	{
	  for ( int j=0; j<3; j++ )
	    {
	      if (vtable[i][j]<bbox[0][j])
		bbox[0][j] = vtable[i][j];
	      if (vtable[i][j]>bbox[1][j])
		bbox[1][j] = vtable[i][j];
	    }
	}
    }
    
  center = 0.5f*(bbox[0]+bbox[1]);
  vec3 boxsize = bbox[1]-bbox[0];
  bboxmaxdim = glm::max(glm::max(boxsize[0],boxsize[1]),boxsize[2]);

  tnormals = NULL;
  vnormals = NULL;
  atable = NULL;
}

/* ------------------------------------------- */

Mesh::~Mesh()
{
  if (ttable) delete[] ttable;
  if (vtable) delete[] vtable;
  if (tnormals) delete[] tnormals;
  if (vnormals) delete[] vnormals;
  if (atable) delete[] atable;
}

/* ------------------------------------------- */


const glm::uvec3 *Mesh::getTriangleTable()
{
  return ttable;
}

/* ------------------------------------------- */

const glm::vec3 *Mesh::getVertexTable()
{
  return vtable;
}

/* ------------------------------------------- */

const glm::vec3 *Mesh::getTriangleNormals()
{
  if (tnormals) 
    return tnormals;
  tnormals = new vec3[triangles];
  for ( int i=0; i<triangles; i++ )
    tnormals[i] = cross(vtable[ttable[i][1]]-vtable[ttable[i][0]],
			      vtable[ttable[i][2]]-vtable[ttable[i][0]]);
  return tnormals;
}
  
/* ------------------------------------------- */

const glm::vec3 *Mesh::getVertexNormals()
{
  if (vnormals)
    return vnormals;
  if (!tnormals)
    getTriangleNormals();
  vnormals = new vec3[vertices];
  for ( int i=0; i<triangles; i++ )
    for ( int j=0; j<3; j++ )
      vnormals[ttable[i][j]] += tnormals[i];
  return vnormals;
}

/* ------------------------------------------- */

vec3 Mesh::getUpperCorner()
{
  return bbox[1];
}

/* ------------------------------------------- */

vec3 Mesh::getLowerCorner()
{
  return bbox[0];
}

/* ------------------------------------------- */

vec3 Mesh::getCenter()
{
  return center;
}

/* ------------------------------------------- */

float Mesh::getDiameter()
{
  return bboxdiam;
}

/* ------------------------------------------- */

float Mesh::getMaxDim()
{
  return bboxmaxdim;
}

/* ------------------------------------------- */

int Mesh::getVertexCount()
{
  return vertices;
}

/* ------------------------------------------- */

int Mesh::getTriangleCount()
{
  return triangles;
}

/* ------------------------------------------- */

  static bool _cmp_ivec4 ( const ivec4 &a, const ivec4 &b )
  {
    if (a[0]<b[0]) return true;
    if (a[0]>b[0]) return false;
    if (a[1]<b[1]) return true;
    if (a[1]>b[1]) return false;
    if (a[2]<b[2]) return true;
    if (a[2]>b[2]) return false;
    if (a[3]<b[3]) return true;
    return false;
  }

/* ------------------------------------------- */

const ivec3 *Mesh::getAdjacencyTable()
{
  atable = new ivec3[triangles];
  vector<ivec4> arr;
  for ( int i=0; i<triangles; i++ )
    for ( int j=0; j<3; j++ )
      {
	int a = ttable[i][(j+1)%3];
	int b = ttable[i][(j+2)%3];
	if (a>b) 
	  swap(a,b);
	arr.push_back(ivec4(a,b,i,j));
      }

  sort(arr.begin(),arr.end(),_cmp_ivec4);

  for ( vector<ivec4>::iterator i = arr.begin(); i!=arr.end(); )
    {
      if (i+1==arr.end() || (*i)[0]!=(*(i+1))[0] || (*i)[1]!=(*(i+1))[1])
	{
	  atable[(*i)[2]][(*i)[3]] = -1;
	  ++i;
	}
      else
	if (i+2!=arr.end() && (*i)[0]==(*(i+2))[0] && (*i)[1]==(*(i+2))[1])
	  {
	    do {
	      atable[(*i)[2]][(*i)[3]] = -1;
	      ++i;
	    }
	    while (i!=arr.end() && (*i)[0]==(*(i-1))[0] && (*i)[1]==(*(i-1))[1]);
	  }
	else
	  {
	    atable[(*i)[2]][(*i)[3]] = (*(i+1))[2];
	    atable[(*(i+1))[2]][(*(i+1))[3]] = (*i)[2];
	    i+=2;
	  }
    }

  return atable;
}

/* ------------------------------------------- */

};
