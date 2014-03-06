#include "PhysicsHeart.h"


PhysicsHeart::PhysicsHeart(void)
	: _seuilBattement(0.8)
{
	_center = Vec3(0,0,0);
	_mass = 0.00;
	_timesomm = 0.0;
}


PhysicsHeart::~PhysicsHeart(void)
{
}


void PhysicsHeart::run(double temps)
{
	_timesomm += temps;
	_distance = 1 + max(sin((_timesomm)* 6.0), _seuilBattement) - _seuilBattement;


//#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);

		//On met à jour les accélérations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);

		//calcul le battement du coeur
		_trf->setScale(Vec3d(_distance, _distance, _distance));
	}
}

void PhysicsHeart::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();
	_trf = node110->getTrf();

	//On calcule le centre
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_center += _vertices->at(i);
	}
	_center /= _vertices->size();
	_trf->setPivotPoint(_center);

	// On calcule les vecteurs de départ
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_projection->at(i) = Vec3(0,0,0);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}
	
#pragma omp parallel for
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		_colors->at(i) = Vec4(1.0, 0.2, 0.2, 1.0);
	}
}