#include "CONSTANTES_LITTERALES.h"

#include "World110.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "Physics110.h"
#include "Loader110.h"
#include "Node110.h"

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


	// Chargement d'un cube AUTOMATIQUE (Changer le constructeur de Node110)
	/*ref_ptr<Node> myNode = osgDB::readNodeFile("resources/cubeOSG.obj");
	ref_ptr<Node110> myNode110auto = new Node110(myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry());
	world->setSelected(myNode110auto);
	world->getScenegraph()->addChild(myNode110auto.get());*/

	// Chargement d'un cube A LA MAIN (Changer le constructeur de Node110)
	ref_ptr<Node110> myNode110 = new Node110();
	myNode110->loadFromFile("resources/cubeOSG.obj");
	world->setSelected(myNode110);
	world->getScenegraph()->addChild(myNode110.get());


	// Evénements

	viewer->addEventHandler(keyboardHandler);
	viewer->addEventHandler(mouseHandler);

	//paramétrage de la scène
	viewer->setSceneData(world->getScenegraph());

	return viewer->run();
}

