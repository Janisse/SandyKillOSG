#include "PhysicsWeird.h"


PhysicsWeird::PhysicsWeird(void)
{
	_mass = 0.00;
}


PhysicsWeird::~PhysicsWeird(void)
{
}

void PhysicsWeird::run(double temps)
{
#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbVertices; i++)
	{

		//On modifit la trajectoire de points au hasard
		if(rand()%10 == 1)
			_movement->at(i) = Vec3(((rand()%10)-5)/100.0f, ((rand()%10)-5)/100.0f, ((rand()%10)-5)/100.0f);
		//On calcule la nouvelle vitesse
		_speed->at(i) = _movement->at(i);

		//On actualise la position
		_vertices->at(i) += _speed->at(i);
	}

#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_colors->size(); i++)
	{
		//On actualise la couleur
		_colors->at(i) = Vec4(0.0, 0.0, 0.0, 1.0);
	}
}

void PhysicsWeird::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();

	// On calcule les vecteurs de départ
#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbVertices; i++)
	{
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}

	for (int i=0; i<_nbFaces; i++)
	{
		_colors->at(i) = Vec4(0,0,0,1);
	}
}

osg::StateSet* PhysicsWeird::makeStateSet()
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