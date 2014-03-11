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

#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbVertices; i++)
	{
		//On calcule la nouvelle vitesse
		_speed->at(i) += _projection->at(i);
		_speed->at(i) += _movement->at(i);

		//On met à jour les accélérations
		_projection->at(i) = Vec3(0,0,0);

		//On actualise la position
		_prevertices->at(i) += _speed->at(i);

		//On calcul les vagues

		_vertices->at(i).z() = _prevertices->at(i).z() + .8 - cos((_timesomm + _vertices->at(i).x())* 3.0) * 0.2;
		_vertices->at(i).y() = _prevertices->at(i).y() + .8 - cos((_timesomm + _vertices->at(i).x())* 3.0) * 0.2;
	}

#pragma omp parallel for schedule(dynamic)
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

osg::StateSet* PhysicsWave::makeStateSet()
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
	osg::Texture2D *tex = new osg::Texture2D();
	tex->setImage(osgDB::readImageFile("resources/star.bmp"));
	set->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);
	return set;
}