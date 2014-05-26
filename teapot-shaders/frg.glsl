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
 
in vec3 normal;  
in vec3 coords; 
in vec2 dst;
in vec3 tdst;

out vec4 fragcolor;
 
uniform float I;
uniform float AI; 
uniform vec3 DAC;  
uniform vec3 lloc;
uniform float Kd, Ks;
uniform float nspec;
uniform float threshold;
uniform int what;

float get_multiplier ( float s, float a, float b, float c ) {
  float mn = min(a,min(b,c));
  return clamp(s*(mn-threshold)+0.75,0,1);
}

void main() { 
	vec3 dac = vec3(0,0,0);
	if (what==1)
	  dac = get_multiplier(100,1-2*abs(0.5-dst[0]),1-2*abs(dst[1]-0.5),1)*DAC;
/*
	  if (1-2*abs(0.5-dst[0])<threshold || 1-2*abs(dst[1]-0.5)<threshold)
		dac = DAC;
	  else
		dac = 0.25*DAC;
		*/
	if (what==0)
	  dac = get_multiplier(1,tdst.x,tdst.y,tdst.z)*DAC;
	/*
	  if (tdst.x<threshold || tdst.y<threshold || tdst.z<threshold)
		dac = DAC;
	  else
		dac = 0.25*DAC;
		*/
	if (what==2) dac = DAC;
	vec3 N = normalize(normal);
	vec3 L = normalize(lloc-coords);
	vec3 V = normalize(-coords);
	vec3 H = normalize(L+V);
  	float NdotL = dot(N,L);
	float HdotN = dot(N,H);
	if (HdotN<0) HdotN = 0;
	if (NdotL<0) NdotL = 0;

	fragcolor = vec4( (I*(Kd*(NdotL > 0.0 ? NdotL : 0.0) + Ks*pow(HdotN,nspec)) + AI) * dac, 1);  
}

