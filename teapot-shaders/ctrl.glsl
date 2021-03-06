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

#version 400

layout(vertices=16) out;

in vec3 ocoord[16];
out vec4 vcoord[16];

uniform float ResInner;
uniform float ResOuter;

void main ()
{
	vcoord[gl_InvocationID] = vec4(ocoord[gl_InvocationID],1); 

   	gl_TessLevelOuter[0] = float(ResOuter);
	gl_TessLevelOuter[1] = float(ResOuter);
	gl_TessLevelOuter[2] = float(ResOuter);
	gl_TessLevelOuter[3] = float(ResOuter);
	gl_TessLevelInner[0] = float(ResInner);
	gl_TessLevelInner[1] = float(ResInner);
}
