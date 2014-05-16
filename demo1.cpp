
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

  Program *pgmGouraud, *pgmPhong;
  vec3 mx, mn;
  float maxdim;
  vec3 center;
  IndexBuffer *ix;
  Buffer *vnormal, *vloc;
  VertexArray *vaGouraudPhong;
  int ts;

  enum mode { PHONG, GOURAUD };

  static int reor;
  static mode which;

public:

  /* -------------------------------------- */

  // You probably won't need to change this, except for requesting additional 
  // features for the frame buffer; here, we request RGB+depth buffer and 
  // double buffering.We also ask for 800x800 window.

  ViewerEventHandlers ( int argc, char **argv ) :
    TrackballHandler(argc,argv,GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGB,800,800)
  {
  }

  /* -------------------------------------- */

  // Functions that handle menu items; notice that:
  // (1) all of them take no arguments and return nothing
  // (2) all of them are static
  // Because of (2), they can operate only on static data members.
  // Remember that static data members have to be defined outside the
  // class (see below)

  static void do_Phong()
  {
    which = PHONG;
  }

  static void do_Gouraud()
  {
    which = GOURAUD;
  }

  static void reorient()
  {
    reor = -reor;
  }

  /* -------------------------------------- */

  // this mehtod is called once, after the basic OpenGL/glew/glut setup
  // it's safe to use OpenGL calls here

  virtual void initializeGL()
  {
    // Compile and link GLSL programs. We use separate programs for
    // Gouraud and Phong shading here. For example, the Gouraud vertex
    // shader source is read from the file simple-viewer-shaders/vtxGouraud.glsl
    // and the fragment shader source - from simple-viewer-shaders/frgGouraud.glsl
    // Any GLSL compiler and linker messages are printed into the terminal.
    // For NVIDIA GPUs, you may not see anything printed if all went well.

    cout << "Creating Gouraud program..." << endl;
    pgmGouraud = createProgram(
			       ShaderFile(Vert,"demo1-shaders/vtxGouraud.glsl"),
			       ShaderFile(Frag,"demo1-shaders/frgGouraud.glsl")
			       );
    cout << "Creating Phong program..." << endl;
    pgmPhong = createProgram(
			     ShaderFile(Vert,"demo1-shaders/vtxPhong.glsl"),
			     ShaderFile(Frag,"demo1-shaders/frgPhong.glsl")
			     );

    // Mesh is a helper class for dealing with triangle meshes.
    // Construct a mesh object; this reads the mesh from the file (the argument)
    // getArgv() (inherited from EventHandlerBase) returns the command line arguments

    Mesh M(getArgv()[1]);

    // Get information about the mesh. Methods used here:
    //  getCenter() returns center of the bounding box
    //  get*Corner() returns corners of the bounding box; Upper = (max x coord, max y coord, max z coord),
    //                      Lower = (min x coord, min y coord, min z coord)
    //  getMaxDim(): maximum dimension of the bounding box, or largest value of 
    //            max coord-min coord over all coordinates; rough estimate of size of the mesh
    //  getTriangleCount(), getVertexCount() - return what they say
    //  getVertexTable(): returns vertex table (array of type vec3* with num of entries = #vertices)
    //  getVertexNormals(): returns area weighted vertex normals (array of type vec3*)
    //  getTriangleTable(): returns triangle table, array of type uvec3* with #entries = #triangles
    //                      entries are unsigned so it can be readily used as data for the index buffer 
    // CAUTION: DON'T delete any arrays returned by the methods of the mesh class! Or you'll corrupt 
    //            your mesh object

    center = M.getCenter();
    mx = M.getUpperCorner();
    mn = M.getLowerCorner();
    maxdim = M.getMaxDim();
    ts = M.getTriangleCount();

    // Buffer class represents OpenGL Vertex Buffer Objects (VBOs), basically arrays residing 
    //  in the GPU memory.
    // The constructor creates a buffer object and sends data to it.
    // Versions of the constructor used here take #entries of an array as the first argument and
    //  the pointer to the array as the second argument (that pointer can be of type 
    //  ivec[234]*, uvec[234]* or vec[234]*).

    vloc = new Buffer(M.getVertexCount(),M.getVertexTable());
    vnormal = new Buffer(M.getVertexCount(),M.getVertexNormals());
    
    // IndexBuffer class represent index buffer objects; Note that they are required to have
    //  entries of an unsigned integer type.
    // create an index buffer; first entry: size of array, second: array (types allowed:
    //  GLubyte*, GLuint*, GLushort*, uvec2*, uvec3*)

    ix = new IndexBuffer(M.getTriangleCount(),M.getTriangleTable());

    // Build a vertex array object (VAO; they are represented by VertexArray class).
    // Basically, a VAO tells the system where to find attributes for a vertex.
    // Here, (after creating an empty VAO) we tell it to look up attribute #0 from the 
    //  buffer vloc and attribute #1 - from the buffer vnormal. These have to match the location 
    //  layout qualifier in the vertex shader. In our case, we have these lines in the vertex shaders:
    //   layout(location=0) in vec3 coord;  [for vertex i, use vloc[i] as value]
    //   layout(location=1) in vec3 normal; [ ... use vnormal[i] as value]

    vaGouraudPhong = new VertexArray;
    vaGouraudPhong->attachAttribute(0,vloc);
    vaGouraudPhong->attachAttribute(1,vnormal); 

    // enable culling and depth test; use white when clearing the color buffer

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    // Build menu; the code is set up so that it is automatically attached to the right mouse button
    // It should clear what happens here (try to run the code and press the right mouse button
    //  over the window). If I got everything right, you should get an error if the menus/submenus
    //  are not properly nested. The second argument of addMenuEntry is a name of the function
    //  that is called when that entry is selected. Because of the requirements of the freeglut
    //  library this is based on, this has to be a function that has a well-defined address
    //  (e.g. a static method). See one of the comments above.

    beginMenu();
    beginSubMenu("Shading");
    addMenuEntry("Gouraud",do_Gouraud);
    addMenuEntry("Phong",do_Phong);
    endSubMenu();
    addMenuEntry("Reorient",reorient);
    endMenu();
  }

  /* -------------------------------------- */

  // This method is called to redraw the contents of the window.
  // In this version of the code, it's called continuously to 
  //  estimate fps rate.

  virtual void draw()
  {
    // clear color & depth buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // make p point to the program we want to use...

    Program *p = NULL;
    switch(which)
      {
      case GOURAUD: p = pgmGouraud; break;
      case PHONG: p = pgmPhong; break;
      }

    // Reverse orientation in case the model's triangles are oriented incorrectly.
    // Back and front face culling are just names for <0 or >0 test performed when
    // deciding if the face should be culled. Note that if front face culling is used,
    // normals are also reversed before illumination calculations (in the shaders).

    if (reor>0)
      glCullFace(GL_BACK);
    else
      glCullFace(GL_FRONT);
    
    // Here, we set values of the uniform variables in the shader.
    // MV = modelview matrix
    // P = projection matrix
    // NM = normal matrix
    // getRotation() and getAspectRatio() are inherited from TrackballHandler and EventHandlerBase.
    //  getRotation returns the rotation (type: mat3, 3x3 matrix), obtained from the trackball.
    // getAspectRatio() = width/height of the window.
    // getZoom is also inherited from TrackballHandler (FOV controlled by the middle mouse button)

    // MV first transforms the model so that its bounding box tightly fits into the cube 
    //  extending from -1 to 1 in all dimensions; then rotates and moves 'forward' by 20 with
    //  respect to the camera.

    p->setUniform("MV",
		    translate(mat4(),vec3(0.0f,0.0f,-20.0f)) *
		    mat4(getRotation()) *
		    scale(mat4(),vec3(1/maxdim)) *
		    translate(mat4(),-center)
		  );

    // this matrix is used to transform normals; basically, rotate them with the mesh

    p->setUniform("NM",getRotation());

    // place camera at the origin, facing -z; near/far clip planes 18 and 22 away.

    p->setUniform("P",perspective(getZoom(),getAspectRatio(),18.0f,22.0f));

    // send light and material data to uniforms

    p->setUniform("lloc",vec3(0.0,0.0,1.0));
    p->setUniform("kd",vec3(0.5,0.7,0.9));
    p->setUniform("ka",vec3(0.5,0.7,0.9));
    p->setUniform("ks",vec3(0.3,0.3,0.3));
    p->setUniform("I",vec3(0.8,0.8,0.8));
    p->setUniform("Ia",vec3(0.2,0.2,0.2));
    p->setUniform("nspec",1000.0f);

    // reor can be +-1 and is used to reverse the normal direction if front face culling is used

    p->setUniform("reor",reor);

    // turn program p on

    p->on();

    // send the vertices to the pipeline (indexed mode; use triangle table as index)

    vaGouraudPhong->sendToPipelineIndexed(GL_TRIANGLES,ix,0,3*ts);

    // turn program off

    p->off();
  }

  /* -------------------------------------- */

  // This method is called when the user presses ESC over the window.
  // Here, we nicely delete all OpenGL objects used; It's OK if you 
  // let the OS do it for you!

  virtual void cleanup()
  {
    cout << "cleaning up..." << endl;
    delete pgmGouraud;
    delete pgmPhong;
    delete ix;
    delete vnormal;
    delete vloc;
    delete vaGouraudPhong;
  }

  /* -------------------------------------- */

};

/* -------------------------------------- */

// definitions of static members - if you add more, include them here

ViewerEventHandlers::mode ViewerEventHandlers::which = ViewerEventHandlers::PHONG;
int ViewerEventHandlers::reor = 1.0;

/* -------------------------------------- */

// you probably want to keep this main function intact

int main ( int argc, char *argv[] )
{
  if (argc<=1) {
    cerr << "Usage: demo1 <.t file>" << endl;
    return 1;
  }
  GLUTwrapper(new ViewerEventHandlers(argc,argv)).run();
  return 0;
}
