#pragma once
#include "Physics110.h"
#include "CONSTANTES_LITTERALES.h"

class PhysicsSand : public Physics110
{
private:

	ref_ptr<Vec4Array> _colors;
	float _frottements;
	float _distance_ground;
	ref_ptr<FloatArray> _masses;
	ref_ptr<ByteArray> _onGround;

public:
	PhysicsSand(void);
	~PhysicsSand(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
	osg::StateSet* makeStateSet();
};

