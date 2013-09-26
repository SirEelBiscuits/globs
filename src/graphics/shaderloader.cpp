#include "shaderloader.h"

#include "shadergl.h"
#include "../util/utility.h"

#undef LOG
StringIntern ShaderLoader::LOG("Shader");

Shader* ShaderLoader::LoadShaderFromFiles(
	char const* fragmentShaderFilename,
	char const* vertexShaderFilename
) {
	std::string frag, vert;
	ReadFile(fragmentShaderFilename, frag);
	ReadFile(vertexShaderFilename, vert);
	return LoadShaderFromBuffers(frag, vert);
}

Shader* ShaderLoader::LoadShaderFromBuffers(
	std::string const& fragmentShaderSource,
	std::string const& vertexShaderSource
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
	auto supportedTypes = getSupportedTypes(program);
	LOG_MSG(LOG.toString(), "Checking attribute support");
	auto supportedAttribs = getSupportedAttributes(program);
	LOG_MSG(LOG.toString(), "Creating shader object");
	return new ShaderGL(program, supportedAttribs, supportedTypes);
}

GLuint ShaderLoader::LoadShaderFromBuffer(
	std::string const& buffer,
	GLenum shaderType
) {
	char const* src = buffer.c_str();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	LOG_GL_ERRORS;

	GLint compStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compStatus);
	LOG_GL_ERRORS;
	if(!compStatus) {
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		LOG_GL_ERRORS;
		std::string log(len, '\0');
		glGetShaderInfoLog(
			shader,
			log.size(),
			nullptr,
			const_cast<char*>(log.data())
		);
		LOG_GL_ERRORS;
		LOG_MSG(LOG.toString(), "Shader compilation failed.");
		LOG_MSG(LOG.toString(), "Log reads: %s", log.c_str());
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
	LOG_GL_ERRORS;
	glLinkProgram(prog);
	LOG_GL_ERRORS;

	GLint linkStatus;
	glGetProgramiv(prog, GL_LINK_STATUS, &linkStatus);
	LOG_GL_ERRORS;
	if(!linkStatus) {
		GLint len;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
		LOG_GL_ERRORS;
		std::string log(len, '\0');
		glGetProgramInfoLog(
			prog,
			log.size(),
			nullptr,
			const_cast<char*>(log.data())
		);
		LOG_GL_ERRORS;
		LOG_MSG(LOG.toString(), "Link Failed");
		LOG_MSG(LOG.toString(), "Log reads: %s", log.c_str());
		return 0;
	}
	return prog;
}

std::vector<TextureType> ShaderLoader::getSupportedTypes(
	GLuint program
) {
	std::vector<TextureType> ret;
	for(int i = 0; i < AS_INDEX(TextureType::Count); ++i) {
		StringIntern tt = Texture::StringFromTextureType(
			static_cast<TextureType>(i)
		);
		LOG_MSG(LOG.toString(), "checking %s", tt.toString());
		GLint pos = glGetUniformLocation(
			program,
			tt.toString()
		);
		if(pos != -1) {
			ret.push_back(static_cast<TextureType>(i));
		}
		else {
			CLEAR_GL_ERRORS;
		}
		LOG_GL_ERRORS;
	}
	return ret;
}

std::vector<VertComponent> ShaderLoader::getSupportedAttributes(
	GLuint program
) {
	std::vector<VertComponent> ret;
	for(int i = 0; i < AS_INDEX(VertComponent::Count); ++i) {
		GLint pos = glGetAttribLocation(
			program,
			Vert::StringFromVertComponent(
				static_cast<VertComponent>(i)
			).toString()
		);
		if(pos != -1) {
			ret.push_back(static_cast<VertComponent>(i));
		}
		else {
			CLEAR_GL_ERRORS;
		}
		LOG_GL_ERRORS;
	}
	return ret;
}

