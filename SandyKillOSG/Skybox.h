#pragma once

#include "CONSTANTES_LITTERALES.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	osg::Node* createSkyBox(std::string name);
	void chooseCubeMape();

private:
	std::string _name;

	osg::TextureCubeMap* readCubeMap();
	std::string computeFilename(std::string dir);
};