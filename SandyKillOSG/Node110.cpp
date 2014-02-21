#include "Node110.h"


Node110::Node110(ref_ptr<Geometry> geom)
	: _geom(geom)
{
	_trf = new PositionAttitudeTransform;
	_gde = new Geode;
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
