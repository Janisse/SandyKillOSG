#include "CONSTANTES_LITTERALES.h"

#include "World110.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "Physics110.h"
#include "Loader110.h"
#include "Node110.h"
#include "Subdivisor.h"
#include "PhysicsSand.h"



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
	ref_ptr<PhysicsSand> physicsEngine = new PhysicsSand;

	Loader110 load;

	// Chargement d'un cube AUTOMATIQUE
	/*
	ref_ptr<Node> myNode = osgDB::readNodeFile("resources/cubeOSG.obj");
	ref_ptr<Node110> myNode110auto = new Node110(myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry());
	myNode110auto->setStateSet(load.makeStateSet(10.f));
	world->setSelected(myNode110auto);
	world->getScenegraph()->addChild(myNode110auto.get());*/


	int nbSubdivision;
	// Chargement d'un cube A LA MAIN
	ref_ptr<Node110> myNode110 = new Node110();
	Loader110::loadFromFile("resources/suzanne.obj", myNode110);

	cout<<"Entrer le nombre de Subdivision souhaite: ";
	cin>>nbSubdivision;

	subdivide(myNode110, nbSubdivision);

	myNode110->getGeometry()->setUseDisplayList(false);

	myNode110->setStateSet(load.makeStateSet(TAILLE_SPRITES));
	world->setSelected(myNode110);
	world->getScenegraph()->addChild(myNode110);

	// Fonction effet sable
	myNode110->addUpdateCallback(new Physics110CallBack(physicsEngine));

	// Ev�nements

	viewer->addEventHandler(keyboardHandler);
	viewer->addEventHandler(mouseHandler);

	//param�trage de la sc�ne
	viewer->setSceneData(world->getScenegraph());

	//Cam�ra
	/*ref_ptr<osgGA::TrackballManipulator> manipCameraLibre = new osgGA::TrackballManipulator;
	viewer->setCameraManipulator(manipCameraLibre);

	while(!viewer->done()){
		viewer->frame();
	}*/

	return viewer->run();
}

