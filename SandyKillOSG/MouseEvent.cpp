#include "MouseEvent.h"


MouseEvent::MouseEvent(void)
{
}


bool MouseEvent::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(GUIEventAdapter::RELEASE):
		{
			osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
			if (!viewer) return false;
			//_picked = pickCible(viewer, ea.getX(), ea.getY());
			return true;
		}
	default:return false;
	}
}