
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
