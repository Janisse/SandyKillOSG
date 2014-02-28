#pragma once
#include "CONSTANTES_LITTERALES.h"
#include "physics110.h"
class PhysicsFireworks :
	public Physics110
{
private:
	bool haveComputeFireworks;
	Vec3 _center;
	ref_ptr<Vec3Array> _directionFireworks;
	ref_ptr<FloatArray> _randomSpeedFall;
	ref_ptr<FloatArray> _randomSpeedFireworks;
	float time;

public:
	PhysicsFireworks(void);
	~PhysicsFireworks(void);

	void fireworksEffect(double temps, ref_ptr<Node110> node110);
	void run(double temps, ref_ptr<Node110> node110);
	void computeFireworks(ref_ptr<Node110> node110);
};

