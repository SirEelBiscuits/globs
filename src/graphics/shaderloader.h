#pragma once

#include "ishader.h"
#include "shadergl.h"

#include <string>

class ShaderLoader {
public:
	static IShader* GetBasicShader();
	static IShader* LoadShaderFromFiles(
		std::string fragmentShaderFilename,
		std::string vertexShaderFilename
	);
	static IShader* LoadShaderFromBuffers(
		std::string fragmentShader,
	       	std::string vertexShader
	);
};
