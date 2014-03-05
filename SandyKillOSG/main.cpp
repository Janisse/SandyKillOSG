#include "CONSTANTES_LITTERALES.h"

#include "World110.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "Physics110.h"
#include "Loader110.h"
#include "Node110.h"
#include "Subdivisor.h"
#include "PhysicsSand.h"
#include "PhysicsExplosion.h"
#include "HUD110.h"
#include "PhysicsFireworks.h"
#include "PhysicsHeart.h"


int main()
{
	//viewer
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	//World
	ref_ptr<World110> world = new World110;

	//Physics

	int nbSubdivision;
	cout<<"Entrer le nombre de Subdivision souhaite: ";
	cin>>nbSubdivision;
	world->setNbSubdivisions(nbSubdivision);

	//Sélection et chargement du model
	world->setModelName("coeur");
	world->loadModel();

	// Evénements

	//Handlers
	ref_ptr<MouseHandler> mouseHandler = new MouseHandler(world);
	ref_ptr<KeyboardHandler> keyboardHandler = new KeyboardHandler(world);

	viewer->addEventHandler(keyboardHandler);
	viewer->addEventHandler(mouseHandler);

	//paramétrage de la scène
	viewer->setSceneData(world->getScenegraph());

	//geode
	ref_ptr<Geode> gdeHUD = new Geode;
	HUD110 hud;
	hud.createLabel();
	for(int i=0; i<hud.getTabLabel().size(); i++)
	{
		gdeHUD->addDrawable(hud.getTabLabel()[i]);
	}

	//Caméra
	ref_ptr<osgGA::TrackballManipulator> manipCameraLibre = new osgGA::TrackballManipulator;
	viewer->setCameraManipulator(manipCameraLibre);
	viewer->getCamera()->setProjectionMatrixAsPerspective(45, 1, 0.5, 1000); 
	viewer->getCamera()->setComputeNearFarMode(CullSettings::DO_NOT_COMPUTE_NEAR_FAR);

	ref_ptr<osg::Camera> camera = hud.createOrthoCamera(1280.0f, 1024.0f);

	camera->addChild(gdeHUD);
	world->getScenegraph()->addChild(camera);

	while(!viewer->done())
	{
		viewer->frame();
	}

	//return viewer->run();
}

