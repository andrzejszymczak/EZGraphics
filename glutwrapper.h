
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
