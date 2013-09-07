#include "modelgl.h"
#include "vert.h"
#include "shader.h"

#include <iostream>

#define LOG "ModelGL"

ModelGL::ModelGL(
	GLuint vao,
       	GLuint vertData,
       	GLuint indexData,
       	int numIndices
)
	: vao(vao)
	, vertData(vertData)
	, indexData(indexData)
	, numIndices(numIndices)
{
	if(!glIsBuffer(vertData))
		LOG_MSG(LOG, "Iffy buffer for vert data (%d)",
			vertData);
	if(!glIsBuffer(indexData))
		LOG_MSG(LOG, "Iffy buffer for index data(%d)",
			indexData);
	if(!glIsVertexArray(vao))
		LOG_MSG(LOG, "Iffy vertex array (%d)", vao);
}

void ModelGL::Draw() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	LOG_GL_ERRORS;
}

void ModelGL::Cleanup() {
	LOG_MSG(LOG, "Cleaning up model");
	glDeleteBuffers(1, &vertData);
	glDeleteBuffers(1, &indexData);
	glDeleteVertexArrays(1, &vao);
	LOG_MSG(LOG, "Done");
	LOG_GL_ERRORS;
}

