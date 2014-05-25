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

#include <vector>
#include "buffer.h"

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  /** a wrapper for the OpenGL vertex array object */
  class VertexArray {

  private:
    GLuint handle;

    void on();
    void off();

  public:

    /** constructs an empty vertex array */
    VertexArray();

    /** destructor */
    ~VertexArray();

    /** generates an error - use only pointers to VertexArray objects for best results */
    VertexArray ( const VertexArray & );

    /** generates an error - use only pointers to VertexArray objects for best results */ 
    VertexArray & operator= ( const VertexArray & );

    /** attach an instanced attribute to the vertex array
	\param aix is the attribute index
	\param b is the pointer to the buffer to be attached
	\param divisor is the divisor of the attribute
    */
    void attachInstancedAttribute ( const GLuint aix, const Buffer * b, GLuint divisor = 1 );

    /** attach a non-instanced attribute 
	\param aix is the attribute index
	\param b is the pointer to the buffer to be attached
    */
    void attachAttribute ( const GLuint aix, const Buffer *b );

    /** sends vertices to pipeline; vertex attributes are generated using indices first ... first+num-1 from data in the buffers attached to the vertex array
	\param ptype is the type of the OpenGL primitive, e.g. GL_TRIANGLES, GL_POINTS, GL_TRIANGLE_STRIP
	\param first is the index of the first vertex
	\param num is the number of vertices to be generated
    */
    void sendToPipeline ( GLenum ptype, GLint first, GLsizei num );

    /** sends vertices to the pipeline; vertex attributes are generated from buffers attached to the vertex array using indices looked up from the index buffer b; these indices are b[first]...b[first+num-1]
	\param ptype is the type of the OpenGL primitive, e.g. GL_TRIANGLES, GL_POINTS, GL_TRIANGLE_STRIP
	\param b is a pointer to the index buffer to be used to generate the vertices
	\param first is the index of the first entry of b used to generate a vertex
	\param num is the number of vertices to be generated
    */
    void sendToPipelineIndexed ( GLenum ptype, IndexBuffer *b, GLint first, GLsizei num );

    /** instanced version of sendToPipeline
	\param ptype is the type of the OpenGL primitive, e.g. GL_TRIANGLES, GL_POINTS, GL_TRIANGLE_STRIP
	\param first is the index of the first vertex
	\param num is the number of vertices to be generated
	\param N is the number of instances to be generated
    */
    void sendToPipelineInstanced ( GLenum ptype, GLint first, GLsizei num, GLsizei N );

    /** instanced version of sendToPipeline
	\param ptype is the type of the OpenGL primitive, e.g. GL_TRIANGLES, GL_POINTS, GL_TRIANGLE_STRIP
	\param b is a pointer to the index buffer to be used to generate the vertices
	\param first is the index of the first entry of b used to generate a vertex
	\param num is the number of vertices to be generated
	\param N is the number of instances to be generated
    */
    void sendToPipelineInstancedIndexed ( GLenum ptype, IndexBuffer *b, GLint first, GLsizei num, GLsizei N );

  };
  

/* ------------------------------------------- */

};
