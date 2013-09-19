#include "shaderloader.h"

#include "ishader.h"
#include "../util/utility.h"

#undef LOG
StringIntern ShaderLoader::LOG("Shader");

IShader* ShaderLoader::LoadShaderFromFiles(
	char const* fragmentShaderFilename,
	char const* vertexShaderFilename
) {
	std::string frag, vert;
	ReadFile(fragmentShaderFilename, frag);
	ReadFile(vertexShaderFilename, vert);
	return LoadShaderFromBuffers(frag, vert);
}

IShader* ShaderLoader::LoadShaderFromBuffers(
	std::string fragmentShaderSource,
	std::string vertexShaderSource
) {
	LOG_MSG(LOG.toString(), "Shader build started");
	LOG_MSG(LOG.toString(), "building fragment shader");
	GLuint frag = LoadShaderFromBuffer(
		fragmentShaderSource,
	       	GL_FRAGMENT_SHADER
	);
	LOG_MSG(LOG.toString(), "building vertex shader");
	GLuint vert = LoadShaderFromBuffer(
		vertexShaderSource,
		GL_VERTEX_SHADER
	);
	if(vert == 0 || frag == 0) {
		LOG_MSG(LOG.toString(), "Compile failed!");
		return nullptr;
	}
	LOG_MSG(LOG.toString(), "Success! Linking...");
	GLuint program = CreateProgramFromShaders(frag, vert);
	if(program == 0) {
		LOG_MSG(LOG.toString(), "Link failed!");
		return nullptr;
	}
	LOG_MSG(LOG.toString(), "Success, checking texture support");
	auto supportedTypes = getSupportedTypes(vertexShaderSource);
	LOG_MSG(LOG.toString(), "Checking attribute support");
	auto supportedAttribs = getSupportedAttributes(vertexShaderSource);
	LOG_MSG(LOG.toString(), "Creating shader object");
	return new ShaderGL(program, supportedAttribs, supportedTypes);
}

bool ShaderLoader::getShaderErrorLog(GLuint shader, GLenum ErrorToQuery) {
	GLint test;
	glGetShaderiv(shader, ErrorToQuery, &test);
	if(!test) {
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		std::string log(len, '\0');
		glGetShaderInfoLog(
			shader,
			log.size(),
			nullptr,
			const_cast<char*>(log.data())
		);
		LOG_MSG(LOG.toString(), "Log reads: %s", log.c_str());
		return false;
	}
	return true;
}

GLuint ShaderLoader::LoadShaderFromBuffer(
	std::string const& buffer,
	GLenum shaderType
) {
	char const* src = buffer.c_str();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	if(!getShaderErrorLog(shader, GL_COMPILE_STATUS)) {
		LOG_MSG(LOG.toString(), "Shader compilation failed.");
		return 0;
	}
	return shader;
}

GLuint ShaderLoader::CreateProgramFromShaders(
	GLuint fragShader,
       	GLuint vertShader
) {
	GLuint prog = glCreateProgram();
	glAttachShader(prog, fragShader);
	glAttachShader(prog, vertShader);
	glLinkProgram(prog);
	if(!getShaderErrorLog(prog, GL_LINK_STATUS)) {
		LOG_MSG(LOG.toString(), "Link Failed");
		return 0;
	}
	return prog;
}

std::vector<TextureType> ShaderLoader::getSupportedTypes(
	std::string vertexShader
) {
	//TODO
	return std::vector<TextureType>();
}

std::vector<VertComponent> ShaderLoader::getSupportedAttributes(
	std::string vertexShader
) {
	//TODO
	return std::vector<VertComponent>();
}
