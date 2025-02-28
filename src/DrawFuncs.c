#include "../include/DrawFuncs.h"


void drawPoint(vec3 pointCoordinate, GLuint vbo) {
	float vertices[3] = { pointCoordinate[0], pointCoordinate[1], pointCoordinate[2] };
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(0);
	// as far as I know the third parameters should be equal to # of vertices.
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);
}


void drawLine(vec3 lineStart, vec3 lineEnd, GLuint vbo) {
	// Not sure about how I feel about this hacky work around but it's the only way I could get cglm vec3s coordinates to read correctly
	float lineVertices[6] = { lineStart[0], lineStart[1], lineStart[2],
							 lineEnd[0], lineEnd[1], lineEnd[2] };
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(0);
	// as far as I know the third parameters should be equal to # of vertices.
	glDrawArrays(GL_LINES, 0, 2);
	glDisableVertexAttribArray(0);
}