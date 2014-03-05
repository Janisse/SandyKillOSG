#pragma once
#include "CONSTANTES_LITTERALES.h"
#include "physics110.h"
class PhysicsHeart :
	public Physics110
{
private:

	Vec3 _center;
	ref_ptr<Vec4Array> _colors;
	float _distance;
	float _seuilBattement;
	double _timesomm;
	ref_ptr<PositionAttitudeTransform> _trf;

public:
	PhysicsHeart(void);
	~PhysicsHeart(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
};

