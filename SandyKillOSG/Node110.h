#pragma once

#include "CONSTANTES_LITTERALES.h"

class Node110 : public Group
{
private:
	ref_ptr<PositionAttitudeTransform> _trf;
	ref_ptr<Geode> _gde;
	ref_ptr<Geometry> _geom;

public:
	Node110(ref_ptr<Geometry> geom);
	~Node110(void);
};

