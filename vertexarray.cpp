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

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <cstdlib>

#include "vertexarray.h"

using namespace std;

namespace EZGraphics {

/* ------------------------------------------- */

VertexArray::VertexArray ( const VertexArray & rhs )
{
  cerr << "Attempting to copy VertexArray object" << endl;
  exit(1);     
}

/* ------------------------------------------- */

VertexArray & VertexArray::operator= ( const VertexArray & rhs )
{
  cerr << "Attempting assignment of VertexArray object" << endl;
  exit(1);
}

/* ------------------------------------------- */

VertexArray::VertexArray()
{
  glGenVertexArrays(1,&handle);
}

/* ------------------------------------------- */

VertexArray::~VertexArray()
{
  assert(glIsVertexArray(handle));
  glDeleteVertexArrays(1,&handle);
}

/* ------------------------------------------- */

void VertexArray::attachInstancedAttribute ( const GLuint aix, const Buffer * b, GLuint divisor )
{
  glBindVertexArray(handle);
  b->setIndex(aix);
  glEnableVertexAttribArray(aix);
  glVertexAttribDivisor(aix,divisor);
  glBindVertexArray(0);
}

/* ------------------------------------------- */

void VertexArray::attachAttribute ( const GLuint aix, const Buffer * b )
{
  glBindVertexArray(handle);
  b->setIndex(aix);
  glEnableVertexAttribArray(aix);
  glBindVertexArray(0);
}

/* ------------------------------------------- */

void VertexArray::on()
{
  glBindVertexArray(handle);
}

/* ------------------------------------------- */

void VertexArray::off()
{
  glBindVertexArray(0);
}

/* ------------------------------------------- */

void VertexArray::sendToPipeline ( GLenum ptype, GLint first, GLsizei num )
{
  on();
  glDrawArrays(ptype,first,num);
  off();
}

/* ------------------------------------------- */

void VertexArray::sendToPipelineInstanced ( GLenum ptype, GLint first, GLsizei num, GLsizei N )
{
  on();
  glDrawArraysInstanced(ptype,first,num,N);
  off();
}

/* ------------------------------------------- */

void VertexArray::sendToPipelineIndexed ( GLenum ptype, IndexBuffer *b, GLint first, GLsizei num )
{
  on();
  b->on();
  glDrawElements(ptype,num,b->getType(),(GLvoid*)(long)first);
  b->off();
  off();
}

/* ------------------------------------------- */


void VertexArray::sendToPipelineInstancedIndexed ( GLenum ptype, IndexBuffer *b, GLint first, GLsizei num, GLsizei N )
{
  on();
  b->on();
  glDrawElementsInstanced(ptype,num,b->getType(),(GLvoid*)(long)first,N);
  b->off();
  off();
}

/* ------------------------------------------- */

};
