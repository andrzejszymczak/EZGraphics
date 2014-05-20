#define GLM_FORCE_RADIANS
#include <GL/gl.h>
#include <glm/glm.hpp>

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  /** supported buffer types: Array is a standard array buffer and ElemArray is an element array (index buffer) */
  typedef enum { Array, ElemArray }  BufType;

  /* ------------------------------------------- */

  /** wrapper class for OpenGL Buffer objects */
  class Buffer {
  
  private:
  
    GLuint handle; /** OpenGL name of the buffer object */
    BufType tp;    /** type of the buffer (array or element) */
    GLenum type;   /** type of entries - this is an OpenGL constant such as GL_INT */
    int components; /** components per entry - can be 1,2,3 or 4, e.g. 3 if entries are 3D vectors */

    void on();
    void off();

    GLenum getType() const { return type; }
    GLuint getHandle() const { return handle; }

    Buffer ( const int cs, const int size, const GLubyte * const data = NULL, const BufType t = Array );
    Buffer ( const int cs, const int size, const GLbyte * const data = NULL, const BufType t = Array );
    Buffer ( const int cs, const int size, const GLuint * const data = NULL, const BufType t = Array );
    Buffer ( const int cs, const int size, const GLint * const data = NULL, const BufType t = Array );
    Buffer ( const int cs, const int size, const GLshort * const data = NULL, const BufType t = Array );
    Buffer ( const int cs, const int size, const GLushort * const data = NULL, const BufType t = Array );
    Buffer ( const int cs, const int size, const GLfloat * const data = NULL, const BufType t = Array );

  public:
  
    /** 
	Generates an error - use only pointers to Buffer objects for best results
    */
    Buffer ( const Buffer &a );   
 
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const GLubyte * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const GLbyte * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */    
    Buffer ( const int size, const GLshort * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */    
    Buffer ( const int size, const GLushort * const data = NULL, const BufType t = Array );

    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const GLint * const data, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */    
    Buffer ( const int size, const glm::ivec2 * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */    
    Buffer ( const int size, const glm::ivec3 * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::ivec4 * const data = NULL, const BufType t = Array );

    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const GLuint * const data, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::uvec2 * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::uvec3 * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::uvec4 * const data = NULL, const BufType t = Array );

    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const GLfloat * const data, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::vec2 * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::vec3 * const data = NULL, const BufType t = Array );
    
    /** 
	Constructs a buffer object; sends data to it if non-NULL pointer is provided as the data parameter
	\param size is the number of entries (typically, vertices in the model)
	\param data is the pointer to data to be sent to the buffer; if data==NULL (default), no data is sent
	\param t is the buffer type; default value is Array (meaning array buffer)
    */
    Buffer ( const int size, const glm::vec4 * const data = NULL, const BufType t = Array );

    /** deletes the buffer */
    ~Buffer();
    
    /** will generate an error */
    Buffer & operator= ( const Buffer & rhs );

    /** 
    sets the vertex attribute index for data stored in the buffer 
    \param aix is the index of the attribute; has to match the location qualifier in the vertex shader
    */
    void setIndex ( int aix ) const;
    
    /** 
    Use buffer as shader storage
    \param index is the index of the shader storage buffer; has to match the binding qualifier of the buffer in the shaders
    */
    void useAsShaderStorage ( GLuint index );
    
    friend class VertexArray;
    friend class TFProgram;
  };

  /* ------------------------------------------- */

  /** a wrapper for index buffers (or element array buffers) */
  class IndexBuffer : public Buffer {
  public:
  
    /** constructs the index buffer; sends data to it if non-NULL pointer is provided as the second argument
       \param size is the number of entries in the buffer
       \param data is the pointer to data to be sent to it
    */
    IndexBuffer ( const int size, const GLubyte * const data = NULL );
    
    /** constructs the index buffer; sends data to it if non-NULL pointer is provided as the second argument
       \param size is the number of entries in the buffer
       \param data is the pointer to data to be sent to it
    */
    IndexBuffer ( const int size, const GLuint * const data = NULL );
    
    /** constructs the index buffer; sends data to it if non-NULL pointer is provided as the second argument
        \param size is the number of entries in the buffer
        \param data is the pointer to data to be sent to it
    */
    IndexBuffer ( const int size, const GLushort * const data = NULL );
    
    /** constructs the index buffer; sends data to it if non-NULL pointer is provided as the second argument
       \param size is the number of entries in the buffer
       \param data is the pointer to data to be sent to it
       The resulting buffer has 2*size scalar entries
    */
    IndexBuffer ( const int size, const glm::uvec2 * const data = NULL );
    
    /** constructs the index buffer; sends data to it if non-NULL pointer is provided as the second argument
       \param size is the number of entries in the buffer
       \param data is the pointer to data to be sent to it
       Note that the resulting buffer has 3*size scalar entries for this variant of the constructor
    */
    IndexBuffer ( const int size, const glm::uvec3 * const data = NULL );
    
    /** will generate an error - use only pointers to IndexBuffer objects for best results */
    IndexBuffer ( const IndexBuffer & );
    
    /** will generate an error - use only pointers to IndexBuffer objects for best results */
    IndexBuffer & operator= ( const IndexBuffer & );
  };

  /* ------------------------------------------- */

};
