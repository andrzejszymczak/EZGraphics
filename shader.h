
#include <GL/gl.h>
#include <string>

#pragma once

namespace EZGraphics {

/* ------------------------------------------- */

/** supported shader types: tesselation control and evaluation, vertex, fragment, geometry and compute */
  typedef enum { TessC, TessE, Vert, Frag, Geom, Comp } ShaderType;

/* ------------------------------------------- */
/** wrapper for OpenGL shader object */
  class Shader {

  private:
    GLuint handle;
    ShaderType tp;

  public:
    /** generates an error - use only pointers to Shader objects for best results */
    Shader ( const Shader &a );

    /** constructor; compiles the shader from source
	\param t is the shader type (TessC, TessE, Vert, Frag, Geom or Comp)
	\param source is the shader source code
    */
    Shader ( const ShaderType t, const std::string source );
    
    /** the destructor */
    ~Shader();

    /** generates an error - use only pointers to Shader objects for best results */
    Shader & operator= ( const Shader & rhs );

    /** returns the type of the shader */
    ShaderType getType() const;

    /** returns the OpenGL name of the shader object */
    GLuint getHandle() const;

    /** prints the compilation errors */
    void printLog();

    /* returns true if the shader compiled successfully */
    operator bool();

    /** reads a file to a string 
       \param name is the file name
       \return returns the string
    */
    static std::string ReadFromFile ( const char *name );
  };



/* ------------------------------------------- */

};
