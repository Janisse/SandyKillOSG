#include "KeyboardEventhandler.h"


KeyboardEventhandler::KeyboardEventhandler(void)
{
}


bool KeyboardEventhandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	switch(ea.getEventType()) {
	case(osgGA::GUIEventAdapter::KEYDOWN):
		switch(ea.getKey()) {
		case osgGA::GUIEventAdapter::KEY_Up :
			_viewer->getSelected()->event_RotationHaut(true);
			return false;
		case osgGA::GUIEventAdapter::KEY_Right :
			_viewer->getSelected()->event_RotationDroite(true);
			return false;
		case osgGA::GUIEventAdapter::KEY_Left :
			_viewer->getSelected()->event_RotationGauche(true);
			return false;
		case osgGA::GUIEventAdapter::KEY_Down :
			_viewer->getSelected()->event_RotationBas(true);
			return false;
		default:
			break;
		}
	case(osgGA::GUIEventAdapter::KEYUP):
		switch(ea.getKey()) {
		case osgGA::GUIEventAdapter::KEY_Up :
			//_demineur->evnmtIHM_Avancer(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Right :
			//_demineur->evnmtIHM_TournerDroite(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Left :
			//_demineur->evnmtIHM_TournerGauche(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Down :
			//_demineur->evnmtIHM_Reculer(false);
			return false;
		default:
			break;
		}
	default:
		return false;
	}
}
