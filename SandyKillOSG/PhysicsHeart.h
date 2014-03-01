#pragma once
#include "CONSTANTES_LITTERALES.h"
#include "physics110.h"
class PhysicsHeart :
	public Physics110
{
public:
	private:

	Vec3 _center;
	ref_ptr<Vec4Array> _colors;

public:
	PhysicsHeart(void);
	~PhysicsHeart(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
};

