#include "World110.h"
#include "Skybox.h"
#include "Subdivisor.h"

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
	//skybox
	SkyBox skybox;
	_skybox = skybox.createSkyBox("Sand");
	//changement de physique
	p = new PhysicsSand;
	reset();
}

void World110::reset()
{
	_scenegraph->removeChild(_selected);
	//Loader110::loadFromFile("resources/cubeOSG.obj", _selected);
	ref_ptr<Node110> myNode110 = new Node110();
	Loader110::loadFromFile("resources/coeur.obj", myNode110);
	_scenegraph->addChild(myNode110);
	_selected = myNode110; 
	Subdivisor subdivisor(_selected);
	subdivisor.subdivide(3);
	Loader110 load;
	_selected->setStateSet(load.makeStateSet(TAILLE_SPRITES));
	//	_selected->setUpdateCallback(new Physics110CallBack(new PhysicsSand));
}