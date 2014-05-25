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

// input attributes

layout(location=0) in vec3 coord;  
layout(location=1) in vec3 normal; 
 
// uniform variables - values are fixed for any given 
// vertex stream

uniform mat4 MV; 
uniform mat4 P; 
uniform mat3 NM;
uniform vec3 lloc;
uniform vec3 kd,ka,ks;
uniform float nspec;
uniform vec3 I,Ia;
uniform int reor;

// output variable - recall it will be interpolated and 
//  made available for the fragment program as input    
// the name reflects what it will become as a result of 
//  interpolation 
// 'noperspective' is the interpolation qualifier, meaning
//   linear interpolation in screen space
// Use 'flat' and 'smooth' for flat and perspectively correct
//  interpolation schemes; 
// IMPORTANT: you have to use identical interpolation
//  qualifier for the input variable with the same name
//  in the fragment shader, unless you want a linker error :)

noperspective out vec3 _fragcolor;

// this function is executed for every vertex ... 

void main()
{
    // transform to world coordinates... 
    //  note that coord is vec3 and we set up M as 4x4 matrix, so
    //  we need to add homogenous coordinate of 1 to coord before 
    //  transforming it with MV

    vec4 wcoord = MV*vec4(coord,1.0);

    // compute all vectors needed for the Phong illumination 
    // note that when computing V, we use (0,0,0) as the lovation of the
    // viewer - this is consistent with our projection matrix
    // reor is +1 or -1, depending on whether front or back
    //  face culling is used

    vec3 N = reor*normalize(NM*normal);
    vec3 L = normalize(lloc-wcoord.xyz);
    vec3 V = -normalize(wcoord.xyz);
    vec3 H = normalize(L+V);

    //  ... and the dot products; clamp to [0...] - negative 
    // intensity contributions don't make sense

    float NdotL = dot(N,L);
    float HdotN = dot(H,N);
    if (NdotL<0) NdotL = 0.0;
    if (HdotN<0) HdotN = 0.0;

    // put the resulting color into our only output variable

    _fragcolor = ka*Ia + (kd*NdotL + ks*pow(HdotN,nspec))*I;

    // vertex shader is REQUIRED to write a value into the 
    // built in output variable gl_Position (of type vec4).
    // this info is used by the rasterizer.
    // the value should be the processed vertex location
    // in homogenous coordinates. just apply the projection 
    // matrix to the world coordinates.

    gl_Position = P*wcoord;
} 
