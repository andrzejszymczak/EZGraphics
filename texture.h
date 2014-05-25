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

#pragma once

namespace EZGraphics {

/* ------------------------------------------- */

/** 
    supported texture formats
    R, RG, RGB and RGBA are 8-bit unsigned integer textures (with 1...4 components)
    RF, RGF, RGBF, RGBAF are 32-bit floating point textures 
    RSF, RGSF, RGBSF, RGBASF are 16-bit floating point textures
    R32UI, RG32UI, RGB32UI, RGBA32UI are 32-bit unsigned int textures
    Depth is a 32-bit floating point depth texture
    DepthStencil is a 24-bit depth / 8 bit stencil texture
    Stencil is a 16-bit int stencil texture 
*/
  typedef enum { R, RG, RGB, RGBA, // 8-bit
		 RF, RGF, RGBF, RGBAF, // 32-bit float
		 RSF, RGSF, RGBSF, RGBASF, // 16-bit float
		 R32UI, RG32UI, RGB32UI, RGBA32UI,  // 32-bit unsigned int
		 Depth, DepthStencil, Stencil }  TexFormat;

/* ------------------------------------------- */

/** a wrapper for OpenGL texture objects */

  class Texture {

  private:

    GLuint handle;
    GLenum tgt;
    GLenum attachedto;

    int dim;
    int size[3];
    GLint internalfmt;
    GLenum fmt;
    GLenum type;

/* ------------------------------------------- */

  public:

    /** constructor for 3D textures
	\param t is the texture format
	\param x,y,z are the resolution of the texture
	\param data points to data to be transferred into the texture (no data is transferred if NULL; NULL is the default value
    */
    Texture ( TexFormat t, int x, int y, int z, GLvoid *data = NULL ); 

    /** constructor for 2D textures
	\param t is the texture format
	\param x,y are the resolution of the texture
	\param data points to data to be transferred into the texture (no data is transferred if NULL; NULL is the default value
    */
    Texture ( TexFormat t, int x, int y, GLvoid *data = NULL );    
    
    
    /** constructor for 1D textures
	\param t is the texture format
	\param x is the resolution of the texture
	\param data points to data to be transferred into the texture (no data is transferred if NULL; NULL is the default value
    */
    Texture ( TexFormat t, int x, GLvoid *data = NULL );               

    /** destructor - deletes the texture object */
    ~Texture();

    /** will generate an error - use only pointers to Texture objects for best results */
    Texture ( const Texture & );

    /** will generate an error - use only pointers to Texture objects for best results */
    Texture & operator= ( const Texture & );

    /** sets interpolation scheme to linear */    
    void linear();

    /** sets interpolation scheme to nearest */
    void nearest();

    /** clamp texture to edge */
    void clampToEdge();

    /** clamp to border */
    void clampToBorder();

    /* sets border color
       \param r,g,b is the new border color in the RGB format; all values are clamped to [0,1]
    */
    void setBorderColor ( GLfloat r, GLfloat g, GLfloat b );

    /** repeat mode */
    void repeat();

    /** makes a mipmap */
    void makeMipmap();

    /** attach texture to a texture attachment point
	\param TAP is the attachment point; TAP should be a small integer (0...15)
    */
    void bind ( int TAP );  // attaches to a texture attachment point #i

    /** attach as an image that can be read or written to inside shaders 
	\param index is the index (should match the binding qualifier for the respective image variable in a shader)
	\param level is the mipmap level to be attached
    */
    void bindAsImage ( int index, int level = 0 );  // attaches as an image...


    /** attach as an image that can be read inside shaders 
	\param index is the index (should match the binding qualifier for the respective image variable in a shader)
	\param level is the mipmap level to be attached
    */
    void bindAsROImage ( int index, int level = 0 );  // attaches as an image...


    /** attach as an image that can be written to inside shaders 
	\param index is the index (should match the binding qualifier for the respective image variable in a shader)
	\param level is the mipmap level to be attached
    */
    void bindAsWOImage ( int index, int level = 0 );  // attaches as an image...

    /** returns the OpenGL name of the texture object */
    GLuint getHandle();

    /** reads 3D texture from a raw 8-bit RGB binary file, creates and returns a pointer to the resulting texture object
	\param x,y,z are resolutions of the texture
	\param name is the file name
	\param r,g,b define the border color (default values: 0)
    */
    static Texture *createRGBTexture3D ( int x, int y, int z, const char *name, GLfloat r = 0.0, GLfloat g = 0.0, GLfloat b = 0.0 );

    /* ----------------------------------------------------- */
  
    /**  reads a 2D texture from a binary 8-bit RGB PPM file creates and returns a pointer to the resulting texture object
	 \param name is the file name (has to be a PPM with no comment lines)
	 \param r,g,b : the border color
    */
    static Texture *createRGBTexture2D ( const char *name, GLfloat r = 0.0, GLfloat g = 0.0, GLfloat b = 0.0 );
  
  };

  /* ----------------------------------------------------- */

};
