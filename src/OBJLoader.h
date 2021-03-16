#pragma once

#include "Model.h"

class OBJLoader
{
public:
	static Model* LoadObj(std::string filename);
};

