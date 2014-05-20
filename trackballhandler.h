#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <buffer.h>
#include <vertexarray.h>
#include <program.h>
#include <handlerbase.h>

#pragma once

namespace EZGraphics {

  /* -------------------------------------- */

  /** Provides a set of event handlers that define a simple trackball interface. Left mouse button is used for rotation, middle mouse button is used for zooming in and out. */
  class TrackballHandler : public EventHandlerBase {

    class Trackball {

      glm::mat3 R;     // finished rotations
      glm::mat3 R0;    // current rotation
      glm::mat3 R0R;

      int winsize[2];  // window size

      bool ismousedown;  // true if dragging
      glm::vec3 last;  // last mouse down event

      glm::vec3 _ij2xyz ( float i, float j );

    public:
    
      Trackball ( int sx, int sy );
      void resize ( int sx, int sy );
  
      void mouseDown ( int i, int j );
      void mouseMove ( int i, int j );
      void mouseUp ( int i, int j );

      glm::mat3 rotation();  // the rotation matrix 
      
      bool isActive();   // is mouse button down?
    };

    Trackball *t;
    float zoom;
    int lasty;

  public:

    TrackballHandler ( int argc, char **argv, unsigned int mode, int width = 800, int height = 800 );

    virtual void motionWithLeftButtonDown ( int mx, int my );
    virtual void motionWithMiddleButtonDown ( int mx, int my );
    virtual void leftMouseButtonDown ( int mx, int my );
    virtual void leftMouseButtonUp ( int mx, int my );
    virtual void middleMouseButtonDown ( int mx, int my );
    virtual void resize ( int sizex, int sizey );

    /** \return the rotation matrix specified by the trackball interface */
    glm::mat3 getRotation();

    /** current zoom level */
    float getZoom();
  };

  /* -------------------------------------- */

};
