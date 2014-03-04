#include "World110.h"
#include "Skybox.h"
#include "Subdivisor.h"

World110::World110(void)
	: _nbSubdivisions(0)
	, _model("cubeOSG")
{
	_scenegraph = new Group();
	_selected = 0;
	SkyBox skybox;
	_skybox = skybox.createSkyBox("Fireworks");
	_scenegraph->addChild(_skybox);
	_physicsEngine = 0;
}

World110::~World110(void)
{
}


void World110::setSandWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Sand");
	_scenegraph->addChild(_skybox);

	//changement de physique
	_selected->removeUpdateCallback(_selected->getUpdateCallback());
	_physicsEngine = new PhysicsSand;
	_physicsEngine->init(_selected);
	_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));

	//Modèle 3D
	//resetModel();
}

void World110::setFireworksWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Fireworks");
	_scenegraph->addChild(_skybox);

	//changement de physique
	_selected->removeUpdateCallback(_selected->getUpdateCallback());
	_physicsEngine = new PhysicsFireworks;
	_physicsEngine->init(_selected);
	_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));

	//Modèle 3D
	//resetModel();
}

void World110::resetModel()
{
	if(_selected)
		_scenegraph->removeChild(_selected);
	//Loader110::loadFromFile("resources/cubeOSG.obj", _selected);
	ref_ptr<Node110> myNode110 = new Node110();
	Loader110::loadFromFile((std::string("resources/")+_model+".obj").c_str(), myNode110);
	_scenegraph->addChild(myNode110);
	_selected = myNode110;
	_selected->setNbSubdivisions(_nbSubdivisions);
	_selected->subdivide110();
	Loader110 load;
	_selected->setStateSet(load.makeStateSet(TAILLE_SPRITES));
	_selected->getGeometry()->setUseDisplayList(false);
	if(_physicsEngine){
		_physicsEngine->init(_selected);
		_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}
}