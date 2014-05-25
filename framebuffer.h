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

#include <vector>
#include <texture.h>

#pragma once

namespace EZGraphics {

/** A wrapper for OpenGL framebuffer objects */
  class Framebuffer {

    GLuint handle;
    std::vector<GLenum> color_attachments;

  public:
  
  /** generates an error - use only pointers to Framebuffer objects for best results */
    Framebuffer ( const Framebuffer &f );
  
  /** generates an error - use only pointers to Framebuffer objects for best results */
    Framebuffer & operator= ( const Framebuffer &f );
  
  /** constructs an empty frameuffer */
    Framebuffer();
    
  /** destructor */
    ~Framebuffer();

  /** attach a depth texture 
  \param t is a pointer to a texture of the Depth type
  */
    void attachDepth ( Texture *t );
    
  /** attach a stencil texture
  \param t is a pointer to a texuture of Stencil type
  */
    void attachStencil ( Texture *t );
    
  /** attach a combined depth-stencil texture
  \param t points to a texutre of DepthStencil type
  */
    void attachDepthStencil ( Texture *t );

  /** attach a color texture
  \param t points to a texture of a color-compatible type, e.g. R, RGB, RGBA etc
  \param i is the index of the color attachment
  */
    void attachColor ( Texture *t, int i = 0 );

  /** activate the framebuffer; from now until the off method is called the framebuffer becomes the render target */
    void on();
  
  /** deactivate the framebuffer */
    void off();

  /** prints the log; returns error code or GL_FRAMEBUFFER_COMPLETE if the framebuffer is complete/ready to use */
    GLenum printLog();
    
  };

};
