#include "World110.h"
#include "Skybox.h"
#include "Subdivisor.h"

World110::World110(void)
	: nbSubdivisions(2)
	, _model("cubeOSG")
	, minSubs(0)
	, maxSubs(9)
{
	_scenegraph = new Group();
	_selected = 0;
	SkyBox skybox;
	_skybox = skybox.createSkyBox("Sand");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);
	_physicsEngine = 0;
}

World110::~World110(void)
{
}

void World110::loadModel()
{
	if(_selected)
		_scenegraph->removeChild(_selected);
	//Loader110::loadFromFile("resources/cubeOSG.obj", _selected);
	ref_ptr<Node110> myNode110 = new Node110(nbSubdivisions);
	Loader110::loadFromFile((std::string("resources/")+_model+".obj").c_str(), myNode110);
	_scenegraph->addChild(myNode110);
	_selected = myNode110;
	_selected->setNbSubdivisions(nbSubdivisions);
	_selected->subdivide110();
	Loader110 load;
	_selected->getGeometry()->setUseDisplayList(false);
	//resetPhysics();
}

void World110::resetPhysics(){
	if(_physicsEngine){
		_physicsEngine->init(_selected);
		_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}
}

void World110::setSandWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Sand");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);

	//changement de physique
	_physicsEngine = new PhysicsSand;
	if(_selected){
		bool continueCallback = _selected->isSubdivided();
		_selected->removeUpdateCallback(_selected->getUpdateCallback());
		_physicsEngine->init(_selected);
		if(continueCallback)
			_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}

}

void World110::setFireworksWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Fireworks");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);

	//changement de physique
	_physicsEngine = new PhysicsFireworks;
	if(_selected){
		bool continueCallback = _selected->isSubdivided();
		_selected->removeUpdateCallback(_selected->getUpdateCallback());
		_physicsEngine->init(_selected);
		if(continueCallback)
			_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}

}


void World110::setExplosionWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Fireworks");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);

	//changement de physique
	_physicsEngine = new PhysicsExplosion;
	if(_selected){
		bool continueCallback = _selected->isSubdivided();
		_selected->removeUpdateCallback(_selected->getUpdateCallback());
		_physicsEngine->init(_selected);
		if(continueCallback)
			_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}
}

void World110::setWaveWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Wave");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);

	//changement de physique
	_physicsEngine = new PhysicsWave;
	if(_selected){
		bool continueCallback = _selected->isSubdivided();
		_selected->removeUpdateCallback(_selected->getUpdateCallback());
		_physicsEngine->init(_selected);
		if(continueCallback)
			_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}
}

void World110::setHeartWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("Fireworks");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);

	//changement de physique
	_physicsEngine = new PhysicsHeart;
	if(_selected){
		bool continueCallback = _selected->isSubdivided();
		_selected->removeUpdateCallback(_selected->getUpdateCallback());
		_physicsEngine->init(_selected);
		if(continueCallback)
			_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}
}

void World110::setWeirdWorld()
{
	//skybox
	SkyBox skybox;
	_scenegraph->removeChild(_skybox);
	_skybox = skybox.createSkyBox("");
	_scenegraph->addChild(_skybox);
	_skybox->setNodeMask(0x1);

	//changement de physique
	_physicsEngine = new PhysicsWeird;
	if(_selected){
		bool continueCallback = _selected->isSubdivided();
		_selected->removeUpdateCallback(_selected->getUpdateCallback());
		_physicsEngine->init(_selected);
		if(continueCallback)
			_selected->setUpdateCallback(new Physics110CallBack(_physicsEngine));
	}
}

void World110::subPlus()
{
	if(nbSubdivisions < maxSubs) nbSubdivisions++;
	if(_selected) _selected->setNbSubdivisions(nbSubdivisions);
}

void World110::subMoins()
{
	if(nbSubdivisions > minSubs) nbSubdivisions--;
	if(_selected) _selected->setNbSubdivisions(nbSubdivisions);
}

void World110::subOK()
{
	if(!_selected) return;
	_selected->setNbSubdivisions(nbSubdivisions);
	_selected->subdivide110();
}