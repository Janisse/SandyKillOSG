#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler(ref_ptr<World110> w, ref_ptr<HUD110> h)
	: _world(w)
	, _hud(h)
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
			return false;
		// z : Effet Fireworks/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Z :
			//_world->getSelected()->restoreSubdivision();
			_world->setFireworksWorld();
			return false;
		// q : Effet Explosion/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_E :
			//_world->getSelected()->restoreSubdivision();
			_world->setExplosionWorld();
			return false;
		// s : Effet Vague/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_R :
			//_world->getSelected()->restoreSubdivision();
			_world->setWaveWorld();
			return false;
		// s : Effet Battement coeur/////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_T :
			//_world->getSelected()->restoreSubdivision();
			_world->setHeartWorld();
			return false;
		// s : Effet Bizarre/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Y :
			//_world->getSelected()->restoreSubdivision();
			_world->setWeirdWorld();
			return false;
		// r : Rejouer animation///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Space :
			_world->restoreSelected();
			return false;
		// w : Cube////////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_W :
			_world->setModelName("cubeOSG");
			_world->loadModel();
			return false;
		// x : Icosphere///////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_X :
			_world->setModelName("icosphere");
			_world->loadModel();
			return false;
		// c : Suzanne/////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_C :
			_world->setModelName("suzanne");
			_world->loadModel();
			return false;
		// v : Coeur//////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_V :
			_world->setModelName("coeur");
			_world->loadModel();
			return false;
		// + : Nombre subdiv ++///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_KP_Add :
			_world->subPlus();
			_hud->update();
			return false;
		// - : Nombre subdiv --///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_KP_Subtract :
			_world->subMoins();
			_hud->update();
			return false;
		// entrer : sub OK////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Return :
			_world->subOK();
			return false;
		default:
			break;
		}
	default:
		return false;
	}
}