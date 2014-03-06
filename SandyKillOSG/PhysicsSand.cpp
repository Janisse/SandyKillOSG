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
			if(!_onGround->at(i)){
				double dirproj = (rand()%1000/1000.)*PI*2;
				double amp = 0.014 * (rand()%1000/1000.);
				_projection->at(i) = Vec3(
					cos(dirproj)*amp,
					sin(dirproj)*amp,
					0);
			}
			_onGround->at(i) = true;
		}
	}

#pragma omp parallel for
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		_colors->at(i) = Vec4(.678, 0.5, 0, 1);
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
	_onGround = new ByteArray(_vertices->size());

	// On calcule les vecteurs de départ
#pragma omp parallel for
	for (int i=0; i<_nbVertices; i++)
	{
		_projection->at(i) = Vec3(0,0,0);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
		_masses->at(i) = _mass * (0.8 + (rand()%10/100.*4. + 0.2));
		_onGround->at(i) = false;
	}
}

// à mettre dans les physiques
osg::StateSet* PhysicsSand::makeStateSet()
{
	osg::StateSet *set = new osg::StateSet();

	/// Setup cool blending
	set->setMode(GL_BLEND, osg::StateAttribute::ON);

	/// Setup the point sprites
	osg::PointSprite *sprite = new osg::PointSprite();
	set->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	/// Give some size to the points to be able to see the sprite
	osg::Point *point = new osg::Point();
	point->setSize(2.0);
	set->setAttribute(point);

	/// Disable depth test to avoid sort problems and Lighting
	set->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	/// The texture for the sprites
	//osg::Texture2D *tex = new osg::Texture2D();
	//tex->setImage(osgDB::readImageFile("resources/star.bmp"));
	//set->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);
	return set;
}