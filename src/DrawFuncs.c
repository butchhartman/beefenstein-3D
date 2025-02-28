#include "../include/DrawFuncs.h"


void drawPoint(Point point, GLuint vbo) {
	float vertices[6] = { 
		point.vertexCoordinates[0], point.vertexCoordinates[1], point.vertexCoordinates[2],

		point.vColor[0], point.vColor[1], point.vColor[2]
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// as far as I know the third parameters should be equal to # of vertices.
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}


void drawLine(Line line, GLuint vbo) {
	// Not sure about how I feel about this hacky work around but it's the only way I could get cglm vec3s coordinates to read correctly
	float lineVertices[12] = { 
		line.vertexStart[0], line.vertexStart[1], line.vertexStart[2],
		line.vertexEnd[0], line.vertexEnd[1], line.vertexEnd[2],

		line.vColor1[0], line.vColor1[1], line.vColor1[2],
		line.vColor2[0], line.vColor2[1], line.vColor2[2]
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// as far as I know the third parameters should be equal to # of vertices.
	glDrawArrays(GL_LINES, 0, 2);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void drawTriangle(Triangle triangle, GLuint vbo) {
	float vertices[18] = {
	triangle.v1[0], triangle.v1[1], triangle.v1[2],
	triangle.v2[0], triangle.v2[1], triangle.v2[2],
	triangle.v3[0], triangle.v3[1], triangle.v3[2],

	triangle.vColor1[0], triangle.vColor1[1], triangle.vColor1[2],
	triangle.vColor2[0], triangle.vColor2[1], triangle.vColor2[2],
	triangle.vColor3[0], triangle.vColor3[1], triangle.vColor3[2]
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// as far as I know the third parameters should be equal to # of vertices.
	glDrawArrays(GL_TRIANGLES, 0, 18);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}