#include "CONSTANTES_LITTERALES.h"

#include "World110.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "Physics110.h"
#include "Loader110.h"
#include "Node110.h"
#include "Subdivisor.h"

int main()
{
	//viewer
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	//World
	ref_ptr<World110> world = new World110;

	//Handlers
	ref_ptr<MouseHandler> mouseHandler = new MouseHandler(world);
	ref_ptr<KeyboardHandler> keyboardHandler = new KeyboardHandler(world);

	//Physics
	Physics110 physicsEngine;

	Loader110 load;

	// Chargement d'un cube AUTOMATIQUE
	/*
	ref_ptr<Node> myNode = osgDB::readNodeFile("resources/cubeOSG.obj");
	ref_ptr<Node110> myNode110auto = new Node110(myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry());
	myNode110auto->setStateSet(load.makeStateSet(10.f));
	world->setSelected(myNode110auto);
	world->getScenegraph()->addChild(myNode110auto.get());*/

	// Chargement d'un cube A LA MAIN
	ref_ptr<Node110> myNode110 = new Node110();
	Loader110::loadFromFile("resources/cubeOSG.obj", myNode110);
	subdivide(myNode110);
	myNode110->setStateSet(load.makeStateSet(10.f));
	world->setSelected(myNode110);
	world->getScenegraph()->addChild(myNode110);

	// convertion vertice en sprites
	//myNode110->convertToSprites();

	// Evénements

	viewer->addEventHandler(keyboardHandler);
	viewer->addEventHandler(mouseHandler);

	//paramétrage de la scène
	viewer->setSceneData(world->getScenegraph().get());

	return viewer->run();
}

