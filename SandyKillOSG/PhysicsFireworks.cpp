#include "PhysicsFireworks.h"


PhysicsFireworks::PhysicsFireworks(void)
	: _explosion_size(0.06)
	, _frottements(0.9984)
{
	_center = Vec3(0,0,0);
	_mass = 0.02;
}


PhysicsFireworks::~PhysicsFireworks(void)
{
}


void PhysicsFireworks::run(double temps)
{
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);
		_speed->at(i) += _gravity*_mass*temps;
		_speed->at(i) *= _speed_attenuation * _frottements;

		//On met à jour les accélérations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);
	}

#pragma omp parallel for
	for (int i=0; i<_nbFaces; i++)
	{
		//On actualise la couleur
		_colors->at(i).r() *= _luminance_attenuations->at(i);
		_colors->at(i).g() *= _luminance_attenuations->at(i);
		_colors->at(i).b() *= _luminance_attenuations->at(i);
	}
}

void PhysicsFireworks::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();

	_luminance_attenuations = new FloatArray(_nbFaces);

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
		_projection->at(i) = Vec3(_vertices->at(i) - _center) * _explosion_size * ((rand()%100 /400.)+0.75);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}

#pragma omp parallel for
	for (int i=0; i<_nbFaces; i++)
	{
		_colors->at(i).r() = (rand()%100 <50) ? 1.0 : 0.0;
		_colors->at(i).g() = (rand()%100 <50) ? 1.0 : 0.0;
		_colors->at(i).b() = (rand()%100 <50) ? 1.0 : 0.0;
		_colors->at(i).a() = 1.0;
		_luminance_attenuations->at(i) = 0.98 + (rand()%100/40000.);
	}
}