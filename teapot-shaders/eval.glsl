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

layout(quads) in;

out vec3 wnormal;
out vec4 wcoords;
out vec2 uv;
out int xsym;

in vec4 vcoord[];

void evaluate ( float t, out float v[4], out float dv[4] )
{

	float tp = 1-t;
	float tp2 = tp*tp;
	float t2 = t*t;
	
	v[0] = tp2*tp;
	v[1] = 3*tp2*t;
	v[2] = 3*t2*tp;
	v[3] = t*t2;

	dv[0] = -3*tp2;
	dv[1] = -dv[0]-6*t*tp;
	dv[2] = 6*t*tp-3*t2;
	dv[3] = 3*t2;
}

void main ()
{
	vec4 p00 = vcoord[0];
	vec4 p01 = vcoord[1];
	vec4 p02 = vcoord[2];
	vec4 p03 = vcoord[3];
	vec4 p10 = vcoord[4];
	vec4 p11 = vcoord[5];
	vec4 p12 = vcoord[6];
	vec4 p13 = vcoord[7];
	vec4 p20 = vcoord[8];
	vec4 p21 = vcoord[9];
	vec4 p22 = vcoord[10];
	vec4 p23 = vcoord[11];
	vec4 p30 = vcoord[12];
	vec4 p31 = vcoord[13];
	vec4 p32 = vcoord[14];
	vec4 p33 = vcoord[15];

	xsym = (gl_PrimitiveID<6 ? 1 : 0);

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	float U[4], V[4], dU[4], dV[4];

	evaluate(u,U,dU);
	evaluate(v,V,dV);

	uv = vec2(u,v);

	vec4 p0 = U[0]*p00 + U[1]*p01 + U[2]*p02 + U[3]*p03;
	vec4 p1 = U[0]*p10 + U[1]*p11 + U[2]*p12 + U[3]*p13;
	vec4 p2 = U[0]*p20 + U[1]*p21 + U[2]*p22 + U[3]*p23;
	vec4 p3 = U[0]*p30 + U[1]*p31 + U[2]*p32 + U[3]*p33;
	vec4 dp0 = dU[0]*p00 + dU[1]*p01 + dU[2]*p02 + dU[3]*p03;
	vec4 dp1 = dU[0]*p10 + dU[1]*p11 + dU[2]*p12 + dU[3]*p13;
	vec4 dp2 = dU[0]*p20 + dU[1]*p21 + dU[2]*p22 + dU[3]*p23;
	vec4 dp3 = dU[0]*p30 + dU[1]*p31 + dU[2]*p32 + dU[3]*p33;

	vec4 p = V[0]*p0 + V[1]*p1 + V[2]*p2 + V[3]*p3;
	vec4 d0p = V[0]*dp0 + V[1]*dp1 + V[2]*dp2 + V[3]*dp3;
	vec4 d1p = dV[0]*p0 + dV[1]*p1 + dV[2]*p2 + dV[3]*p3;

	wnormal = cross(d0p.xyz,d1p.xyz);
	wcoords = p;
}
