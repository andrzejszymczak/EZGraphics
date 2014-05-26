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
#include <menucreator.h>

using namespace std;
using namespace glm;
using namespace EZGraphics;

/* -------------------------------------- */

class ViewerEventHandlers : public TrackballHandler, public MenuCreator {

  Program *p;
  vec3 mx, mn;
  float maxdim;
  vec3 center;
  IndexBuffer *ix;
  Buffer *cpts;
  VertexArray *va;
  static int router,rinner;


  enum mode { PHONG, FLAT, FLATBUF, FLATINDEX, GOURAUD };

  static int reor;
  static mode which;
  static int what;

public:

  ViewerEventHandlers ( int argc, char **argv ) :
    TrackballHandler(argc,argv,GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGB|GLUT_MULTISAMPLE,800,800)
  {
  }

/* -------------------------------------- */

  static void plain()
  {
    what = 2;
  }

  static void patch()
  {
    what = 1;
  }

  static void tri()
  {
    what = 0;
  }

  static void seti1()
  {
    rinner = 1;
  }

  static void seti2()
  {
    rinner = 2;
  }

  static void seti4()
  {
    rinner = 4;
  }

  static void seti8()
  {
    rinner = 8;
  }

  static void seti16()
  {
    rinner = 16;
  }

  static void seti32()
  {
    rinner = 32;
  }

  static void seti64()
  {
    rinner = 64;
  }

  static void seto1()
  {
    router = 1;
  }

  static void seto2()
  {
    router = 2;
  }

  static void seto4()
  {
    router = 4;
  }

  static void seto8()
  {
    router = 8;
  }

  static void seto16()
  {
    router = 16;
  }

  static void seto32()
  {
    router = 32;
  }

  static void seto64()
  {
    router = 64;
  }

  /* -------------------------------------- */

  void initializeGL()
  {
    p = Program::createProgram(ShaderFile(Vert,"teapot-shaders/vtx.glsl"),
			       ShaderFile(TessC,"teapot-shaders/ctrl.glsl"),
			       ShaderFile(TessE,"teapot-shaders/eval.glsl"),
			       ShaderFile(Geom,"teapot-shaders/geom.glsl"),
			       ShaderFile(Frag,"teapot-shaders/frg.glsl"));
    
    const vec3 vc[127] = { 
      vec3(0.2000,0.0000,2.70000),vec3(0.2000,-0.1120,2.70000),
      vec3(0.1120,-0.2000,2.70000),vec3(0.0000,-0.2000,2.70000),
      vec3(1.3375,0.0000,2.53125),vec3(1.3375,-0.7490,2.53125),
      vec3(0.7490,-1.3375,2.53125),vec3(0.0000,-1.3375,2.53125),
      vec3(1.4375,0.0000,2.53125),vec3(1.4375,-0.8050,2.53125),
      vec3(0.8050,-1.4375,2.53125),vec3(0.0000,-1.4375,2.53125),
      vec3(1.5000,0.0000,2.40000),vec3(1.5000,-0.8400,2.40000),
      vec3(0.8400,-1.5000,2.40000),vec3(0.0000,-1.5000,2.40000),
      vec3(1.7500,0.0000,1.87500),vec3(1.7500,-0.9800,1.87500),
      vec3(0.9800,-1.7500,1.87500),vec3(0.0000,-1.7500,1.87500),
      
      vec3(2.0000,0.0000,1.35000),vec3(2.0000,-1.1200,1.35000),
      vec3(1.1200,-2.0000,1.35000),vec3(0.0000,-2.0000,1.35000),
      vec3(2.0000,0.0000,0.90000),vec3(2.0000,-1.1200,0.90000),
      vec3(1.1200,-2.0000,0.90000),vec3(0.0000,-2.0000,0.90000),
      vec3(-2.0000,0.0000,0.90000),vec3(2.0000,0.0000,0.45000),
      vec3(2.0000,-1.1200,0.45000),vec3(1.1200,-2.0000,0.45000),
      vec3(0.0000,-2.0000,0.45000),vec3(1.5000,0.0000,0.22500),
      vec3(1.5000,-0.8400,0.22500),vec3(0.8400,-1.5000,0.22500),
      vec3(0.0000,-1.5000,0.22500),vec3(1.5000,0.0000,0.15000),
      vec3(1.5000,-0.8400,0.15000),vec3(0.8400,-1.5000,0.15000),

      vec3(0.0000,-1.5000,0.15000),vec3(-1.6000,0.0000,2.02500),
      vec3(-1.6000,-0.3000,2.02500),vec3(-1.5000,-0.3000,2.25000),
      vec3(-1.5000,0.0000,2.25000),vec3(-2.3000,0.0000,2.02500),
      vec3(-2.3000,-0.3000,2.02500),vec3(-2.5000,-0.3000,2.25000),
      vec3(-2.5000,0.0000,2.25000),vec3(-2.7000,0.0000,2.02500),
      vec3(-2.7000,-0.3000,2.02500),vec3(-3.0000,-0.3000,2.25000),
      vec3(-3.0000,0.0000,2.25000),vec3(-2.7000,0.0000,1.80000),
      vec3(-2.7000,-0.3000,1.80000),vec3(-3.0000,-0.3000,1.80000),
      vec3(-3.0000,0.0000,1.80000),vec3(-2.7000,0.0000,1.57500),
      vec3(-2.7000,-0.3000,1.57500),vec3(-3.0000,-0.3000,1.35000),

      vec3(-3.0000,0.0000,1.35000),vec3(-2.5000,0.0000,1.12500),
      vec3(-2.5000,-0.3000,1.12500),vec3(-2.6500,-0.3000,0.93750),
      vec3(-2.6500,0.0000,0.93750),vec3(-2.0000,-0.3000,0.90000),
      vec3(-1.9000,-0.3000,0.60000),vec3(-1.9000,0.0000,0.60000),
      vec3(1.7000,0.0000,1.42500),vec3(1.7000,-0.6600,1.42500),
      vec3(1.7000,-0.6600,0.60000),vec3(1.7000,0.0000,0.60000),
      vec3(2.6000,0.0000,1.42500),vec3(2.6000,-0.6600,1.42500),
      vec3(3.1000,-0.6600,0.82500),vec3(3.1000,0.0000,0.82500),
      vec3(2.3000,0.0000,2.10000),vec3(2.3000,-0.2500,2.10000),
      vec3(2.4000,-0.2500,2.02500),vec3(2.4000,0.0000,2.02500),

      vec3(2.7000,0.0000,2.40000),vec3(2.7000,-0.2500,2.40000),
      vec3(3.3000,-0.2500,2.40000),vec3(3.3000,0.0000,2.40000),
      vec3(2.8000,0.0000,2.47500),vec3(2.8000,-0.2500,2.47500),
      vec3(3.5250,-0.2500,2.49375),vec3(3.5250,0.0000,2.49375),
      vec3(2.9000,0.0000,2.47500),vec3(2.9000,-0.1500,2.47500),
      vec3(3.4500,-0.1500,2.51250),vec3(3.4500,0.0000,2.51250),
      vec3(2.8000,0.0000,2.40000),vec3(2.8000,-0.1500,2.40000),
      vec3(3.2000,-0.1500,2.40000),vec3(3.2000,0.0000,2.40000),
      vec3(0.0000,0.0000,3.15000),vec3(0.8000,0.0000,3.15000),
      vec3(0.8000,-0.4500,3.15000),vec3(0.4500,-0.8000,3.15000),

      vec3(0.0000,-0.8000,3.15000),vec3(0.0000,0.0000,2.85000),
      vec3(1.4000,0.0000,2.40000),vec3(1.4000,-0.7840,2.40000),
      vec3(0.7840,-1.4000,2.40000),vec3(0.0000,-1.4000,2.40000),
      vec3(0.4000,0.0000,2.55000),vec3(0.4000,-0.2240,2.55000),
      vec3(0.2240,-0.4000,2.55000),vec3(0.0000,-0.4000,2.55000),
      vec3(1.3000,0.0000,2.55000),vec3(1.3000,-0.7280,2.55000),
      vec3(0.7280,-1.3000,2.55000),vec3(0.0000,-1.3000,2.55000),
      vec3(1.3000,0.0000,2.40000),vec3(1.3000,-0.7280,2.40000),
      vec3(0.7280,-1.3000,2.40000),vec3(0.0000,-1.3000,2.40000),
      vec3(0.0000,0.0000,0.00000),vec3(1.4250,-0.7980,0.00000),

      vec3(1.5000,0.0000,0.07500),vec3(1.4250,0.0000,0.00000),
      vec3(0.7980,-1.4250,0.00000),vec3(0.0000,-1.5000,0.07500),
      vec3(0.0000,-1.4250,0.00000),vec3(1.5000,-0.8400,0.07500),
      vec3(0.8400,-1.5000,0.07500)
    };  


    const GLuint ixa[16*10] = { 
      118,118,118,118,124,122,119,121,123,126,125,120,40,39,38,37,
      24,25,26,27,29,30,31,32,33,34,35,36,37,38,39,40,
      96,96,96,96,97,98,99,100,101,101,101,101,0,1,2,3,
      102,103,104,105,4,5,6,7,8,9,10,11,12,13,14,15,
      12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
      0,1,2,3,106,107,108,109,110,111,112,113,114,115,116,117,
      41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,
      53,54,55,56,57,58,59,60,61,62,63,64,28,65,66,67,
      68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,
      80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
    };

    cpts = new Buffer(127,vc);
    ix = new IndexBuffer(160,ixa);

    mn = vec3(-4,-4,0);
    mx = vec3(4,4,3);
    center = 0.5f*(mn+mx);
    maxdim = 8;

    va = new VertexArray();
    va->attachAttribute(0,cpts);

    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);


    beginMenu();
    addMenuEntry("Plain",plain);
    addMenuEntry("Patch",patch);
    addMenuEntry("Triangles",tri);
    beginSubMenu("Inner");
    addMenuEntry("1",seti1);
    addMenuEntry("2",seti2);
    addMenuEntry("4",seti4);
    addMenuEntry("8",seti8);
    addMenuEntry("16",seti16);
    addMenuEntry("32",seti32);
    addMenuEntry("64",seti64);
    endSubMenu();
    beginSubMenu("Outer");
    addMenuEntry("1",seto1);
    addMenuEntry("2",seto2);
    addMenuEntry("4",seto4);
    addMenuEntry("8",seto8);
    addMenuEntry("16",seto16);
    addMenuEntry("32",seto32);
    addMenuEntry("64",seto64);
    endSubMenu();
    endMenu();
  }

  /* -------------------------------------- */

  void draw()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    p->setUniform("MV",
		  translate(mat4(),vec3(0.0f,0.0f,-20.0f)) *
		  mat4(getRotation()) *
		  scale(mat4(),vec3(1/maxdim)) *
		  translate(mat4(),vec3(-center[0],-center[1],-center[2]))
		  );
    p->setUniform("N",getRotation());
    p->setUniform("P",perspective(getZoom(),getAspectRatio(),18.0f,22.0f));
    p->setUniform("lloc",vec3(0.0f,10.0f,20.0f));
    p->setUniform("I",0.8f);
    p->setUniform("AI",0.2f);
    p->setUniform("DAC",vec3(0.2f,0.9f,1.0f));
    p->setUniform("ResInner",(float)rinner);
    p->setUniform("ResOuter",(float)router);
    p->setUniform("Kd",0.6f);
    p->setUniform("Ks",0.4f);
    p->setUniform("nspec",200.0f);
    p->setUniform("threshold",0.05f);
    p->setUniform("what",what);

    glPatchParameteri(GL_PATCH_VERTICES, 16);

    p->on();
    va->sendToPipelineIndexed(GL_PATCHES,ix,0,160);
    p->off();

    glFlush();
  }
};

int ViewerEventHandlers::rinner = 1;
int ViewerEventHandlers::router = 1;
int ViewerEventHandlers::what = 1;

/* -------------------------------------- */

int main ( int argc, char *argv[] )
{
  GLUTwrapper(new ViewerEventHandlers(argc,argv)).run();
  return 0;
}
