#include "PhysicsExplosion.h"


PhysicsExplosion::PhysicsExplosion(void)
{
	haveComputeExplosion = false;
	_center = Vec3(0,0,0);
	_directionExplosion = new Vec3Array();
	time = 25;
}


PhysicsExplosion::~PhysicsExplosion(void)
{
}


void PhysicsExplosion::explosionEffect(double temps, ref_ptr<Node110> node110)
{
	if(haveComputeExplosion == false)
		computeExplosion(node110);

	for(int i = 0; i < node110->getVertexs()->size(); i++)
	{
		if(node110->getVertexs()->at(i).z() > -2.0)
		{
			//Projection dans la direction opposé au centre de l'explosion
			node110->getVertexs()->at(i) += _directionExplosion->at(i)*(1/time);

			//Attraction au sol
			node110->getVertexs()->at(i).z() -= 1.0 * temps + (rand()%100)/8000.;
		}
		else
			node110->getVertexs()->at(i).z() = -2;
	}
	time += 1;
}

void PhysicsExplosion::run(double temps, ref_ptr<Node110> node110)
{
	explosionEffect(temps, node110);
}

void PhysicsExplosion::computeExplosion(ref_ptr<Node110> node110)
{
	//On calcule le centre de l'explosion
	//On ajoute tout les points dans un vecteur
	for (int i=0; i<node110->getVertexs()->size(); i++)
	{
		_center += node110->getVertexs()->at(i);
	}
	//Et on le divise pour obtenir la moyenne de tout les points
	_center /= node110->getVertexs()->size();


	//On creer un tableau des direction opposées au centre de l'explosion pour chaque point
	for (int i=0; i<node110->getVertexs()->size(); i++)
	{
		_directionExplosion->push_back(node110->getVertexs()->at(i) - _center);
	}
}