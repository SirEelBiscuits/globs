#pragma once

#include <string>
#include <fstream>

#include "log.h"
#include "model.h"

/*
 * For now, this class loads models for openGL usage only :)
 */

Model* LoadModelFromFile(char const* fileName);
Model* LoadModelFromBuffer(std::string const& buffer);
void   addVertsToModel(ModelGL* model, std::vector<char*> verts);
void   addFaceToModel(ModelGL* model, std::vector<char*> face);
