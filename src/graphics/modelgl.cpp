#include "modelgl.h"
#include "vert.h"

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

bool ModelGL::draw() const {
	bool returnFlag = true;
	returnFlag &= bind();
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	returnFlag &= LOG_GL_ERRORS;
	returnFlag &= unbind();
	return returnFlag;
}

bool ModelGL::cleanup() {
	LOG_MSG(LOG, "Cleaning up model");
	glDeleteBuffers(1, &vertData);
	glDeleteBuffers(1, &indexData);
	glDeleteVertexArrays(1, &vao);
	LOG_MSG(LOG, "Done");
	return LOG_GL_ERRORS;
}

bool ModelGL::bind() const {
	glBindVertexArray(vao);
	return LOG_GL_ERRORS;
}

bool ModelGL::unbind() const {
	glBindVertexArray(0u);
	return LOG_GL_ERRORS;
}

bool ModelGL::useShader(Shader* shader) {
	bool returnFlag = true;
	returnFlag &= bind();
	glBindBuffer(GL_ARRAY_BUFFER, vertData);
	returnFlag &= LOG_GL_ERRORS;

	returnFlag &= shader->bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	returnFlag &= LOG_GL_ERRORS;
	returnFlag &= unbind();
	return returnFlag;
}

unsigned int ModelGL::getID() const {
	return vao;
}
