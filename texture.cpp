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

#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include <texture.h>

using namespace std;

namespace EZGraphics {

  static const GLint _ifmt[19] = {
    GL_RED, GL_RG, GL_RGB, GL_RGBA, 
    GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F, 
    GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F, 
    GL_R32UI, GL_RG32UI, GL_RGB32UI, GL_RGBA32UI, 
    GL_DEPTH_COMPONENT32, GL_DEPTH24_STENCIL8, GL_STENCIL_INDEX16 };

  static const GLint _fmt[19] = {
    GL_RED, GL_RG, GL_RGB, GL_RGBA,
    GL_RED, GL_RG, GL_RGB, GL_RGBA,
    GL_RED, GL_RG, GL_RGB, GL_RGBA,
    GL_RED, GL_RG, GL_RGB, GL_RGBA,
    GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, GL_STENCIL_INDEX };

  static const GLint _type[19] = {
    GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE,
    GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT,
    GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT,
    GL_UNSIGNED_INT, GL_UNSIGNED_INT, GL_UNSIGNED_INT, GL_UNSIGNED_INT,
    GL_FLOAT, GL_UNSIGNED_INT_24_8, GL_UNSIGNED_INT };
    

/* ----------------------------------------------------- */

Texture::Texture ( const Texture & )
{
  cerr << "Attempting to use copy constructor for a Texture object" << endl;
  exit(0);
}

/* ----------------------------------------------------- */

Texture & Texture::operator= ( const Texture & )
{
  cerr << "Attempting to use assignment operator for a Texture object" << endl;
  exit(0);
}

/* ----------------------------------------------------- */

  Texture::Texture ( TexFormat t, int x, GLvoid *data )
{
  attachedto = GL_TEXTURE15;
  glGenTextures(1,&handle);
  dim = 1;
  size[0] = x;
  size[1] = size[2] = 0;
  tgt = GL_TEXTURE_1D;
  internalfmt = _ifmt[t];
  type = _type[t];
  fmt = _fmt[t];
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexImage1D(GL_TEXTURE_1D,0,internalfmt,size[0],0,fmt,type,data);
  nearest();
}

/* ----------------------------------------------------- */

Texture::Texture ( TexFormat t, int x, int y, GLvoid *data )
{
  attachedto = GL_TEXTURE15;
  glGenTextures(1,&handle);
  dim = 2;
  size[0] = x;
  size[1] = y;
  size[2] = 0;
  tgt = GL_TEXTURE_2D;
  internalfmt = _ifmt[t];
  type = _type[t];
  fmt = _fmt[t];
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);

  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexImage2D(GL_TEXTURE_2D,0,internalfmt,size[0],size[1],0,fmt,type,data);

  nearest();
}

/* ----------------------------------------------------- */

Texture::Texture ( TexFormat t, int x, int y, int z, GLvoid *data )
{
  attachedto = GL_TEXTURE15;
  glGenTextures(1,&handle);
  dim = 3;
  size[0] = x;
  size[1] = y;
  size[2] = z;
  tgt = GL_TEXTURE_3D;
  internalfmt = _ifmt[t];
  type = _type[t];
  fmt = _fmt[t];
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexImage3D(GL_TEXTURE_3D,0,internalfmt,size[0],size[1],size[2],0,fmt,type,data);
  nearest();
}

/* ----------------------------------------------------- */

Texture::~Texture()
{
  glDeleteTextures(1,&handle);
}

/* ----------------------------------------------------- */

void Texture::linear()
{
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glTexParameteri(tgt,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(tgt,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

/* ----------------------------------------------------- */

void Texture::nearest()
{
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glTexParameteri(tgt,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(tgt,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}

/* ----------------------------------------------------- */

void Texture::repeat()
{
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_R,GL_REPEAT);
}

/* ----------------------------------------------------- */

void Texture::clampToEdge()
{
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
}

/* ----------------------------------------------------- */

  void Texture::makeMipmap()
  {
    glActiveTexture(attachedto);
    glBindTexture(tgt,handle);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glGenerateMipmap(tgt);
    glTexParameteri(tgt,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(tgt,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  }

/* ----------------------------------------------------- */

void Texture::clampToBorder()
{
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
  glTexParameteri(tgt,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_BORDER);
  //  glBindTexture(tgt,0);
}

/* ----------------------------------------------------- */

void Texture::setBorderColor ( GLfloat r, GLfloat g, GLfloat b )
{
  GLfloat rgb[3] = { r, g, b };
  glActiveTexture(attachedto);
  glBindTexture(tgt,handle);
  glTexParameterfv(tgt,GL_TEXTURE_BORDER_COLOR,rgb);
}

/* ----------------------------------------------------- */

void Texture::bind ( int i )
{
  glActiveTexture(attachedto = GL_TEXTURE0+i);
  glBindTexture(tgt,handle);
}

/* ----------------------------------------------------- */

  void Texture::bindAsImage ( int ix, int level )
  {
    glBindImageTexture(ix,handle,level,GL_FALSE,0,GL_READ_WRITE,internalfmt);
  }

/* ----------------------------------------------------- */

  void Texture::bindAsROImage ( int ix, int level )
  {
    glBindImageTexture(ix,handle,level,GL_FALSE,0,GL_READ_ONLY,internalfmt);
  }

/* ----------------------------------------------------- */

  void Texture::bindAsWOImage ( int ix, int level )
  {
    glBindImageTexture(ix,handle,level,GL_FALSE,0,GL_WRITE_ONLY,internalfmt);
  }

/* ----------------------------------------------------- */

// reads 3D texture from a raw binary file,
// creates and returns a pointer to the resulting texture object
// arguments: resolution and file name

Texture *Texture::createRGBTexture3D ( int x, int y, int z, const char *name, GLfloat r, GLfloat g, GLfloat b )
{
  ifstream ifs(name,ios::binary);
  GLubyte *vox = new GLubyte[3*x*y*z];
  ifs.read((char*)vox,3*x*y*z*sizeof(GLubyte));
  Texture *res = new Texture(RGB,x,y,z,vox);
  res->setBorderColor(r,g,b);
  delete[] vox;
  return res;
}

/* ----------------------------------------------------- */

// reads a 2D texture from a binary PPM file
// creates and returns a pointer to the resulting texture object
// The argument: file name (has to be PPM with no comment lines)
  
Texture *Texture::createRGBTexture2D ( const char *name, GLfloat r, GLfloat g, GLfloat b )
{
  ifstream ifs(name,ios::binary);
  char c;
  ifs >> c;
  assert(c=='P');
  ifs >> c;
  assert(c=='6');
  int x,y;
  ifs >> x >> y;
  int comps;
  ifs >> comps;
  assert(comps==255);
  GLubyte *pix = new GLubyte[3*x*y];
  ifs.get();
  ifs.read((char*)pix,3*x*y*sizeof(GLubyte));
  Texture *res = new Texture(RGB,x,y,pix);
  res->setBorderColor(r,g,b);
  delete[] pix;
  return res;
}

/* ----------------------------------------------------- */

  GLuint Texture::getHandle()
  {
    return handle;
  }

/* ----------------------------------------------------- */

};
