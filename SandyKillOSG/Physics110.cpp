#include "Physics110.h"


Physics110::Physics110(void)
{
	update = new ref_ptr<Physics110CallBack>;
}


Physics110::~Physics110(void)
{
}

void Physics110::startUpdate(ref_ptr<Node110> _node110, Vec3 center)
{
	node110 = _node110;
	node110->setUpdateCallback(update.get());
}



//CallBack
Physics110CallBack::Physics110CallBack(void)
{
}


void Physics110CallBack::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	ref_ptr<Physics110> node110 = dynamic_cast<Physics110*> (node->getUserData());
	if(node110)
		node110->run();
}
