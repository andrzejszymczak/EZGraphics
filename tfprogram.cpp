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

#include <iostream>
#include <tfprogram.h>

using namespace std;
using namespace glm;

namespace EZGraphics {

/* ------------------------------------------- */

TFProgram::TFProgram ( const TFProgram &a )
{
  cerr << "Attempting to copy TFProgram object" << endl;
  exit(1);
}

/* ------------------------------------------- */

TFProgram & TFProgram::operator= ( const TFProgram & rhs )
{
  cerr << "Attempting assignment for a TFProgram object" << endl;
  exit(1);
}

/* ------------------------------------------- */

int TFProgram::index ( const string &s )
{
  int res = 0;
  for ( vector<std::string>::const_iterator i=variables.begin(); i!=variables.end(); ++i )
    {
      if (*i==s)
	return res;
      ++res;
    }
  return -1;
}

/* ------------------------------------------- */

TFProgram::TFProgram ( const vector<string> & l,
		       const Shader *aa, const Shader *bb, const Shader *cc, const Shader *dd, const Shader *ee ) :
  Program(l,aa,bb,cc,dd,ee)
{
  glGenTransformFeedbacks(1,&handle);
  for ( vector<string>::const_iterator s=l.begin(); s!=l.end(); ++s )
    {
      variables.push_back(*s);
      target.push_back(NULL);
    }
}

/* ------------------------------------------- */

TFProgram::~TFProgram()
{
  glDeleteTransformFeedbacks(1,&handle);
}

/* ------------------------------------------- */

void TFProgram::on ( GLenum mode )
{
  Program::on();
  glEnable(GL_RASTERIZER_DISCARD);
  glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,handle);
  glBeginTransformFeedback(mode);
}

/* ------------------------------------------- */

void TFProgram::off()
{
  glEndTransformFeedback();
  glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,0);
  glDisable(GL_RASTERIZER_DISCARD);
  Program::off();
}

/* ------------------------------------------- */

void TFProgram::link ( string s, Buffer *b )
{
  int where = index(s);
  if (where==-1)
    {
      cerr << "Error: program not ready to use " << s << " as transform feedback variable" << endl;
      cerr << "       Make sure its name is included when creating the TFProgram object" << endl;
      exit(1);
    }
  glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,handle);
  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,where,b ? b->getHandle() : 0);
  glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,0);
}

/* ------------------------------------------- */

void TFProgram::unlink ( string s )
{
  link(s,NULL);
}

/* --------------------------------------------- */

  static string _type2string ( ShaderType t )
  {
    switch(t)
      {
      case Vert:
	return "Vertex";
	break;
      case Frag:
	return "Fragment";
	break;
      case Geom:
	return "Geometry";
	break;
      case TessC:
	return "Tesselation control";
	break;
      case TessE:
	return "Tesselation Evaluation";
	break;
      default:
	cout << "Unknown shader type" << endl;
	exit(1);
	break;
      }
  }

/* --------------------------------------------- */

TFProgram * createTFProgram ( const std::vector<std::string> &l, ShaderFile s1, 
			    ShaderFile s2, ShaderFile s3, ShaderFile s4, ShaderFile s5 )
{
  ShaderFile in[5];
  Shader *sh[5] = {NULL,NULL,NULL,NULL,NULL};
  int ins = 0;
  
  if (s1.name!="") in[ins++] = s1;
  if (s2.name!="") in[ins++] = s2;
  if (s3.name!="") in[ins++] = s3;
  if (s4.name!="") in[ins++] = s4;
  if (s5.name!="") in[ins++] = s5;

  for ( int i=0; i<ins; i++ )
    for ( int j=i+1; j<ins; j++ )
      if (in[i].type==in[j].type)
	{
	  cout << "Program cannot contain two shaders for the same pipeline stage" << endl;
	  exit(1);
	}

  bool failed = false;

  for ( int i=0; i<ins; i++ )
    {
      string src = Shader::ReadFromFile(in[i].name.c_str());
      sh[i] = new Shader(in[i].type,src);
      cout << _type2string(in[i].type) << " shader log:" << endl;
      sh[i]->printLog();
      failed = failed || !sh[i];
    }

  if (failed)
    {
      cout << "Compilation of one of the shaders failed!" << endl;
      exit(1);
    }

  TFProgram *res = new TFProgram(l,sh[0],sh[1],sh[2],sh[3],sh[4]);

  cout << "Program info log: " << endl;
  res->printLog();
  if (!*res)
    {
      cout << "Linking failed!" << endl;
      exit(1);
    }

  // mark shaders for deletion
  for ( int i=0; i<ins; i++ )
    delete sh[i];

  return res;    
}

/* --------------------------------------------- */

};
