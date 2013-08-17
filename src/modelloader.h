#pragma once

#include <string>
#include <fstream>

#include "log.h"
#include "model.h"

Model* LoadModelFromFile(char const* fileName);
Model* LoadModelFromBuffer(std::string const& buffer);
void   addVertsToModel(Model* model, std::vector<char*> verts);
void   addFaceToModel(Model* model, std::vector<char*> face);