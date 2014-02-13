
#include "CONSTANTES_LITTERALES.h"
#include "TestParticles.h"

int main()
{
	//IHM


	//scene3D (contenant Camera + list model 3D déjà chargé + particules srpites)


	//viewer
	osgViewer::Viewer * viewer = new osgViewer::Viewer; 


	///////////////////////////////////////test particles sprites
	// Make the galaxy of points
	TestParticles partic;
	osg::Node *node = partic.makeGalaxy(5000);
	node->setStateSet(partic.makeStateSet(10.0f));
	viewer->setSceneData(node);
	///////////////////////////////////////////////////

	return viewer->run();
}

