#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "Physics110.h"

class PhysicsExplosion : public Physics110
{
public:
	PhysicsExplosion(void);
	virtual ~PhysicsExplosion(void);
	void update(double time, ref_ptr<Node110> node110);
};