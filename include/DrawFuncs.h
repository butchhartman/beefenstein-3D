#pragma once

#include"cglm/cglm.h"
#include"../include/GL3W/GL/gl3w.h"
#include "CommonDefs.h"

// General consensus with these functions is that the performance is not very good due to the CPU having to write to the GPU buffer each frame.


/* Loads the provided vertices into the VBO and calls the point to be drawn to the screen.
   Performance implications of loading data to the buffer each frame and using the same VBO for multiple points must
   be studied further.
   PointCoordinate should be in clip space coordinates
 */
void drawPoint(Point point, GLuint vbo);


/* Loads coordinate data into the VBO and draws the line defined by them to the screen.
   Performance implications of loading data to the buffer each frame and using the same VBO for multiple points must
   be studied further
   Line start and lineEnd should be given as clip space coordinates
 */
void drawLine(Line line, GLuint vbo);


/* Loads coordinate data into the VBO and draws the triangle defined by them to the screen.
   Performance implications of loading data to the buffer each frame and using the same VBO for multiple points must
   be studied further
   Coordinates should be in clip space.
 */
void drawTriangle(Triangle triangle, GLuint vbo);