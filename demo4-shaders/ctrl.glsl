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

/* 
TESSELATION CONTROL SHADER:
- For each patch, invoked once per vertex (in other words, if the patch has N vertices,
   it is invoked N times for that patch); gl_InvocationID provides the index of the
   vertex within the patch. 
- In the project, you'll also find the built-in variable gl_PrimitiveID useful (it
   provides the patch number - first patch you send into the pipeline is 0, next - 1
   etc). This value can be used to figure out what kind of symmetry (2-fold or 4-fold)
   needs to be applied to a particular patch.
*/

/* 
Our patches have 4 vertices; There will be 16 for bicubic Bezier patches 
*/
layout(vertices=4) out;

/* 
We are using uniforms to request tesselation granularity from the C code;
A more realistic scenario is to vary the resolution based on the estimated size
of the projection of the patch onto the screen 
*/
uniform float ResInner;
uniform float ResOuter;

void main ()
{
	/* 
	gl_in[].gl_Position is the gl_Position output from the vertex shader.
	Here, we just copy it to the respective output variable. This line should
	also work for your project.
	gl_in and gl_out are arrays with # of entries = # vertices in a patch.
	However, there are restrictions on writes to the output variables - basically,
	one can only use gl_InvocationID index. Also, reading from output variables 
	assigned by other invocations is possible but requires synchronization. See
	http://www.opengl.org/wiki/Tessellation_Control_Shader for more details
	*/
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	/*
	gl_TessLevel* control the tesselation level on the boundary (outer) and in
	the interior of the patch (inner)
	*/
	gl_TessLevelOuter[0] = float(ResOuter);
	gl_TessLevelOuter[1] = float(ResOuter);
	gl_TessLevelOuter[2] = float(ResOuter);
	gl_TessLevelOuter[3] = float(ResOuter);
	gl_TessLevelInner[0] = float(ResInner);
	gl_TessLevelInner[1] = float(ResInner);
}
