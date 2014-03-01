#pragma once
#include "Physics110.h"
#include "CONSTANTES_LITTERALES.h"

class PhysicsExplosion : public Physics110
{
private:

	Vec3 _center;
	ref_ptr<Vec4Array> _colors;
	float _explosion_size;
	float _frottements;

public:
	PhysicsExplosion(void);
	~PhysicsExplosion(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
};

