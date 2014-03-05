#include "PhysicsHeart.h"


PhysicsHeart::PhysicsHeart(void)
	: _seuilBattement(7.)
{
	_center = Vec3(0,0,0);
	_mass = 0.00;
}


PhysicsHeart::~PhysicsHeart(void)
{
}


void PhysicsHeart::run(double temps)
{
	_timesomm += temps;

#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);

		//On met � jour les acc�l�rations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);

		//calcul le battement du coeur
		_distance = max((sin(_timesomm * 0.2)* 1.0), _seuilBattement);

	}

#pragma omp parallel for
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		_colors->at(i) = Vec4(1.0, 0.2, 0.2, 1.0);
	}
}

void PhysicsHeart::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();
	_prevertices = dynamic_cast<Vec3Array*>(_vertices->clone(CopyOp::DEEP_COPY_ALL));

	std::srand(std::time(NULL));

	//On calcule le centre
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_center += _vertices->at(i);
	}
	_center /= _vertices->size();

	// On calcule les vecteurs de d�part
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_projection->at(i) = Vec3(0,0,0);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}


}