#pragma once
#include "Physics110.h"
#include "Node110.h"
#include "CONSTANTES_LITTERALES.h"

class PhysicsExplosion : public Physics110
{
private:
	bool haveComputeExplosion;
	Vec3 _center;
	ref_ptr<Vec3Array> _directionExplosion;
	float time;

public:
	PhysicsExplosion(void);
	~PhysicsExplosion(void);

	void explosionEffect(double temps, ref_ptr<Node110> node110);
	void run(double temps, ref_ptr<Node110> node110);
	void computeExplosion(ref_ptr<Node110> node110);
};

