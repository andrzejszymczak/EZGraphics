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

// output fragment color
out vec3 color;

// coordinates of the fragment in range [0,1]
noperspective in vec2 loc;

// This is how you declare texture variables, called samplers
//  since you can sample values from them. binding=1 means that
//  tex can be used to sample texture with TAP #1 
//  (cf t->bind(1) in the C++ code). Generally, you can use more 
//  than 1 sampler in a shader, but here (and in your shadow program) 
//  one will be enough.
layout (binding=1) uniform sampler2D tex;

void main() { 
	
	// Use the texture() function to look up color from texture.
	// First argument: sampler, second argument: texture coordinates.
	// For regular samplers, opposite texture corners correspond
        // to texture coordinates (0,0) and (1,1); this is why we scaled 
	// the coordinates to [0,1] range in the vertex shader.
	color = texture(tex,loc).rgb;
} 
