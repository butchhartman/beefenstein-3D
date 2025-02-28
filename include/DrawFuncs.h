#pragma once

#include"cglm/cglm.h"
#include"../include/GL3W/GL/gl3w.h"


/* Loads the provided vertices into the VBO and calls the point to be drawn to the screen.
   Currently no color support.
   Performance implications of loading data to the buffer each frame and using the same VBO for multiple points must
   be studied further.
   PointCoordinate should be in clip space coordinates
   */
void drawPoint(vec3 pointCoordinate, GLuint vbo);


/* Loads coordinate data into the VBO and draws the line defined by them to the screen.
   Currently no color support.
   Performance implications of loading data to the buffer each frame and using the same VBO for multiple points must
   be studied further
   Line start and lineEnd should be given as clip space coordinates
   */
void drawLine(vec3 lineStart, vec3 lineEnd, GLuint vbo);