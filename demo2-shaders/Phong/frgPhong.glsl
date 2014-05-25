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

// final color

out vec3 fragcolor;

// input variables, matching the outputs of the vertex shader

noperspective in vec3 _wnormal;
noperspective in vec3 _wcoord;

// light/material data

uniform vec3 lloc;
uniform vec3 kd,ka,ks;
uniform float nspec;
uniform vec3 I,Ia;
uniform int reor;

void main() { 

    // this is basically the same as code in vtxGouraud.glsl,
    // but we use interpolated values of coordinates/normals 
    // in the world coordinates

    vec3 N = reor*normalize(_wnormal);
    vec3 L = normalize(lloc-_wcoord);
    vec3 V = -normalize(_wcoord);
    vec3 H = normalize(L+V);

    float NdotL = dot(N,L);
    float HdotN = dot(H,N);

    if (NdotL<0) NdotL = 0.0;
    if (HdotN<0) HdotN = 0.0;

    fragcolor = ka*Ia + (kd*NdotL + ks*pow(HdotN,nspec))*I;
} 
