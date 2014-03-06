#include "MouseHandler.h"


MouseHandler::MouseHandler(ref_ptr<World110> w)
	:_world(w)
	, _mX(0)
	, _mY(0)
{
	_picked = 0;
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
	case osgGA::GUIEventAdapter::RELEASE:
		{
			_mX = ea.getX();
			_mY = ea.getY();
			if (_mX && _mY)
			{
				if (pickCible( viewer, ea))
				{
					if(_picked)
						_world->setSelected(_picked);
						_picked->convertToSprites();
						_world->resetPhysics();
					return true;
				}
				else
					cout << "YOLO !!" << endl;
			}
			return false;
		}    

	default:
		return false;
	}
}

bool MouseHandler::pickCible (osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter& ea)
{
	if (!viewer->getSceneData())
		// Rien à picker
		return false;

	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (viewer->computeIntersections(ea,intersections, 0x2))
	{
		if(intersections.size()){

			const osg::NodePath& nodePath = intersections.begin()->nodePath;

			ref_ptr<Node> current = nodePath.back();
			Node* parent;
			while(current->getParents().size()){
				parent = current->getParent(0);
				if(dynamic_cast<Node110*>(parent)){
					_picked = static_cast<Node110*>(parent);
					return true;
				}
				else
					current = parent;
			}
		}
	}
	return false;
}