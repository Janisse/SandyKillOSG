#pragma once
#include "physics110.h"
#include "Node110.h"
#include "CONSTANTES_LITTERALES.h"

class PhysicsSand : public Physics110
{
public:
	PhysicsSand(void);
	~PhysicsSand(void);

	void sandEffect(double temps, ref_ptr<Node110> node110);
	void update(double time, ref_ptr<Node110> node110);
};

