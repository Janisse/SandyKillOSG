#include "PhysicsSand.h"


PhysicsSand::PhysicsSand(void)
	: _frottements(0.9984)
	, _distance_ground(-8)
{
	_mass = 0.09;
}


PhysicsSand::~PhysicsSand(void)
{
}

void PhysicsSand::run(double temps)
{
	#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);
		_speed->at(i) += _gravity*_masses->at(i)*temps;
		_speed->at(i) *= _speed_attenuation * _frottements;

		//On met à jour les accélérations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);
		if(_vertices->at(i).z() <= _distance_ground)
		{
			_vertices->at(i).z() = _distance_ground;
			_projection->at(i) = Vec3(
				(rand()%100 - 50) / 4000.,
				(rand()%100 - 50) / 4000.,
				0);
		}
	}

#pragma omp parallel for
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		_colors->at(i) = Vec4(.678, 0, 0, 1);
	}
}

void PhysicsSand::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();

	std::srand(std::time(NULL));

	_masses = new FloatArray(_vertices->size());

	// On calcule les vecteurs de départ
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_projection->at(i) = Vec3(0,0,0);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
		_masses->at(i) = _mass * (0.8 + (rand()%10/100.*4. + 0.2));
	}
}