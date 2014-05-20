#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <buffer.h>
#include <vertexarray.h>
#include <program.h>

#pragma once

namespace EZGraphics {

  /* -------------------------------------- */

  /** base class for a colloection of GLUT event handlers; also, keeps track of window size and basic parameters (such as command line arguments) */
  class EventHandlerBase {

    int windowWidth, windowHeight;
    int _argc;
    char **_argv;
    unsigned int windowMode;

  public:

    /** constructor
	\param argc is the number of command-line parameters (executable name is the 0th)
	\param argv is an array containing these parameters
	\param mode defines the initial display mode (see glutInitDisplayMode for what it can be
	\param width, height define the initial size of the window */
    EventHandlerBase ( int argc, char **argv, unsigned int mode, int width = 800, int height = 800 );

    /** method called when mouse moves with right button down; in this class, this method does nothing
	\param mx,my are the event coordinates */
    virtual void motionWithRightButtonDown ( int mx, int my );

    /** method called when mouse moves with left button down; in this class, this method does nothing
	\param mx,my are the event coordinates */
    virtual void motionWithLeftButtonDown ( int mx, int my );

    /** method called when mouse moves with middle button down; in this class, this method does nothing
	\param mx,my are the event coordinates */
    virtual void motionWithMiddleButtonDown ( int mx, int my );

    /** method used to redraw the contents of the window */
    virtual void draw();

    /** method called when the left mouse button is pressed down
	\param mx,my are the event coordinates */
    virtual void leftMouseButtonDown ( int mx, int my );

    /** method called when the left mouse button is released
	\param mx,my are the event coordinates */
    virtual void leftMouseButtonUp ( int mx, int my );

    /** method called when the middle mouse button is pressed down
	\param mx,my are the event coordinates */
    virtual void middleMouseButtonDown ( int mx, int my );

    /** method called when the middle mouse button is released
	\param mx,my are the event coordinates */
    virtual void middleMouseButtonUp ( int mx, int my );

    /** method called when the right mouse button is pressed down
	\param mx,my are the event coordinates */
    virtual void rightMouseButtonDown ( int mx, int my );

    /** method called when the right mouse button is released
	\param mx,my are the event coordinates */
    virtual void rightMouseButtonUp ( int mx, int my );

    /** method called when a key is pressed
	\param key is the key
	\param x,y are the event coordinates */
    virtual void keyPressed ( unsigned char key, int x, int y );

    /** method called when the window is resized
	\param sizex, sizey are the new window dimensions */
    virtual void resize ( int sizex, int sizey );

    /** method called when there is no event in the queue */
    virtual void idleFunction();

    /** method called when the mouse moves without any button pressed down 
	\param mx,my are the event coordinates */
    virtual void passiveMotion ( int mx, int my );

    /** method called when the window becomes visible */
    virtual void windowVisible();

    /** method called when the window becomes invisible */
    virtual void windowInvisible();

    /** method called when a special key is pressed
	\param key is the special key code; see glutSpecialFunc for codes
	\param x,y are the event coordinates */					       
    virtual void specialKeyFunction ( int key, int x, int y );

    /** method called when the cursor enters the window */
    virtual void mouseCursorEnters();

    /** method called when the cursor leaves the window */
    virtual void mouseCursorLeaves();

    /** method called when a glutwrapper object is constructed, before the GLUT event loop */
    virtual void initializeGL();

    /** get the window width
	\return window width */
    int getWindowWidth();

    /** get the window height
	\return window height */
    int getWindowHeight();

    /** \return aspect ratio of the window */
    float getAspectRatio();

    /** \return window mode */
    unsigned int getWindowMode();

    /** \return number of command line arguments */
    int getArgc();

    /** \return array containing command line arguments */
    char ** getArgv();
  };

  /* -------------------------------------- */

};
