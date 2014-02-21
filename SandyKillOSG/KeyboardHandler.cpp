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
	switch(ea.getEventType()) {
	case(osgGA::GUIEventAdapter::KEYDOWN):
		switch(ea.getKey()) {
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
		default:
			break;
		}
	case(osgGA::GUIEventAdapter::KEYUP):
		switch(ea.getKey()) {
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
		default:
			break;
		}
	default:
		return false;
	}
}