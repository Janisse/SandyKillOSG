#include "KeyboardEventhandler.h"


KeyboardEventhandler::KeyboardEventhandler(ref_ptr<Viewer110> v)
	: _viewer(v)
{
}


bool KeyboardEventhandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	if(!_viewer->getSelected()) return true;

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
			_viewer->getSelected()->event_RotationHaut(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Right :
			_viewer->getSelected()->event_RotationBas(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Left :
			_viewer->getSelected()->event_RotationGauche(false);
			return false;
		case osgGA::GUIEventAdapter::KEY_Down :
			_viewer->getSelected()->event_RotationDroite(false);
			return false;
		default:
			break;
		}
	default:
		return false;
	}
}
