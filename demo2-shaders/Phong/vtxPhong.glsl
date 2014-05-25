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

// inputs are the same as in the Gouraud shader

layout(location=0) in vec3 coord;  
layout(location=1) in vec3 normal; 

// we won't be evaluating the Phong's formula here,
// so all we need is the transformation matrices
// (we still need to do transformations!) 

uniform mat4 MV; 
uniform mat4 P; 
uniform mat3 NM;

// output world coordinates and normals (also transformed to 
//  world coordinates) - we need this info on the fragment 
//  processing stage to evaluate the Phong's formula

noperspective out vec3 _wcoord;
noperspective out vec3 _wnormal;

void main()
{
    // transform locations and normals to world coordinates
    // and put the results into the output variables

    vec4 wcoord = MV*vec4(coord,1.0);
    _wcoord = wcoord.xyz;
    _wnormal = normalize(NM*normal);

    // cf vtxGouraud.glsl

    gl_Position = P*wcoord;
} 
