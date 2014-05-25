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

#include <iostream>
#include <cstdlib>

#include <mesh.h>
#include <trackballhandler.h>
#include <program.h>
#include <buffer.h>
#include <glutwrapper.h>

using namespace std;
using namespace glm;

namespace EZGraphics {

/* ---------------------------------------------- */

TrackballHandler::Trackball::Trackball ( int sx, int sy ) : R(), R0(), R0R(), ismousedown(false)
{
  winsize[0] = sx;
  winsize[1] = sy;
  
}

/* ---------------------------------------------- */

void TrackballHandler::Trackball::resize ( int sx, int sy )
{
  winsize[0] = sx;
  winsize[1] = sy;
}

/* ---------------------------------------------- */

vec3 TrackballHandler::Trackball::_ij2xyz ( float i, float j )
{
  float x = 2*i/winsize[0]-1;
  float y = 1-2*j/winsize[1];
  float x2y2 = 1-x*x-y*y;

  if (x2y2<0)
    {
      double l = sqrt(x*x+y*y);
      x = x/l;
      y = y/l;
      x2y2 = 0;
      
    }

  float z = sqrt(x2y2);

  return vec3(x,y,z);      
}

/* ---------------------------------------------- */

void TrackballHandler::Trackball::mouseDown ( int i, int j )
{
  ismousedown = true;
  last = _ij2xyz(i+0.013347689,j+0.0347387583);    // perturb to ensure no degeneracy
}

/* ---------------------------------------------- */

void TrackballHandler::Trackball::mouseMove ( int i, int j )
{
  vec3 cur = _ij2xyz(i,j);
  vec3 axis = cross(last, cur);
  R0 = mat3(rotate(mat4(),float(acos(dot(last,cur))),axis));
  R0R = R0*R;
}

/* ---------------------------------------------- */

void TrackballHandler::Trackball::mouseUp ( int i, int j )
{
  if (!ismousedown)
    return;
  ismousedown = false;

  vec3 cur = _ij2xyz(i,j);
  vec3 axis = cross(last, cur);
  R0 = mat3(rotate(mat4(),float(acos(dot(last,cur))),axis));
  R = R0*R;
  R0 = dmat3();
  R0R = R;
}

/* ---------------------------------------------- */

mat3 TrackballHandler::Trackball::rotation()
{
  return R0R;
}

/* ---------------------------------------------- */

bool TrackballHandler::Trackball::isActive()
{
  return ismousedown;
}

/* -------------------------------------- */

TrackballHandler::TrackballHandler ( int argc, char **argv, unsigned int mode, int width, int height ) :
  EventHandlerBase(argc,argv,mode,width,height), zoom(0.05f)
{
  t = new Trackball(width,height);
}

/* -------------------------------------- */

void TrackballHandler::motionWithMiddleButtonDown ( int mx, int my )
{
  int dy = my-lasty;
  zoom += dy/6000.0;
  if (zoom<=0.0001) zoom = 0.0001;
  if (zoom>=0.999*M_PI) zoom = 0.999*M_PI;
  lasty = my;
}

/* -------------------------------------- */

void TrackballHandler::motionWithLeftButtonDown ( int mx, int my )
{
  t->mouseMove(mx,my);
}

/* -------------------------------------- */

void TrackballHandler::leftMouseButtonDown ( int mx, int my )
{
  t->mouseDown(mx,my);
}

/* -------------------------------------- */

void TrackballHandler::leftMouseButtonUp ( int mx, int my )
{
  t->mouseUp(mx,my);
}

/* -------------------------------------- */

void TrackballHandler::middleMouseButtonDown ( int mx, int my )
{
  lasty = my;
}

/* -------------------------------------- */

void TrackballHandler::resize ( int sizex, int sizey )
{
  EventHandlerBase::resize(sizex,sizey);
  t->resize(sizex,sizey);  
}

/* -------------------------------------- */

glm::mat3 TrackballHandler::getRotation()
{
  return t->rotation();
}

/* -------------------------------------- */

float TrackballHandler::getZoom()
{
  return zoom;
}

/* -------------------------------------- */

};
