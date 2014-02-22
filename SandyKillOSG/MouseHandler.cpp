#include "MouseHandler.h"


MouseHandler::MouseHandler(ref_ptr<World110> w)
	: _isLeftClicking(false)
	, _isRightClicking(false)
	, _world(w)
	, _mX(0)
	, _mY(0)
{
}


MouseHandler::~MouseHandler(void)
{
}


bool MouseHandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa)
{

	ref_ptr<osgViewer::Viewer> viewer = dynamic_cast<osgViewer::Viewer*>( &aa );

	if (!viewer)
		return false;

	switch( ea.getEventType() )
	{
	case osgGA::GUIEventAdapter::PUSH:
	case osgGA::GUIEventAdapter::MOVE:
		{
			// Record mouse location for the button press
			//   and move events.
			_mX = ea.getX();
			_mY = ea.getY();
			return false;
		}
	case osgGA::GUIEventAdapter::RELEASE:
		{
			// If the mouse hasn't moved since the last
			//   button press or move event, perform a
			//   pick. (Otherwise, the trackball
			//   manipulator will handle it.)
			if (_mX == ea.getX() && _mY == ea.getY())
			{
				if (pickCible( viewer, ea.getXnormalized(), ea.getYnormalized()))
					return true;
			}
			return false;
		}    

	default:
		return false;
	}
}

bool MouseHandler::pickCible (osgViewer::Viewer* viewer, float mx, float my)
{
	if (!viewer->getSceneData())
		// Nothing to pick.
		return false;

	double w( .05 ), h( .05 );
	osgUtil::PolytopeIntersector* picker = new osgUtil::PolytopeIntersector(osgUtil::Intersector::PROJECTION,mx-w, my-h, mx+w, my+h );

	osgUtil::IntersectionVisitor iv( picker );
	viewer->getCamera()->accept( iv );

	if (picker->containsIntersections())
	{
		const osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;
		ref_ptr<osg::Node> nde = nodePath.at(0);
		//_picked = dynamic_cast<Node110*>(nde);
	}
	return _picked.valid();
}

void MouseHandler::onClick()
{
}


void MouseHandler::onRelease()
{
}

void MouseHandler::onMove()
{
}