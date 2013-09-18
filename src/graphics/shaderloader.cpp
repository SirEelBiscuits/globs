#include "shaderloader.h"

#include "ishader.h"
#include "../util/utility.h"

IShader* ShaderLoader::GetBasicShader() {
	return nullptr;
}

IShader* ShaderLoader::LoadShaderFromFiles(
	char const* fragmentShaderFilename,
	char const* vertexShaderFilename
) {
	std::string frag, vert;
	ReadFile(fragmentShaderFilename, frag);
	ReadFile(vertexShaderFilename, vert);
	return LoadShaderFromBuffers(frag, vert);
}

IShader* ShaderLoader:: LoadShaderFromBuffers(
	std::string fragmentShader,
	std::string vertexShader
) {
	return nullptr;
}
