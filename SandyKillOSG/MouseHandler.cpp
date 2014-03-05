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
	case osgGA::GUIEventAdapter::RELEASE:
		{
			// If the mouse hasn't moved since the last
			//   button press or move event, perform a
			//   pick. (Otherwise, the trackball
			//   manipulator will handle it.)
			_mX = ea.getX();
			_mY = ea.getY();
			if (_mX && _mY)
			{
				if (pickCible( viewer, ea.getXnormalized(), ea.getYnormalized()))
				{
					_world->setSelected(_picked);
					if(_picked)
						_world->resetModel();
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

		//0:Scengraph
		//1:Node110
		//2:Transform
		//3:Switch
		//4:Geode
		ref_ptr<osg::Node> node = (nodePath.size() >= 2)?nodePath[1]:0;			
		//ref_ptr<osg::Node> nde = nodePath.back();
		if(node)
			_picked = dynamic_cast<Node110*>(node.get());
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