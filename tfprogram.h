#include <GL/glew.h>
#include <GL/gl.h>

#include <program.h>
#include <buffer.h>
#include <vector>
#include <string>

#pragma once

namespace EZGraphics {

  /* ------------------------------------------- */

  class TFProgram : public Program {

    std::vector<std::string> variables;
    std::vector<Buffer*> target;
    GLuint handle;

    int index ( const std::string &s );

  public:
    TFProgram ( const TFProgram &a );  // will generate an error
    TFProgram & operator= ( const TFProgram & rhs );  // will generate an error
    
    TFProgram ( const std::vector<std::string> &l,
		const Shader *aa = NULL, const Shader *bb = NULL, const Shader *cc = NULL, 
		const Shader *dd = NULL, const Shader *ee = NULL );

    void on ( GLenum mode );
    void off();
    
    void link ( std::string s, Buffer *b );
    void unlink ( std::string s );

    ~TFProgram();
  };

  /* ------------------------------------------- */

  extern TFProgram * createTFProgram ( const std::vector<std::string> &l, ShaderFile s1, 
				     ShaderFile s2 = ShaderFile(), ShaderFile s3 = ShaderFile(), 
				     ShaderFile s4 = ShaderFile(), ShaderFile s5 = ShaderFile() );

  /* ------------------------------------------- */

};
