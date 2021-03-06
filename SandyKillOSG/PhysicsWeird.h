#pragma once
#include "physics110.h"
#include "CONSTANTES_LITTERALES.h"
class PhysicsWeird :
	public Physics110
{
private:
	ref_ptr<Vec4Array> _colors;

public:
	PhysicsWeird(void);
	~PhysicsWeird(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
	osg::StateSet* makeStateSet();
};

