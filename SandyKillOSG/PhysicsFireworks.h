#pragma once
#include "CONSTANTES_LITTERALES.h"
#include "physics110.h"
class PhysicsFireworks : public Physics110
{
private:

	Vec3 _center;
	ref_ptr<Vec4Array> _colors;
	float _luminance_attenuation;
	float _explosion_size;
	float _frottements;

public:
	PhysicsFireworks(void);
	~PhysicsFireworks(void);

	void run(double temps);
	void init(ref_ptr<Node110> node110);
};

