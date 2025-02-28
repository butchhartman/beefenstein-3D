#pragma once

#include "cglm/cglm.h"

// Is it a better idea to have point and line be a table of floats?

typedef struct {
	vec3 vertexCoordinates;
	vec3 vColor;
} Point;

typedef struct {
	vec3 vertexStart;
	vec3 vertexEnd;
	vec3 vColor1;
	vec3 vColor2;
} Line;


/* For some reason, triangles must initialized as follows : 
   Triangle tri = { 0 };
   Otherwise nothing will be drawn to the screen when passed to its drawing function.
 */
typedef struct {
	vec3 v1;
	vec3 v2;
	vec3 v3;

	vec3 vColor1;
	vec3 vColor2;
	vec3 vColor3;
} Triangle;