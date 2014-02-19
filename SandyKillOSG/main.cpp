#include "CONSTANTES_LITTERALES.h"
#include "TestParticles.h"
#include "TestLoad.h"
#include "Picking_Select.h"

int main()
{
	ref_ptr<Group> grpRoot (new Group);

	//viewer
	osgViewer::Viewer * viewer = new osgViewer::Viewer; 

	///////////////////////////////////////test chargement model
	
	TestLoad loader;
	ref_ptr<Geometry> model;
	loader.loadOBJ("resources/cubeOSG.obj", model);

	/////////////////////////////////////////////////// affichage modèle

	ref_ptr<PositionAttitudeTransform> trfModel = new PositionAttitudeTransform;
	ref_ptr<Geode> gdeModel = new Geode;
	gdeModel->addDrawable(model.get());
	gdeModel->setStateSet(loader.makeStateSet(10.0f));
	trfModel->addChild(gdeModel);
	grpRoot->addChild(trfModel);

	/*///////////////////////////////////////test particles sprites
	// Make the galaxy of points
	TestParticles partic;
	osg::Node *node = partic.makeGalaxy(5000);
	node->setStateSet(partic.makeStateSet(10.0f));
	viewer->setSceneData(node);
	///////////////////////////////////////////////////*/

	viewer->addEventHandler(new Picking_Select);
	viewer->setSceneData(grpRoot);
	return viewer->run();
}

