#include "PhysicsSand.h"


PhysicsSand::PhysicsSand(void)
{
}


PhysicsSand::~PhysicsSand(void)
{
}


void sandEffect(double temps, ref_ptr<Node110> node110)
{
	for(int i = 0; i < node110->getVertexs()->size(); i++)
	{
		if(node110->getVertexs()->at(i).z() > -10)
		{
			node110->getVertexs()->at(i).z()-= 2.0 * temps;
		}
	}
}

void update(double temps, ref_ptr<Node110> node110)
{
	sandEffect(temps, node110);
}