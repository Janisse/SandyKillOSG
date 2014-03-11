#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler(ref_ptr<World110> w, ref_ptr<HUD110> h, ref_ptr<osgViewer::Viewer> v)
	: _world(w)
	, _hud(h)
	, _viewer(v)
{

}


KeyboardHandler::~KeyboardHandler(void)
{
}


bool KeyboardHandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		//Enleve les avertissements a l'ecran lors de la prochaine touche enfoncé
		_hud->selectAPhysic(false);
		switch(ea.getKey())
		{
		// Fleche : Rotation///////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Up :
			_world->getSelected()->event_RotationHaut(true);
			return false;
		case osgGA::GUIEventAdapter::KEY_Right :
			_world->getSelected()->event_RotationDroite(true);
			return false;
		case osgGA::GUIEventAdapter::KEY_Left :
			_world->getSelected()->event_RotationGauche(true);
			return false;
		case osgGA::GUIEventAdapter::KEY_Down :
			_world->getSelected()->event_RotationBas(true);
			return false;
		// a : Effet Sable/////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_A :
			//_world->getSelected()->restoreSubdivision();
			_world->setSandWorld();
			_hud->setColorHud(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			return false;
		// z : Effet Fireworks/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Z :
			//_world->getSelected()->restoreSubdivision();
			_world->setFireworksWorld();
			_hud->setColorHud(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			return false;
		// q : Effet Explosion/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_E :
			//_world->getSelected()->restoreSubdivision();
			_world->setExplosionWorld();
			_hud->setColorHud(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			return false;
		// s : Effet Vague/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_R :
			//_world->getSelected()->restoreSubdivision();
			_world->setWaveWorld();
			_hud->setColorHud(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			return false;
		// s : Effet Battement coeur/////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_T :
			//_world->getSelected()->restoreSubdivision();
			_world->setHeartWorld();
			_hud->setColorHud(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			return false;
		// s : Effet Bizarre/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Y :
			//_world->getSelected()->restoreSubdivision();
			_world->setWeirdWorld();
			_hud->setColorHud(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
			return false;
		// r : Rejouer animation///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Space :
			_world->restoreSelected();
			return false;
		// w : Cube////////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_W :
			_hud->loading(true);
			_viewer->frame();
			_world->setModelName("cubeOSG");
			_world->loadModel();
			_hud->loading(false);
			return false;
		// x : Icosphere///////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_X :
			_hud->loading(true);
			_viewer->frame();
			_world->setModelName("icosphere");
			_world->loadModel();
			_hud->loading(false);
			return false;
		// c : Suzanne/////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_C :
			_hud->loading(true);
			_viewer->frame();
			_world->setModelName("suzanne");
			_world->loadModel();
			_hud->loading(false);
			return false;
		// v : Coeur//////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_V :
			_hud->loading(true);
			_viewer->frame();
			_world->setModelName("coeur");
			_world->loadModel();
			_hud->loading(false);
			return false;
		// + : Nombre subdiv ++///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Plus :
			_world->subPlus();
			_hud->update();
			return false;
		// - : Nombre subdiv --///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Minus :
			_world->subMoins();
			_hud->update();
			return false;
		// entrer : sub OK////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Return :
			_hud->subdivisionInProgress(true);
			_viewer->frame();	//Actualise l'image pour afficher "Subdivision en cours..." avant la subdivision
			_world->subOK();
			_hud->subdivisionInProgress(false);
			return false;
		// tab : stop physique////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Tab :
			if(_world->getPhysics() != NULL)
			{
				_world->pausePhys();
				_hud->updatePause();
			}
			else
				_hud->selectAPhysic(true);
			return false;
		default:
			break;
		}
	default:
		return false;
	}
}