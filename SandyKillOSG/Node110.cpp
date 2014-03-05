#include "Node110.h"
#include "Loader110.h"
#include "Subdivisor.h"

Node110::Node110()
{
	_trf = new PositionAttitudeTransform;
	_gde = new Geode;
	_geom = new Geometry;
	_gde->addDrawable(_geom);
	_vertexs = new Vec3Array();
	_faces = new Vec3Array();
	_colors = new Vec4Array();

	_gdeSubSave = new Geode;
	_geomSubSave = new Geometry;
	_gdeSubSave->addDrawable(_geomSubSave);
	_vertexsSubSave = new Vec3Array();
	_facesSubSave = new Vec3Array();
	_colorsSubSave = new Vec4Array();

	_gdeOriginal = new Geode;
	_geomOriginal = new Geometry;
	_gdeOriginal->addDrawable(_geomOriginal);
	_vertexsOriginal = new Vec3Array();
	_facesOriginal = new Vec3Array();
	_colorsOriginal = new Vec4Array();

	_swh = new Switch();
	_trf->addChild(_swh);
	this->addChild(_trf);

	_swh->addChild(_gdeOriginal);
	_swh->addChild(_gdeSubSave);
	_swh->addChild(_gde);
	_swh->setSingleChildOn(0);
}

Node110::Node110(ref_ptr<Geometry> geom, unsigned int nbSubs)
	: _nbSubdivisions(nbSubs)
{
	_trf = new PositionAttitudeTransform;
	_gde = new Geode;
	_geom = geom;
	_gde->addDrawable(_geom);
	_trf->addChild(_gde);
	this->addChild(_trf);
}


Node110::~Node110(void)
{
}

void Node110::event_RotationHaut(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(-1,0,0,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::event_RotationBas(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(1,0,0,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::event_RotationGauche(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(0,0,-1,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::event_RotationDroite(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(0,0,1,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::convertToSprites()
{
	_gde->setStateSet(Loader110::makeStateSet(10.0f));
}

void Node110::subdivide110()
{
	Subdivisor subdivisor(this);
	subdivisor.subdivide(_nbSubdivisions);
}

//Passe d'une geometry a une autre
//0 -> geometry original
//1 -> geometry subdivisé
//2 -> geometry modifiable
bool Node110::switchGeometry(int i)
{
	switch(i)
	{
	case 0:
		_swh->setSingleChildOn(0);
		return true;
	case 1:
		_swh->setSingleChildOn(1);
		return true;
	case 2:
		_swh->setSingleChildOn(2);
		return true;
	default:
		return false;
	}
}

void Node110::restoreSubdivision()
{
	//Copie la geometry subdivisée pour la sauvegarder
	_vertexs = dynamic_cast<Vec3Array*>(_vertexsSubSave->clone(CopyOp(CopyOp::DEEP_COPY_ALL)));
	_faces = dynamic_cast<Vec3Array*>(_facesSubSave->clone(CopyOp(CopyOp::DEEP_COPY_ALL)));
	//On crée la geometry subdivisée sauvegardée
	_geom->setVertexArray(_vertexs);
	_geom->setPrimitiveSetList(_geomSubSave->getPrimitiveSetList());
}