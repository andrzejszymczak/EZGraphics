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

    /** returns true if the shader compiled successfully */
    operator bool();

    /** reads a file to a string 
       \param name is the file name
       \return returns the string
    */
    static std::string ReadFromFile ( const char *name );
  };



/* ------------------------------------------- */

};
