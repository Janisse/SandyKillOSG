#include "PhysicsHeart.h"


PhysicsHeart::PhysicsHeart(void)
{
	_center = Vec3(0,0,0);
	_mass = 0.00;
}


PhysicsHeart::~PhysicsHeart(void)
{
}


void PhysicsHeart::run(double temps)
{
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);

		//On met à jour les accélérations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);
	}

#pragma omp parallel for
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		/*_colors->at(i) = Vec4(
			(rand()%100 <50) ? 1.0 : 0.0,
			(rand()%100 <50) ? 1.0 : 0.0,
			(rand()%100 <50) ? 1.0 : 0.0,
			1.0);*/
	}
}

void PhysicsHeart::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();

	std::srand(std::time(NULL));

	//On calcule le centre de l'explosion
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_center += _vertices->at(i);
	}
	_center /= _vertices->size();

	// On calcule les vecteurs de départ
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_projection->at(i) = Vec3(0,0,0);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}
}