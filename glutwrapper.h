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
#include <GL/glext.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <handlerbase.h>

#pragma once

namespace EZGraphics {

  /* -------------------------------------- */

  /** a simple wrapper class for the GLUT library */
  class GLUTwrapper {
    
    static  EventHandlerBase *handler;
    static int windowID;
    static int buttonDown;
    
    static void activeMotion ( int mx, int my );
    static void draw();
    static void mouseButton ( int btn, int state, int mx, int my );
    static void keyPressed ( unsigned char key, int x, int y );
    static void resize ( int sizex, int sizey );
    static void idleFunction();
    static void passiveMotion ( int mx, int my );
    static void visibilityFunction ( int state );
    static void specialFunction ( int key, int x, int y );
    static void entryFunction ( int state );

  public:

    /** constructor; generates an error if called twice 
\param h is a pointer to a class derived from EventHandlerBase that implements callback functions as methods; see EventHandlerBase documentation */
    GLUTwrapper ( EventHandlerBase *h );

    /** run the event loop */
    void run();
  };

  /* -------------------------------------- */

};
