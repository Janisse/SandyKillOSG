#include "PhysicsExplosion.h"


PhysicsExplosion::PhysicsExplosion(void)
	: _explosion_size(0.02)
	, _frottements(0.999989)
{
	_center = Vec3(0,0,0);
	_mass = 0;
}


PhysicsExplosion::~PhysicsExplosion(void)
{
}


/*void PhysicsFireworks::fireworksEffect(double temps)
{
ref_ptr<Vec3Array> vertexs = node110->getVertexs();

#pragma omp parallel for schedule(dynamic)
for(int i = 0; i < vertexs->size(); i++)
{
//Projection dans la direction opposé au centre de l'explosion
vertexs->at(i) += _directionFireworks->at(i)*(time)*_randomSpeedFireworks->at(i);

//Attraction au sol
vertexs->at(i).z() -= 1.0 * temps + _randomSpeedFall->at(i);
}
time += 1;
}*/

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
		_projection->at(i) = Vec3(_vertices->at(i) - _center) * _explosion_size * (rand()%100 /100.);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}
}

/*void PhysicsFireworks::computeFireworks()
{
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


}*/