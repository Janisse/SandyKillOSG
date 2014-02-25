#include "Physics110.h"


Physics110::Physics110(void)
{

}


Physics110::~Physics110(void)
{
}

void Physics110::run(double temps, ref_ptr<Node110> node110)
{
	//Simulation de la physique durant un temps donné pour le node spécifié.
}


//---------------------------------------------------------------------------------------------------------------------
// Physics110CallBack -------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

Physics110CallBack::Physics110CallBack(ref_ptr<Physics110> ph)
	: _phys(ph)
{
}


void Physics110CallBack::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	ref_ptr<Node110> node110 = dynamic_cast<Node110*> (node);
	if(node110)
		_phys->run(0.005, node110);
	else
		traverse(node, nv);
}
