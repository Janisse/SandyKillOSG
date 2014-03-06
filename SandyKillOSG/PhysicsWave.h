#pragma once
#include "physics110.h"
#include "CONSTANTES_LITTERALES.h"
class PhysicsWave :
	public Physics110
{
private:

	Vec3 _center;
	ref_ptr<Vec4Array> _colors;
	ref_ptr<Vec3Array> _prevertices;
	double _timesomm;

public:
	PhysicsWave(void);
	~PhysicsWave(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
	osg::StateSet* makeStateSet();
};