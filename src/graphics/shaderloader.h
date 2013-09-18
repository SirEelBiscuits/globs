#pragma once

#include "ishader.h"
#include "shadergl.h"

#include <string>

class ShaderLoader {
public:
	static IShader* GetBasicShader();
	static IShader* LoadShaderFromFiles(
		char const* fragmentShaderFilename,
		char const* vertexShaderFilename
	);
	static IShader* LoadShaderFromBuffers(
		std::string fragmentShader,
	       	std::string vertexShader
	);
};
