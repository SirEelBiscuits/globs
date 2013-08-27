#include "modelloader.h"
#include "utility.h"
#include "glm.h"

#include <string>
#include <cstdlib>
#include <iostream>

#include "modelgl.h"
#include "shader.h"

#define LOG "Model"

bool terminatesLine(char const* c) {
	return *c == '\0' || *c == '\n';
}

char const* munchWhitespace(char const* buf) {
	while(!terminatesLine(buf) && *buf <= ' ')
		++buf;
	return buf;
}

char const* findWhitespace(char const* buf) {
	while(!terminatesLine(buf) && *buf > ' ')
		++buf;
	return buf;
}

Vert getOrCreateVert(std::vector<Vert>& vec, unsigned int Index) {
	if(Index >= vec.size()) {
		vec.resize(Index + 1);
		return vec[Index];
	}
	return vec[Index];
}

glm::vec2 vec2FromStringArray(std::vector<const char*> verts) {
	glm::vec2 ret;
	for(int i = 0; i < 2; ++i) {
		ret[i] = atof(verts[i]);
	}
	return ret;
}

glm::vec3 vec3FromStringArray(std::vector<const char*> verts) {
	glm::vec3 ret;
	for(int i = 0; i < 3; ++i) {
		ret[i] = atof(verts[i]);
	}
	return ret;
}

glm::vec4 vec4FromStringArray(std::vector<const char*> values) {
	glm::vec4 ret;
	for(int i = 0; i < 4; ++i) {
		ret[i] = atof(values[i]);
	}
	return ret;
}

void addVertToModel(std::vector<Vert>& outVec, int index, std::vector<const char*> verts) {
	Vert vert = getOrCreateVert(outVec, index);
	vert.v = vec3FromStringArray(verts);
	outVec[index] = vert;
}

void addColourToModel(std::vector<Vert>& outVec, int index, std::vector<const char*> verts) {
	Vert vert = getOrCreateVert(outVec, index);
	vert.c = vec4FromStringArray(verts);
	outVec[index] = vert;
}

void addTextureCoordToModel(std::vector<Vert>& outVec, int index, std::vector<const char*> verts) {
	Vert vert = getOrCreateVert(outVec, index);
	vert.t = vec2FromStringArray(verts);
	outVec[index] = vert;
}

void addFaceToModel(std::vector<GLuint>& outIndices, std::vector<const char*> face) {
	for(auto v : face)
		outIndices.push_back(atoi(v));
}

bool readObjectLine(
	char const lineType,
	char const* line,
	std::vector<const char*>& outStrings
) {
	if(*line != lineType)
		return false;
	++line;
	if(terminatesLine(line) || *line > ' ')
		return false;
	line = munchWhitespace(line);

	std::vector<const char*> ret;

	while(!terminatesLine(line)) {
		ret.push_back(line);
		line = findWhitespace(line);
		line = munchWhitespace(line);
	}
	outStrings = ret;
	return true;
}

bool readObjectLine(
	char const lineType,
	int const numElements,
	char const* line,
	std::vector<const char*>& outStrings
) {
	if(*line != lineType)
		return false;
	++line;
	if(terminatesLine(line) || *line > ' ')
		return false;
	line = munchWhitespace(line);

	std::vector<const char*> ret;
	for( int i = 0; i < numElements; ++i ) {
		if(terminatesLine(line))
			return false;
		ret.push_back(line);
		line = findWhitespace(line);
		line = munchWhitespace(line);
	}
	outStrings = ret;
	return true;
}

Model* ModelLoader::LoadModelFromFile(char const* fileName) {
	std::string buf;
	ReadFile(fileName, buf);
	Logger::log(LOG, "Loading model %s", fileName);
	return LoadModelFromBuffer(buf);
}

void FinaliseLoad(
	std::vector<Vert> const& verts,
	std::vector<GLuint> const& indices,
	GLuint& vao,
	GLuint& vertData,
	GLuint& indexData
) {
	Logger::log(LOG, "Sending model data to GL");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Logger::log(LOG,"Allocating vertex store size: %d", sizeof(Vert) * verts.size());
	glGenBuffers(1, &vertData);
	glBindBuffer(GL_ARRAY_BUFFER, vertData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * verts.size(), verts.data(), GL_STATIC_DRAW);
	LOG_GL_ERRORS;

	Logger::log(LOG,"Initialising shader params");

	for( auto vc : {
		VertComponent::Position,
		VertComponent::Colour,
		VertComponent::Texture,
		VertComponent::Normal
	} ) {
		BindParameter(
			GetBasicShader(),
			stringFromVertComponent(vc),
			Vert::getElementWidths(vc),
			GL_FLOAT,
			Vert::getStride(),
			(GLvoid*)Vert::getOffset(vc)
		);
		LOG_GL_ERRORS;
	}

	Logger::log(LOG, "Initialising element array size: %d", sizeof(int) * indices.size());
	glGenBuffers(1, &indexData);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	LOG_GL_ERRORS;

	Logger::log(LOG, "Data all uploaded, cleanup time.");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	LOG_GL_ERRORS;

	Logger::log(LOG, "all done");
}

Model* ModelLoader::LoadModelFromBuffer(std::string const& buffer) {
	/*
	 * METHOD:
	 * we are going to be loading .obj files (description at
	 * http://en.wikipedia.org/wiki/Wavefront_.obj_file)
	 *
	 * this would be a lot nicer with regex but boost is a mother fucker
	 * and gcc doesn't support std::regex yet
	 *
	 * Stage 1:
	 * comprehend 'v' lines with three coordinates
	 * comprehend 'f' lines, with n verts
	 */

	std::vector<Vert> vertList;
	std::vector<GLuint> indexList;

	Logger::log(LOG, "Started openGL type Model Load");

	size_t curPos = 0;
	int curVertIndex = 0;
	int curColourIndex = 0;
	int curTextureIndex = 0;
	while( curPos < buffer.size()) {
		char const* curLine = buffer.c_str() + curPos;
		std::vector<const char*> vec(4); // no more than 4 elements anticipated

		if(readObjectLine('v', 3, curLine, vec)) {
			Logger::log(LOG, "found vert");
			addVertToModel(vertList, curVertIndex, vec);
			++curVertIndex;
		}
		else if(readObjectLine('c', 4, curLine, vec)) {
			Logger::log(LOG, "found colour");
			addColourToModel(vertList, curColourIndex, vec);
			++curColourIndex;
		}
		else if(readObjectLine('t', 2, curLine, vec)) {
			Logger::log(LOG, "found texture coord");
			addTextureCoordToModel(vertList, curTextureIndex, vec);
			++curTextureIndex;
		}

		//faces work a little differently, because while order dependent,
		// there is no interdependence (ie, v and c lines need to be matched up)
		else if(readObjectLine('f', curLine, vec)) {
			Logger::log(LOG, "found face");
			addFaceToModel(indexList, vec);
		}
		curPos = buffer.find('\n', curPos) + 1;
	}

	Logger::log(LOG, "Finished loading model");

	GLuint vao, vertHandle, indexHandle;
	FinaliseLoad(vertList, indexList, vao, vertHandle, indexHandle);
	ModelGL* ret = new ModelGL(vao, vertHandle, indexHandle, indexList.size());
	return ret;
}

#undef LOG

