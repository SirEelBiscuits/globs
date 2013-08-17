#include "modelloader.h"
#include "utility.h"
#include "glm.h"

#include <string>
#include <cstdlib>
#include <iostream>

#include "modelgl.h"

#define LOG "Model"

char const* munchWhitespace(char const* buf) {
	while(*buf != '\0' && *buf != '\n' && *buf <= ' ')
		++buf;
	return buf;
}

char const* findWhitespace(char const* buf) {
	while(*buf != '\0' && *buf != '\n' && *buf > ' ')
		++buf;
	return buf;
}

bool readVertex(std::string line, std::vector<const char*>& outStrings) {
	/* METHOD:
	 * line should be of the form
	 * "v $FLOAT $FLOAT $FLOAT"
	 */

	char const* cur = line.c_str();

	if(*cur != 'v')
		return false;
	++cur;
	if(*cur == '\0' || *cur > ' ')
		return false;
	cur = munchWhitespace(cur);

	std::vector<const char*> ret;

	for(int i = 0; i < 3; ++i) {
		if(cur == '\0')
			return false;
		ret.push_back(cur);
		cur = findWhitespace(cur);
		cur = munchWhitespace(cur);
	}
	outStrings = ret;
	return true;
}

glm::vec3 vec3FromStringArray(std::vector<const char*> verts) {
	glm::vec3 ret;
	for(int i = 0; i < 3; ++i) {
		ret[i] = atof(verts[i]);
	}
	return ret;
}

void addVertToModel(ModelGL* model, int index, std::vector<const char*> verts) {
	Vert vert = model->getOrCreateVert(index);
	vert.v = vec3FromStringArray(verts);
	model->setVert(index, vert);
}

bool readFace(std::string line, std::vector<const char*>& outStrings) {
	char const* cur = line.c_str();

	if(*cur != 'f')
		return false;
	++cur;
	if(*cur == '\0' || *cur > ' ')
		return false;
	cur = munchWhitespace(cur);

	std::vector<const char*> ret;

	while(*cur != '\n' && *cur != '\0') {
		ret.push_back(cur);
		cur = findWhitespace(cur);
		cur = munchWhitespace(cur);
	}
	outStrings = ret;
	return true;
}

void addFaceToModel(ModelGL* model, std::vector<const char*> face) {
	for(auto v : face)
		model->appendIndex(atoi(v));
}

Model* LoadModelFromFile(char const* fileName) {
	std::string buf;
	ReadFile(fileName, buf);
	return LoadModelFromBuffer(buf);
}

Model* LoadModelFromBuffer(std::string const& buffer) {
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

	std::string curLine;
	ModelGL* ret = new ModelGL();

	Logger::log(LOG, "Started openGL type Model Load");

	size_t curPos = 0;
	int curIndex = 0;
	while( curPos < buffer.size()) {
		size_t nextPos = buffer.find('\n', curPos);
		std::string curLine(buffer, curPos, nextPos);
		curPos = nextPos + 1;

		std::vector<const char*> vec(4); // no more than 4 elements anticipated
		if(readVertex(curLine, vec)) {
			Logger::log(LOG, "found vert");
			addVertToModel(ret, curIndex, vec);
		}
		++curIndex;
	}

	curPos = 0;
	while(curPos < buffer.size()) {
		size_t nextPos = buffer.find('\n', curPos);
		std::string curLine(buffer, curPos, nextPos);
		curPos = nextPos + 1;

		std::vector<const char*> vec(4);
		if(readFace(curLine, vec)) {
			Logger::log(LOG, "found face");
			addFaceToModel(ret, vec);
		}
	}

	ret->FinaliseLoad();
	return ret;
}

#undef LOG

