#include "World110.h"
#include "Skybox.h"

World110::World110(void)
{
	_scenegraph = new Group();
	_selected = 0;
	SkyBox skybox;
	_skybox = skybox.createSkyBox("Fireworks");
	_scenegraph->addChild(_skybox);
}


World110::~World110(void)
{
}


void World110::setSandWorld(ref_ptr<Physics110> p)
{
	reset();
	//skybox
	SkyBox skybox;
	_skybox = skybox.createSkyBox("Sand");
	//changement de physique
	p = new PhysicsSand;
}

void World110::reset()
{
	Loader110::loadFromFile("resources/cubeOSG.obj", _selected);
//	_selected->setUpdateCallback(new Physics110CallBack(new PhysicsSand));
}