#include <GL/glew.h>
#include <GL/gl.h>

#include <program.h>
#include <buffer.h>
#include <vector>
#include <string>

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  /** a wrapper class for transform feedback programs */
  class TFProgram : public Program {

    std::vector<std::string> variables;
    std::vector<Buffer*> target;
    GLuint handle;

    int index ( const std::string &s );

  public:

    /** generates an error - use only pointers to TFProgram objects for best results */
    TFProgram ( const TFProgram &a );  

    /** generates an error - use only pointers to TFProgram objects for best results */
    TFProgram & operator= ( const TFProgram & rhs );  
    
    /** read shader source code from files, compile them and link
	\param l is a vector containing all names of shader variables to be captured in the transform feedback buffers
	\param s1,s2,s3,s4,s5 - shader files
	\return a pointer to the resulting Program object
    */
    TFProgram ( const std::vector<std::string> &l,
		const Shader *aa = NULL, const Shader *bb = NULL, const Shader *cc = NULL, 
		const Shader *dd = NULL, const Shader *ee = NULL );
    /** turn the program on
	\param mode is the typr of data to be written into the transform feedback buffer (GL_POINTS, GL_LINES or GL_TRIANGLES); see glBeginTransformFeedback for more details */
    void on ( GLenum mode );
    
    /** turn the program off */
    void off();
    
    /** link an output shader variable with a specific buffer 
	\param s is the name of the variable
	\param b is the pointer to a Buffer object in which values of s will be stored */
    void link ( std::string s, Buffer *b );

    /** detach s from its buffer */
    void unlink ( std::string s );


    /** read shader source code from files, compile them and link
	\param l is a vector of variables that will be written into the transform feedback buffers
        \param s1,s2,s3,s4,s5 - shader files
        \return a pointer to the resulting TFProgram object
    */
    static TFProgram * createTFProgram ( const std::vector<std::string> &l, ShaderFile s1, 
	   			     ShaderFile s2 = ShaderFile(), ShaderFile s3 = ShaderFile(), 
				     ShaderFile s4 = ShaderFile(), ShaderFile s5 = ShaderFile() );

    ~TFProgram();
  };

  /* ------------------------------------------- */

  /* ------------------------------------------- */

};
