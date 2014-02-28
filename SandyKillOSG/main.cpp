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


int main()
{
	//viewer
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	//World
	ref_ptr<World110> world = new World110;

	//Physics
	ref_ptr<PhysicsSand> physicsEngine = new PhysicsSand;
	//ref_ptr<PhysicsFireworks> physicsEngine = new PhysicsFireworks;

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

	Subdivisor subdivisor(myNode110);
	subdivisor.subdivide(nbSubdivision);
	//subdivide(myNode110, nbSubdivision);

	myNode110->getGeometry()->setUseDisplayList(false);

	myNode110->setStateSet(load.makeStateSet(TAILLE_SPRITES));
	world->setSelected(myNode110);
	world->getScenegraph()->addChild(myNode110);

	// Fonction effet sable
	myNode110->addUpdateCallback(new Physics110CallBack(physicsEngine));

	// Evénements

	//Handlers
	ref_ptr<MouseHandler> mouseHandler = new MouseHandler(world);
	ref_ptr<KeyboardHandler> keyboardHandler = new KeyboardHandler(world, physicsEngine);

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

	return viewer->run();
}

