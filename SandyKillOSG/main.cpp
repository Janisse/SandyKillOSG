#include "CONSTANTES_LITTERALES.h"
#include "TestParticles.h"
#include "TestLoad.h"

int main()
{
	ref_ptr<Group> grpRoot (new Group);

	//viewer
	osgViewer::Viewer * viewer = new osgViewer::Viewer; 

	///////////////////////////////////////test chargement model
	
	/*TestLoad loader;
	ref_ptr<Geometry> model;
	loader.loadOBJ("resources/cubeOSG.obj", model);*/

	ref_ptr<Node> myNode = osgDB::readNodeFile("resources/cubeOSG.obj");
	grpRoot->addChild(myNode);
	//myNode->asGeode()->getDrawable(0)->asGeometry()->getVertexArray();	//ceci ne fonctionne pas, il faurait voir commment récupérer les vertices


	/////////////////////////////////////////////////// affichage modèle

	/*ref_ptr<Geode> gdeModel = new Geode;
	gdeModel->addDrawable(model.get());
	gdeModel->setStateSet(loader.makeStateSet(10.0f));
	grpRoot->addChild(gdeModel);*/

	/*///////////////////////////////////////test particles sprites
	// Make the galaxy of points
	TestParticles partic;
	osg::Node *node = partic.makeGalaxy(5000);
	node->setStateSet(partic.makeStateSet(10.0f));
	viewer->setSceneData(node);
	///////////////////////////////////////////////////*/

	viewer->setSceneData(grpRoot);
	return viewer->run();
}

