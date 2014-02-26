#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler(ref_ptr<World110> w)
	: _world(w)
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
			//_world->getSelected()->FONCTION(true);
			return false;
			// z : Effet Fireworks/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Z :
			//_world->getSelected()->FONCTION(true);
			return false;
			// r : Rejouer animation///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_R :
			//_world->getSelected()->FONCTION(true);
			return false;
			// w : Cube////////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_W :
			//_world->getSelected()->FONCTION(true);
			return false;
			// x : Isosphere///////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_X :
			//_world->getSelected()->FONCTION(true);
			return false;
			// c : Suzanne/////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_C :
			//_world->getSelected()->FONCTION(true);
			return false;
			// v : Requin//////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_V :
			//_world->getSelected()->FONCTION(true);
			return false;
		default:
			break;
		}


	case(osgGA::GUIEventAdapter::KEYUP):
		switch(ea.getKey())
		{
			// Fleche : Rotation///////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Up :
			_world->getSelected()->event_RotationHaut(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Right :
			_world->getSelected()->event_RotationDroite(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Left :
			_world->getSelected()->event_RotationGauche(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Down :
			_world->getSelected()->event_RotationBas(false);
			return false;
			// a : Effet Sable/////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_A :
			//_world->getSelected()->FONCTION(false);
			return false;
			// z : Effet Fireworks/////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_Z :
			//_world->getSelected()->FONCTION(false);
			return false;
			// r : Rejouer animation///////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_R :
			//_world->getSelected()->FONCTION(false);
			return false;
			// w : Cube////////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_W :
			//_world->getSelected()->FONCTION(false);
			return false;
			// x : Isosphere///////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_X :
			//_world->getSelected()->FONCTION(false);
			return false;
			// c : Suzanne/////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_C :
			//_world->getSelected()->FONCTION(false);
			return false;
			// v : Requin//////////////////////////////////////////////////////////////////////////////////////
		case osgGA::GUIEventAdapter::KEY_V :
			//_world->getSelected()->FONCTION(false);
			return false;
		default:
			break;
		}
	default:
		return false;
	}
}