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
