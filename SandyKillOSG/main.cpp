#include "CONSTANTES_LITTERALES.h"

#include "World110.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "Physics110.h"

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


	// Chargement d'un cube
	ref_ptr<Node> myNode = osgDB::readNodeFile("resources/cubeOSG.obj");
	ref_ptr<Node110> myNode110 = new Node110(myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry());

	world->setSelected(myNode110);
	world->getScenegraph()->addChild(myNode110);


	// Evénements

	viewer->addEventHandler(keyboardHandler);
	viewer->addEventHandler(mouseHandler);

	//paramétrage de la scène
	viewer->setSceneData(world->getScenegraph());




	//osgViewer::Viewer * viewer = new osgViewer::Viewer; 



	///////////////////////////////////////test chargement model
	
	/*TestLoad loader;
	ref_ptr<Geometry> model;
	loader.loadOBJ("resources/cubeOSG.obj", model);*/

	ref_ptr<Node> myNode = osgDB::readNodeFile("resources/cubeOSG.obj");
	ref_ptr<Node110> myNode110 = new Node110(myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry());

	viewer->setSelected(myNode110);
	viewer->getScenegraph()->addChild(myNode110);
	//osg::ref_ptr<osg::Array> vertex = myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry()->getVertexArray();

	//osg::Geometry::PrimitiveSetList pSet = myNode->asGroup()->getChild(0)->asGeode()->getDrawable(0)->asGeometry()->getPrimitiveSetList();
	
	//myNode->asGeode()->getDrawable(0)->asGeometry()->getVertexArray();	//ceci ne fonctionne pas, il faurait voir commment récupérer les vertices


	/////////////////////////////////////////////////// affichage modèle

	/*ref_ptr<Geode> gdeModel = new Geode;
	gdeModel->addDrawable(model.get());
	gdeModel->setStateSet(loader.makeStateSet(10.0f));
	viewer->getScenegraph()->addChild(gdeModel);*/

	/*///////////////////////////////////////test particles sprites
	// Make the galaxy of points
	TestParticles partic;
	osg::Node *node = partic.makeGalaxy(5000);
	node->setStateSet(partic.makeStateSet(10.0f));
	viewer->setSceneData(node);
	///////////////////////////////////////////////////*/

	return viewer->run();
}

