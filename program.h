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
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <map>
#include <string>
#include <glm/glm.hpp>

#include <buffer.h>

#include "shader.h"

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  /** a struct representing a shader source file */
  struct ShaderFile {

    /** name of the file */
    std::string name;

    /** type of the file */
    ShaderType type;

    /** simple constructor
	\param t is the shader type
	\param n is the name of the file 
    */
    ShaderFile ( ShaderType t, std::string n );

    /** a convenient default constructor */
    ShaderFile();
  };

  /* ------------------------------------------- */

  /** a wrapper for the OpenGL program object */
  class Program {

  private:

    struct unidata {
      GLint location;
      GLenum type;
      unidata ( GLint l, GLint t ) : location(l), type(t) {}
      unidata() {}
    };

    static const Program * laston;

    GLuint handle;
    const Shader *c, *e, *v, *f, *g, *cs;
    const Shader *cmp;
    bool one_warning_printed;

    std::map<std::string,unidata> univars;

  protected:

    /** a version of the constructor used in transform feedback */
    Program ( const std::vector<std::string> &l,
	      const Shader *aa = NULL, const Shader *bb = NULL, const Shader *cc = NULL, const Shader *dd = NULL, const Shader *ee = NULL );

  public:

    /** generates an error - use only pointers to Program objects for best results */
    Program ( const Program &a );  

    /** generates an error - use only pointers to Program objects for best results */
    Program & operator= ( const Program & rhs ); 

    /** constructs a program object and attaches up to 5 shaders to it
	\param aa,bb,cc,dd,ee are pointers to Shader objects the program consists of
    */
    Program ( const Shader *aa = NULL, const Shader *bb = NULL, const Shader *cc = NULL, const Shader *dd = NULL, const Shader *ee = NULL );

    /** destroys the program object */
    ~Program();

    /** turn the program on; turn programs on one at a time for best results */
    void on() const;

    /** turns the program off */
    void off() const;

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::vec2 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::vec3 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::vec4 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, GLfloat v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::ivec2 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::ivec3 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::ivec4 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, GLint v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::uvec2 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::uvec3 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::uvec4 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, GLuint v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat2 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat3 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat4 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat2x3 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat2x4 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat3x2 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat3x4 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat4x2 v );

    /** assigns a value to a uniform variable
	\name is the name of the variable
	\v is the value to be assigned to it
    */
    void setUniform ( const GLchar *name, glm::mat4x3 v );
    
    /** print OpenGL compiler and linker errors */
    void printLog();

    /** returns true if the compilation and linking went fine */
    operator bool();

    /** read shader source code from files, compile them and link
        \param s1,s2,s3,s4,s5 - shader files
        \return a pointer to the resulting Program object
    */
    static Program * createProgram ( ShaderFile s1, 
				   ShaderFile s2 = ShaderFile(), ShaderFile s3 = ShaderFile(), 
				   ShaderFile s4 = ShaderFile(), ShaderFile s5 = ShaderFile() );
  };

  /* ------------------------------------------- */

};
