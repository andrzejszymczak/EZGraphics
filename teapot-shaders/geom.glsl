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
#extension GL_EXT_geometry_shader4 : enable


layout (triangles) in;
layout (triangle_strip, max_vertices=12) out;

in vec3 wnormal[3];
in vec4 wcoords[3];
in int xsym[3];
in vec2 uv[3];

out vec3 normal;
out vec3 coords;
out vec2 dst;
out vec3 tdst;

uniform mat4 P;
uniform mat4 MV; 
uniform mat3 N; 

void main(void)
{

	for ( int i=0; i<3; i++ )
	{
		tdst = vec3(0);
		tdst[i] = 1;
		dst = uv[i];
		coords = (MV*wcoords[i]).xyz;
		normal = N*wnormal[i];
		gl_Position = P*MV*wcoords[i];
		EmitVertex();
	}
	EndPrimitive();
	
	dst = uv[1];
	tdst = vec3(0,1,0);
	vec4 sc = wcoords[1];
	sc.y = -sc.y;
	coords = (MV*sc).xyz;
	normal = wnormal[1];
	normal.y = -normal.y;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	tdst = vec3(1,0,0);
	dst = uv[0];
	sc = wcoords[0];
	sc.y = -sc.y;
	coords = (MV*sc).xyz;
	normal = wnormal[0];
	normal.y = -normal.y;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	tdst = vec3(0,0,1);
	dst = uv[2];
	sc = wcoords[2];
	sc.y = -sc.y;
	coords = (MV*sc).xyz;
	normal = wnormal[2];
	normal.y = -normal.y;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	EndPrimitive();

	if (xsym[0]==0)
		return;

	tdst = vec3(0,1,0);
	dst = uv[1];
	sc = wcoords[1];
	sc.x = -sc.x;
	coords = (MV*sc).xyz;
	normal = wnormal[1];
	normal.x = -normal.x;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	tdst = vec3(1,0,0);
	dst = uv[0];
	sc = wcoords[0];
	sc.x = -sc.x;
	coords = (MV*sc).xyz;
	normal = wnormal[0];
	normal.x = -normal.x;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	tdst = vec3(0,0,1);
	dst = uv[2];
	sc = wcoords[2];
	sc.x = -sc.x;
	coords = (MV*sc).xyz;
	normal = wnormal[2];
	normal.x = -normal.x;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	EndPrimitive();

	tdst = vec3(1,0,0);
	dst = uv[0];
	sc = wcoords[0];
	sc.xy = -sc.xy;
	coords = (MV*sc).xyz;
	normal = wnormal[0];
	normal.xy = -normal.xy;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	tdst = vec3(0,1,0);
	dst = uv[1];
	sc = wcoords[1];
	sc.xy = -sc.xy;
	coords = (MV*sc).xyz;
	normal = wnormal[1];
	normal.xy = -normal.xy;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	tdst = vec3(0,0,1);
	dst = uv[2];
	sc = wcoords[2];
	sc.xy = -sc.xy;
	coords = (MV*sc).xyz;
	normal = wnormal[2];
	normal.xy = -normal.xy;
	normal = N*normal;
	gl_Position = P*MV*sc;
	EmitVertex();

	EndPrimitive();
}
