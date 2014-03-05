#include "PhysicsExplosion.h"


PhysicsExplosion::PhysicsExplosion(void)
	: _explosion_size(0.2)
	, _frottements(1)
{
	_center = Vec3(0,0,0);
	_mass = 0;
}


PhysicsExplosion::~PhysicsExplosion(void)
{
}


void PhysicsExplosion::run(double temps)
{
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);
		//_speed->at(i) += _gravity*_mass*temps;
		_speed->at(i) *= _speed_attenuation * _frottements;

		//On met à jour les accélérations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);
	}
}

void PhysicsExplosion::init(ref_ptr<Node110> node110)
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
		_projection->at(i) = Vec3(_vertices->at(i) - _center) * _explosion_size * ((rand()%100 /100.)+0.1);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}
}