#include "Physics110.h"


Physics110::Physics110(void)
{
	_update = new Physics110CallBack;
}


Physics110::~Physics110(void)
{
}

void Physics110::startUpdate(ref_ptr<Node110> node110, Vec3 center)
{
	_node110 = node110;
	_node110->setUpdateCallback(_update.get());
}



//CallBack
Physics110CallBack::Physics110CallBack(void)
{
}


void Physics110CallBack::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	ref_ptr<Node110> node110 = dynamic_cast<Node110*> (node);
	//if(node110)
		//Physics110::update(2.0, node110);
}
