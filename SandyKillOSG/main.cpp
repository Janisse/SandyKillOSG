#include "CONSTANTES_LITTERALES.h"
#include "TestParticles.h"
#include "TestLoad.h"

int main()
{
	//viewer
	osgViewer::Viewer * viewer = new osgViewer::Viewer; 

	///////////////////////////////////////test chargement model
	
	TestLoad loader;
	loader.loadOBJ("resources/cubeOSG.obj");

	///////////////////////////////////////////////////

	///////////////////////////////////////test particles sprites
	// Make the galaxy of points
	TestParticles partic;
	osg::Node *node = partic.makeGalaxy(5000);
	node->setStateSet(partic.makeStateSet(10.0f));
	viewer->setSceneData(node);
	///////////////////////////////////////////////////

	return viewer->run();
}

