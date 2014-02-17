#pragma once
#include "CONSTANTES_LITTERALES.h"


class TestParticles
{
public:
	TestParticles(void);

	osg::Geode* makeGalaxy(unsigned nvertices);
	osg::StateSet* makeStateSet(float size);
};

