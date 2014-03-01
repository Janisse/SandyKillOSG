#pragma once
#include "Physics110.h"
#include "CONSTANTES_LITTERALES.h"

class PhysicsSand : public Physics110
{
public:
	PhysicsSand(void);
	~PhysicsSand(void);

	void sandEffect(double temps, ref_ptr<Node110> node110);
	void run(double temps, ref_ptr<Node110> node110);
};

