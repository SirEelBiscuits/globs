#include "modelloader.h"
#include "utility.h"
#include "glm.h"

#include <string>
#include <cstdlib>
#include <iostream>

#define LOG "Model"

char const* munchWhitespace(char const* buf) {
	while( *buf != '\0' && *buf <= ' ' )
		++buf;
	return buf;
}

char const* findWhitespace(char const* buf) {
	while( *buf != '\0' && *buf > ' ' )
		++buf;
	return buf;
}

bool readVertex(std::string line, glm::vec3& vec) {
	/* METHOD:
	 * line should be of the form
	 * "v $FLOAT $FLOAT $FLOAT"
	 */

	char const* cur = line.c_str();

	if( *cur != 'v' )
		return false;
	++cur;
	if( *cur == '\0' || *cur > ' ' )
		return false;
	cur = munchWhitespace(cur);
	if( cur == '\0' )
		return false;

	glm::vec3 ret;

	for( int i = 0; i < 3; ++i ) {
		if( cur == '\0' )
			return false;
		ret[i] = atof(cur);
		cur = findWhitespace(cur);
		cur = munchWhitespace(cur);
	}

	vec = ret;
	return true;
}

bool readFace(std::string line, uint16_t verts[3]) {
	char const* cur = line.c_str();

	if( *cur != 'f' )
		return false;
	++cur;
	if( *cur == '\0' || *cur > ' ' )
		return false;
	cur = munchWhitespace(cur);

	for( int i = 0; i < 3; ++i ) {
		if( cur == '\0' )
			return false;
		verts[i] = atoi(cur);
		cur = findWhitespace(cur);
		cur = munchWhitespace(cur);
	}
	return true;
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
	 * http://en.wikipedia.org/wiki/Wavefront_.obj_file )
	 *
	 * this would be a lot nicer with regex but boost is a mother fucker
	 * and gcc doesn't support std::regex yet
	 *
	 * Stage 1:
	 * comprehend 'v' lines with three coordinates
	 * comprehend 'f' lines, with three verts
	 */

	size_t curPos = 0;
	std::string curLine;
	Model* ret = new Model();

	Logger::log(LOG, "Started Model Load");

	while(curPos < buffer.size()) {
		size_t nextPos = buffer.find('\n', curPos);
		std::string curLine(buffer, curPos, nextPos);
		curPos = nextPos + 1;

		glm::vec3 vec;
		uint16_t verts[3];
		if( readVertex(curLine, vec ) ) {
			Logger::log(LOG, "found vert");
			ret->verts.push_back(vec);
		}
		else if( readFace(curLine, verts ) ) {
			Logger::log(LOG, "found face");
			for( int i = 0; i < 3; ++i )
				ret->indices.push_back(verts[i]);
		}

		if( nextPos == std::string::npos )
			break;
	}

	return ret;
}

#undef LOG

