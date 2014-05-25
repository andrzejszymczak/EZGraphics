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
#version 420
#extension GL_EXT_geometry_shader4 : enable

// See the geoFlat shader for explanation of the technicalities.

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

uniform mat4 P;
//uniform int reor;

in vec3 _wcoord[3];
in vec3 _wnormal[3];

noperspective out vec3 _wnormal2;
noperspective out vec3 _wcoord2;

// this will allow us to distinguish the original and the 
// symmetric copy and use a different color for each

flat out int which;

void main()
{

  // send the original triangle first...

  for ( int i=0; i<3; ++i )
  {
    which = 0;
    _wnormal2 = _wnormal[i];
    _wcoord2 = _wcoord[i];
    gl_Position = P*vec4(_wcoord[i],1);
    EmitVertex();
  }
  EndPrimitive();

  // .. and the symmetric image (about y=0)
  // note that we reverse the orientation here since a planar symmetry
  // reverses it.

  for ( int i=2; i>=0; --i )
  {
    which = 1;
    _wnormal2 = vec3(1,-1,1) * _wnormal[i];
    vec3 wcoordsym = vec3(1,-1,1) * _wcoord[i];
    _wcoord2 = wcoordsym;
    gl_Position = P*vec4(wcoordsym,1);
    EmitVertex();
  }
  EndPrimitive();

}
