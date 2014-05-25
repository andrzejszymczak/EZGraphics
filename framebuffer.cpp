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
#include <iostream>
#include <algorithm>

#include "framebuffer.h"

using namespace std;

namespace EZGraphics {

  Framebuffer::Framebuffer ( const Framebuffer &f )
    {
        cerr << "Attempting to use copy constructor for a Buffer object" << endl;
        exit(1);
    }
    
  Framebuffer & Framebuffer::operator= ( const Framebuffer &f )
    {
        cerr << "Attempting to use assignment operator for a Buffer object" << endl;
        exit(1);
    }

  Framebuffer::Framebuffer()
    {
      glGenFramebuffers(1,&handle);
    }

  void Framebuffer::on()
    {
      glBindFramebuffer(GL_FRAMEBUFFER,handle);
      glDrawBuffers(color_attachments.size(),color_attachments.data());
    }

  void Framebuffer::off()
    {
      glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

  Framebuffer::~Framebuffer()
    {
      glDeleteFramebuffers(1,&handle);
    }

  void Framebuffer::attachDepth ( Texture *t )
    {
      glBindFramebuffer(GL_FRAMEBUFFER,handle);
      glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,t->getHandle(),0);
      glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
  
  void Framebuffer::attachDepthStencil ( Texture *t )
  {
    glBindFramebuffer(GL_FRAMEBUFFER,handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D,t->getHandle(),0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
  }

  void Framebuffer::attachStencil ( Texture *t )
  {
    glBindFramebuffer(GL_FRAMEBUFFER,handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,GL_TEXTURE_2D,t->getHandle(),0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
  }

  void Framebuffer::attachColor ( Texture *t, int i )
    {
      glBindFramebuffer(GL_FRAMEBUFFER,handle);
      glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+i,GL_TEXTURE_2D,t->getHandle(),0);
      if (find(color_attachments.begin(),color_attachments.end(),
	       GL_COLOR_ATTACHMENT0+i)==color_attachments.end())
	color_attachments.push_back(GL_COLOR_ATTACHMENT0+i);
      glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

  GLenum Framebuffer::printLog()
  {
    glBindFramebuffer(GL_FRAMEBUFFER,handle);
    GLenum error;
    // check the error status of this framebuffer */
    error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    {
      switch(error)
	{
	case GL_FRAMEBUFFER_COMPLETE:
	  break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
	  cout << "missing a required image/buffer attachment!" << endl;
	  break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
	  cout << "no images/buffers attached!" << endl;
	  break;
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
	  cout << "mismatched image/buffer dimensions!" << endl;
	  break;
	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
	  cout << "colorbuffer attachments have different types!" << endl;
	  break;
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
	  cout << "trying to draw to non-attached color buffer!" << endl;
	  break;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
	  cout << "trying to read from a non-attached color buffer!" << endl;
	  break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
	  cout << "format is not supported by current graphics card/driver!" << endl;
	  break;
	default:
	  cout << "*UNKNOWN ERROR* reported from glCheckFramebufferStatus()" << endl;
	  break;
	}
    }    
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    return error;    
  }
};
