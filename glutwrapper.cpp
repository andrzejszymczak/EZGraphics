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
#include <glutwrapper.h>
#include <handlerbase.h>

using namespace std;

namespace EZGraphics {

/* -------------------------------------- */

EventHandlerBase *GLUTwrapper::handler = NULL;
int GLUTwrapper::windowID = -1;
int GLUTwrapper::buttonDown = -1;

/* -------------------------------------- */

void GLUTwrapper::activeMotion ( int mx, int my )
{
  switch(buttonDown)
    {
    case GLUT_RIGHT_BUTTON:
      handler->motionWithRightButtonDown(mx,my);
      break;
    case GLUT_LEFT_BUTTON:
      handler->motionWithLeftButtonDown(mx,my);
      break;
    case GLUT_MIDDLE_BUTTON:
      handler->motionWithMiddleButtonDown(mx,my);
      break;
    }
}

/* -------------------------------------- */

void GLUTwrapper::draw()
{
  glutSetWindow(windowID);
  handler->draw();
}

/* -------------------------------------- */

void GLUTwrapper::mouseButton ( int btn, int state, int mx, int my )
{
  switch(btn)
    {
    case GLUT_LEFT_BUTTON:
      if(state==GLUT_DOWN)
	{
	  handler->leftMouseButtonDown(mx,my);
	  buttonDown = GLUT_LEFT_BUTTON;
	}
      if (state==GLUT_UP)
	{
	  if (buttonDown==GLUT_LEFT_BUTTON)
	    handler->leftMouseButtonUp(mx,my);
	  buttonDown = -1;
	}
      break;
    case GLUT_MIDDLE_BUTTON:
      if(state==GLUT_DOWN)
	{
	  handler->middleMouseButtonDown(mx,my);
	  buttonDown = GLUT_MIDDLE_BUTTON;
	}
      if (state==GLUT_UP)
	{
	  if (buttonDown==GLUT_MIDDLE_BUTTON)
	    handler->middleMouseButtonUp(mx,my);
	  buttonDown = -1;
	}
      break;
    case GLUT_RIGHT_BUTTON:
      if(state==GLUT_DOWN)
	{
	  handler->rightMouseButtonDown(mx,my);
	  buttonDown = GLUT_RIGHT_BUTTON;
	}
      if (state==GLUT_UP)
	{
	  if (buttonDown==GLUT_RIGHT_BUTTON)
	    handler->rightMouseButtonUp(mx,my);
	  buttonDown = -1;
	}
      break;
    }
}

/* -------------------------------------- */

void GLUTwrapper::keyPressed ( unsigned char key, int x, int y )
{
  handler->keyPressed(key,x,y);
}

/* -------------------------------------- */

void GLUTwrapper::resize ( int sizex, int sizey )
{
  handler->resize(sizex,sizey);
}

/* -------------------------------------- */

void GLUTwrapper::idleFunction()
{
  handler->idleFunction();
}

/* -------------------------------------- */

void GLUTwrapper::passiveMotion ( int mx, int my )
{
  handler->passiveMotion(mx,my);
}

/* -------------------------------------- */

void GLUTwrapper::visibilityFunction ( int state )
{
  switch(state)
    {
    case GLUT_VISIBLE:
      handler->windowVisible();
      break;
    case GLUT_NOT_VISIBLE:
      handler->windowInvisible();
      break;
    }
}

/* -------------------------------------- */

void GLUTwrapper::specialFunction ( int key, int x, int y )
{
  handler->specialKeyFunction(key,x,y);
}

/* -------------------------------------- */

void GLUTwrapper::entryFunction ( int state )
{
  switch(state)
    {
    case GLUT_ENTERED:
      handler->mouseCursorEnters();
      break;
    case GLUT_LEFT:
      handler->mouseCursorLeaves();
      break;
    }
}

/* -------------------------------------- */

GLUTwrapper::GLUTwrapper ( EventHandlerBase *h )
{
  if (handler)
    {
      std::cerr << "Only one instance of the GLUTwrapper class allowed!" << std::endl;
      std::exit(1);
    }

  int a = h->getArgc();
  glutInit(&a,h->getArgv());
  
  glutInitWindowSize(h->getWindowWidth(),h->getWindowHeight());
  glutInitWindowPosition(10,10);
  glutInitDisplayMode(h->getWindowMode());
  windowID = glutCreateWindow("A window");

  // initialize glew and check for OpenGL 4.0 support
  glewInit();
  if (glewIsSupported("GL_VERSION_4_3"))
    cout << "Ready for OpenGL 4.3" << endl;
  else 
    {
      cerr << "OpenGL 4.3 not supported" << endl;
      exit(1);
    }

  handler = h;

  glutMouseFunc(mouseButton);
  glutMotionFunc(activeMotion);
  glutPassiveMotionFunc(passiveMotion);
  glutIdleFunc(idleFunction);
  glutDisplayFunc(draw);
  glutVisibilityFunc(visibilityFunction);
  glutSpecialFunc(specialFunction);
  glutEntryFunc(entryFunction);
  glutKeyboardFunc(keyPressed);
  glutReshapeFunc(resize);

  h->initializeGL();
}

/* -------------------------------------- */

void GLUTwrapper::run()
{
  glutMainLoop();
}

/* -------------------------------------- */

};
