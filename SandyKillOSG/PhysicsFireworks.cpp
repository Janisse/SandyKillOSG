#include "PhysicsFireworks.h"


PhysicsFireworks::PhysicsFireworks(void)
{
	haveComputeFireworks = false;
	_center = Vec3(0,0,0);
	_directionFireworks = new Vec3Array();
	_randomSpeedFall = new FloatArray();
	_randomSpeedFireworks = new FloatArray();
	time = 25;
}


PhysicsFireworks::~PhysicsFireworks(void)
{
}


void PhysicsFireworks::fireworksEffect(double temps, ref_ptr<Node110> node110)
{
	ref_ptr<Vec3Array> vertexs = node110->getVertexs();

	if(haveComputeFireworks == false)
		computeFireworks(node110);

	#pragma omp parallel for schedule(dynamic)
	for(int i = 0; i < vertexs->size(); i++)
	{
		//Projection dans la direction opposé au centre de l'explosion
		vertexs->at(i) += _directionFireworks->at(i)*(time)*_randomSpeedFireworks->at(i);

		//Attraction au sol
		vertexs->at(i).z() -= 1.0 * temps + _randomSpeedFall->at(i);
	}
	time += 1;
}

void PhysicsFireworks::run(double temps, ref_ptr<Node110> node110)
{
	fireworksEffect(temps, node110);
}

void PhysicsFireworks::computeFireworks(ref_ptr<Node110> node110)
{
	std::srand(std::time(NULL));
	//On calcule le centre de l'explosion
	//On ajoute tout les points dans un vecteur
	for (int i=0; i<node110->getVertexs()->size(); i++)
	{
		_center += node110->getVertexs()->at(i);
	}
	//Et on le divise pour obtenir la moyenne de tout les points
	_center /= node110->getVertexs()->size();


	//On creer un tableau des direction opposées au centre de l'explosion pour chaque point
	//Et un tableau de vitesse aleatiore pour chaque point
	for (int i=0; i<node110->getVertexs()->size(); i++)
	{
		_directionFireworks->push_back(node110->getVertexs()->at(i) - _center);
		_randomSpeedFall->push_back(0.06+((rand()%100)/8000.));
		_randomSpeedFireworks->push_back(.0004+((rand()%100)/1000000.));
	}

	//on remet les vertices au centre
	for (int i=0; i<node110->getVertexs()->size(); i++)
	{
		node110->getVertexs()->at(i) = _center;
	}

	//on remet les couleurs
	for (int i=0; i<node110->getColors()->size(); i++)
	{
		node110->getColors()->at(i) = Vec4(
			(rand()%100 <50) ? 1.0 : 0.0,
			(rand()%100 <50) ? 1.0 : 0.0,
			(rand()%100 <50) ? 1.0 : 0.0,
			1.0);
	}

	haveComputeFireworks = true;

}