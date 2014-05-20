
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
