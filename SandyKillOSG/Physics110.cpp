#include "Physics110.h"


Physics110::Physics110()
	: _gravity(0, 0, -0.89)
	, _speed_attenuation(0.985)
	, _mass(1)
{
	_movement = new Vec3Array();
	_projection = new Vec3Array();
	_speed = new Vec3Array();

	_vertices = new Vec3Array();
	_faces = new Vec3Array();
}


Physics110::~Physics110(void)
{
}

void Physics110::run(double temps)
{
	//Simulation de la physique durant un temps donné pour le node spécifié.
}

void Physics110::init(ref_ptr<Node110> node110)
{
	_vertices = node110->getVertexs();
	_nbVertices = _vertices->size();
	_faces = node110->getFaces();
	_nbFaces = _faces->size();
}

// à mettre dans les physiques
osg::StateSet* Physics110::makeStateSet()
{
	osg::StateSet *set = new osg::StateSet();

	/// Setup cool blending
	set->setMode(GL_BLEND, osg::StateAttribute::ON);

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


//---------------------------------------------------------------------------------------------------------------------
// Physics110CallBack -------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

Physics110CallBack::Physics110CallBack(ref_ptr<Physics110> ph)
	: _phys(ph)
{
}


void Physics110CallBack::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	ref_ptr<Node110> node110 = dynamic_cast<Node110*> (node);
	if(node110)
		_phys->run(0.016);	//60fps
	else
		traverse(node, nv);
}
