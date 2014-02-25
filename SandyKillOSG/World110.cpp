#include "World110.h"
#include "Skybox.h"

World110::World110(void)
{
	_scenegraph = new Group();
	_selected = 0;
	SkyBox skybox;
	_skybox = skybox.createSkyBox();
	_scenegraph->addChild(_skybox);
}


World110::~World110(void)
{
}
