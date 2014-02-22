#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "Node110.h"

class Loader110
{
public:
	Loader110(void);
	~Loader110(void);

	bool static loadFromFile(const char * path, ref_ptr<Node110>& node110);
};

