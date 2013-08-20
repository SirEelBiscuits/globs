#include "modelgl.h"
#include "vert.h"
#include "shader.h"

#include <iostream>

#define LOG "ModelGL"

ModelGL::ModelGL(GLuint vao, GLuint vertData, GLuint indexData, int numIndices)
	: vao(vao)
	, vertData(vertData)
	, indexData(indexData)
	, numIndices(numIndices)
{}

void ModelGL::Draw() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ModelGL::Cleanup() {
	Logger::log(LOG, "Cleaning up model");
	glDeleteBuffers(1, &vertData);
	glDeleteBuffers(1, &indexData);
	glDeleteVertexArrays(1, &vao);
	Logger::log(LOG, "Done");
}

