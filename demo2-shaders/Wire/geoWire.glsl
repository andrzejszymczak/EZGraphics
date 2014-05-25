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

layout (triangles) in;
layout (triangle_strip, max_vertices = 8) out;

uniform mat4 P;
uniform vec3 lloc;
uniform vec3 kd,ka,ks;
uniform float nspec;
uniform vec3 I,Ia;
uniform int reor;

in vec3 _wcoord[3];

flat out vec3 _fragcolor;

const float width = 0.25;

void main()
{
    vec3 N = reor*normalize(cross(_wcoord[1]-_wcoord[0],_wcoord[2]-_wcoord[0]));
    vec3 barycenter = (_wcoord[0]+_wcoord[1]+_wcoord[2])/3;
    vec3 L = normalize(lloc-barycenter);
    vec3 V = -normalize(barycenter);
    vec3 H = normalize(L+V);

    float NdotL = dot(N,L);
    float HdotN = dot(H,N);
    if (NdotL<0) NdotL = 0.0;
    if (HdotN<0) HdotN = 0.0;

    vec3 color = ka*Ia + (kd*NdotL + ks*pow(HdotN,nspec))*I;

    // note that 4 iterations are used here since we want to close the tri-strip
    // that follows the boundary of the triangle - to do that, we repeat the
    // first two vertices at the end

    for ( int i=0; i<4; i++ )
    {
      // vertex #(i mod 3) moved toward the center of the triangle...
      _fragcolor = color;
      gl_Position = P*vec4(_wcoord[i%3]+width*(barycenter-_wcoord[i%3]),1);
      EmitVertex();

      // ... and the original vertex 
      _fragcolor = color;
      gl_Position = P*vec4(_wcoord[i%3],1);
      EmitVertex();
    }
    EndPrimitive();
}
