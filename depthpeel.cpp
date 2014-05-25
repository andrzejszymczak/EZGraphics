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
#include <texture.h>
#include <framebuffer.h>

using namespace std;
using namespace glm;
using namespace EZGraphics;

/* -------------------------------------- */

class ViewerEventHandlers : public TrackballHandler, public MenuCreator {

  Program *pgmPhong, *pgmQuad;
  vec3 mx, mn;
  float maxdim;
  vec3 center;
  IndexBuffer *ix;
  Buffer *vnormal, *vloc, *q;
  VertexArray *vaGouraudPhong, *vaQuad;
  int ts;
  Texture *(tex_depth[2]), *tex_color;
  Framebuffer *fb;
  int texsize;
  static int reor;
  static int layer;
  GLuint query;
  static bool naive;

public:

  ViewerEventHandlers ( int argc, char **argv ) :
    TrackballHandler(argc,argv,GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGB|GLUT_ALPHA,800,800)
  {
  }

  /* -------------------------------------- */

  static void reorient()
  {
    reor = -reor;
  }

  static void next_layer()
  {
    layer += 1;
  }

  static void do_naive()
  {
    naive = true;
  }

  static void do_peel()
  {
    naive = false;
  }

  static void toggle_layer()
  {
    layer = (layer>=0 ? -1 : 0);
  }

  static void previous_layer()
  {
    layer -= 1;
    if (layer<0) layer=0;
  }

  virtual void keyPressed ( unsigned char key, int x, int y )
  {
    if (!naive)
      switch(key)
	{
	case 'n':
	case 'N': 
	  next_layer(); break;
	case 'p':
	case 'P': 
	  previous_layer(); break;
	case 'l':
	case 'L': 
	  toggle_layer(); break; 
	}
    TrackballHandler::keyPressed(key,x,y);
  }
  

  /* -------------------------------------- */

  void initializeGL()
  {

    vec2 qbuf[4];
    qbuf[0] = vec2(-1,-1);
    qbuf[1] = vec2(1,-1);
    qbuf[2] = vec2(-1,1);
    qbuf[3] = vec2(1,1);

    Buffer *q = new Buffer(4,qbuf);
    vaQuad = new VertexArray;
    vaQuad->attachAttribute(0,q);

    pgmPhong = Program::createProgram(ShaderFile(Vert,"dpeel-shaders/vtxPhong.glsl"),
				      ShaderFile(Frag,"dpeel-shaders/frgPhong.glsl"));
    pgmQuad = Program::createProgram(ShaderFile(Vert,"dpeel-shaders/vtxQuad.glsl"),
				     ShaderFile(Frag,"dpeel-shaders/frgQuad.glsl"));

    Mesh M(getArgv()[1]);

    center = M.getCenter();
    mx = M.getUpperCorner();
    mn = M.getLowerCorner();
    maxdim = M.getMaxDim();
    ts = M.getTriangleCount();

    vloc = new Buffer(M.getVertexCount(),M.getVertexTable());
    vnormal = new Buffer(M.getVertexCount(),M.getVertexNormals());
    ix = new IndexBuffer(M.getTriangleCount(),M.getTriangleTable());

    vaGouraudPhong = new VertexArray();
    vaGouraudPhong->attachAttribute(0,vloc);
    vaGouraudPhong->attachAttribute(1,vnormal); 

    glDisable(GL_CULL_FACE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    texsize = 800;
    fb = new Framebuffer;
    tex_depth[0] = new Texture(Depth,texsize,texsize);   // clear
    tex_depth[1] = new Texture(Depth,texsize,texsize);
    tex_color = new Texture(RGBA,texsize,texsize);
    fb->attachDepth(tex_depth[0]);

    glClearDepth(1.0);
    fb->attachColor(tex_color);
    tex_color->bind(1);
    tex_depth[0]->nearest();
    tex_depth[1]->nearest();
    tex_color->nearest();

    beginMenu();
    addMenuEntry("Peeling",do_peel);
    addMenuEntry("Naive",do_naive);
    endMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glGenQueries(1,&query);
  }

  /* -------------------------------------- */

  void draw()
  {    
    static int counter = 0;
    counter++;

    if (naive)
      {
	glClearDepth(1.0);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      }
    else
      {
	glClearDepth(0.0);
	fb->attachDepth(tex_depth[0]);
	fb->on();
	glClear(GL_DEPTH_BUFFER_BIT);
	fb->off();
	glClearDepth(1.0);
	glEnable(GL_BLEND);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
      }

    Program *p = NULL;

    p = pgmPhong;
    
    p->setUniform("MV",
		    translate(mat4(),vec3(0.0f,0.0f,-20.0f)) *
		    mat4(getRotation()) *
		    scale(mat4(),vec3(1/maxdim)) *
		    translate(mat4(),vec3(-center[0],-center[1],-center[2]))
		  );
    p->setUniform("NM",getRotation());
    p->setUniform("P",perspective(getZoom(),getAspectRatio(),18.0f,22.0f));

    p->setUniform("lloc",vec3(0.0,0.0,1.0));
    p->setUniform("kd",vec3(0.5,0.7,0.9));
    p->setUniform("ka",vec3(0.5,0.7,0.9));
    p->setUniform("ks",vec3(0.3,0.3,0.3));
    p->setUniform("I",vec3(0.8,0.8,0.8));
    p->setUniform("Ia",vec3(0.2,0.2,0.2));
    p->setUniform("nspec",1000.0f);
    p->setUniform("reor",reor);

    if (naive)
      {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	p->setUniform("dfilter",0);
	p->on();
	vaGouraudPhong->sendToPipelineIndexed(GL_TRIANGLES,ix,0,3*ts);
	p->off();
	glDisable(GL_BLEND);
	return;
      }

    int i;

    p->setUniform("dfilter",1);

    for ( i=0; ; i++ )
      {
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	fb->attachDepth(tex_depth[(i+1)%2]);
	tex_depth[i%2]->bind(0);

	// tex_depth is currently bound to GL_TEXTURE_2D; the binding occurs in the bind() method
	// below, additional paramteters are set for that texture

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);

	p->on();
	fb->on();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBeginQuery(GL_SAMPLES_PASSED,query);
	vaGouraudPhong->sendToPipelineIndexed(GL_TRIANGLES,ix,0,3*ts);
	glEndQuery(GL_SAMPLES_PASSED);
	p->off();
	fb->off();

	do {
	  GLint val;
	  glGetQueryObjectiv(query,GL_QUERY_RESULT_AVAILABLE,&val);
	  if (val==GL_TRUE) 
	      break;
	} while(1);

	GLint pixels;
	glGetQueryObjectiv(query,GL_QUERY_RESULT,&pixels);
	if (counter%100==0) cout << ((i==0) ? "\n" : "") << "Fragments rendered into layer " << i << ": " << pixels << endl;
	if (pixels==0) 
	  {
	    pgmQuad->setUniform("white",1);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_ONE);
	    glDisable(GL_DEPTH_TEST);
	    pgmQuad->on();
	    vaQuad->sendToPipeline(GL_TRIANGLE_STRIP,0,4);
	    pgmQuad->off();
	    pgmQuad->setUniform("white",0);
	    glEnable(GL_DEPTH_TEST);
	    glDisable(GL_BLEND);
	    
	    return;
	  }
	if (i==layer) goto label;

	tex_depth[(i+1)%2]->bind(0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_NONE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_ONE);
	glDisable(GL_DEPTH_TEST);
	glViewport(0,0,getWindowWidth(),getWindowHeight());
	pgmQuad->on();
	vaQuad->sendToPipeline(GL_TRIANGLE_STRIP,0,4);
	pgmQuad->off();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
      }

    return;

  label:

    tex_depth[i%2]->bind(0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_NONE);
    glDisable(GL_DEPTH_TEST);
    glViewport(0,0,getWindowWidth(),getWindowHeight());
    pgmQuad->on();
    vaQuad->sendToPipeline(GL_TRIANGLE_STRIP,0,4);
    pgmQuad->off();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
  }

};

int ViewerEventHandlers::reor = 1.0;
int ViewerEventHandlers::layer = -1;
bool ViewerEventHandlers::naive = true;

/* -------------------------------------- */

int main ( int argc, char *argv[] )
{
  if (argc<=1) {
    cerr << "Usage: demo1 <.t file>" << endl;
    return 1;
  }
  cout << "Use the popup menu (press right mouse button over the window) to switch between the naive transparency and depth peeling" << endl;
  cout << "Keyboard events in the depth peeling mode: " << endl;
  cout << "    L/l: switch between layer view and transparent rendering" << endl;
  cout << "    N/n: show the next layer" << endl;
  cout << "    P/p: go to the previous layer" << endl;
  cout << "    N/n/P/p enter the layer view if in the depth peeling mode; use L/l to go back to depth peeled image" << endl;
  GLUTwrapper(new ViewerEventHandlers(argc,argv)).run();
  return 0;
}
