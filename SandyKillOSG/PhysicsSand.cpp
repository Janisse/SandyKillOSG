#include "PhysicsSand.h"


PhysicsSand::PhysicsSand(void)
{
}


PhysicsSand::~PhysicsSand(void)
{
}


void PhysicsSand::sandEffect(double temps, ref_ptr<Node110> node110)
{
	for(int i = 0; i < node110->getVertexs()->size(); i++)
	{
		if(node110->getVertexs()->at(i).z() > HAUTEUR_SOL)
		{
			node110->getVertexs()->at(i).z() -= 1.0 * temps + (rand()%100)/8000.;
		}
		else
			node110->getVertexs()->at(i).z() = HAUTEUR_SOL;
	}
}

void PhysicsSand::run(double temps, ref_ptr<Node110> node110)
{
	sandEffect(temps, node110);
}