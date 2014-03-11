#include "PhysicsFireworks.h"


PhysicsFireworks::PhysicsFireworks(void)
	: _explosion_size(0.06)
	, _frottements(0.9984)
	, _luminance_attenuation(0.988)
{
	_center = Vec3(0,0,0);
	_mass = 0.02;
}


PhysicsFireworks::~PhysicsFireworks(void)
{
}


void PhysicsFireworks::run(double temps)
{
#pragma omp parallel for schedule(dynamic)
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

#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbFaces; i++)
	{
		//On actualise la couleur
		_colors->at(i).r() *= _luminance_attenuation;
		_colors->at(i).g() *= _luminance_attenuation;
		_colors->at(i).b() *= _luminance_attenuation;
	}
}

void PhysicsFireworks::init(ref_ptr<Node110> node110)
{
	Physics110::init(node110);
	_projection = new Vec3Array(_nbVertices);
	_movement = new Vec3Array(_nbVertices);
	_speed = new Vec3Array(_nbVertices);
	_colors = node110->getColors();

	//On calcule le centre de l'explosion
#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbVertices; i++)
	{
		_center += _vertices->at(i);
	}
	_center /= _vertices->size();

	// On calcule les vecteurs de départ
#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbVertices; i++)
	{
		_projection->at(i) = Vec3(_vertices->at(i) - _center) * _explosion_size * ((rand()%100 /400.)+0.75);
		_movement->at(i) = Vec3(0,0,0);
		_speed->at(i) = Vec3(0,0,0);
	}

#pragma omp parallel for schedule(dynamic)
	for (int i=0; i<_nbFaces; i++)
	{
		int coulnum = rand()%6;
		Vec4 couleur;
		switch(coulnum){
		case 0: couleur = Vec4(1,0,0,1); break;		// Rouge
		case 1: couleur = Vec4(1,1,0,1); break;		// Jaune
		case 2: couleur = Vec4(0,1,0,1); break;		// Vert
		case 3: couleur = Vec4(0,1,1,1); break;		// Cyan
		case 4: couleur = Vec4(0,0,1,1); break;		// Bleu
		case 5: couleur = Vec4(1,0,1,1); break;		// Magenta
		}
		_colors->at(i) = couleur;
	}
}

osg::StateSet* PhysicsFireworks::makeStateSet()
{
	osg::StateSet *set = new osg::StateSet();

	/// Setup cool blending
	set->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::BlendFunc *fn = new osg::BlendFunc();
	fn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::DST_ALPHA);
	set->setAttributeAndModes(fn, osg::StateAttribute::ON);

	/// Setup the point sprites
	osg::PointSprite *sprite = new osg::PointSprite();
	set->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	/// Give some size to the points to be able to see the sprite
	osg::Point *point = new osg::Point();
	point->setSize(4.0);
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