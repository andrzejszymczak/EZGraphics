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

out vec4 fragcolor;

noperspective in vec3 _wnormal;
noperspective in vec3 _wcoord;

uniform vec3 lloc;
uniform vec3 kd,ka,ks;
uniform float nspec;
uniform vec3 I,Ia;
uniform int reor;
uniform int dfilter;

layout (binding=0) uniform sampler2DShadow depth;

void main() { 

    if (dfilter==1 && texture(depth,vec3(gl_FragCoord.xy/800.0,gl_FragCoord.z)).r==1)
	discard;

    vec3 N = reor*(gl_FrontFacing ? 1 : -1)*normalize(_wnormal);
    vec3 L = normalize(lloc-_wcoord);
    vec3 V = -normalize(_wcoord);
    vec3 H = normalize(L+V);

    float NdotL = dot(N,L);
    float HdotN = dot(H,N);

    if (NdotL<0) NdotL = 0.0;
    if (HdotN<0) HdotN = 0.0;

    fragcolor = vec4(ka*Ia + (kd*NdotL + ks*pow(HdotN,nspec))*I,0.6);
} 
