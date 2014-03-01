#pragma once

#include "CONSTANTES_LITTERALES.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	osg::Node* createSkyBox();
	void chooseCubeMape();

private:
	osg::TextureCubeMap* readCubeMap();
};