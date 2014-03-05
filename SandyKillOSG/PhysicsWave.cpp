#include "PhysicsWave.h"


PhysicsWave::PhysicsWave(void)
{
	_center = Vec3(0,0,0);
	_mass = 0.00;
	_timesomm = 0.0;
}


PhysicsWave::~PhysicsWave(void)
{
}


void PhysicsWave::run(double temps)
{
	_timesomm += temps;

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

		//On calcul les vagues
		_vertices->at(i).z() = .5 - cos((_timesomm + _vertices->at(i).x())* 3.0) * 0.5;
	}

#pragma omp parallel for
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		_colors->at(i) = Vec4(0.1, 0.2, 9.0, 1.0);
	}
}

void PhysicsWave::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();
	_prevertices = dynamic_cast<Vec3Array*>(_vertices->clone(CopyOp::DEEP_COPY_ALL));
}