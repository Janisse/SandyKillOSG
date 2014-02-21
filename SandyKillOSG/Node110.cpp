#include "Node110.h"


Node110::Node110(ref_ptr<Geometry> geom)
{


}


Node110::~Node110(void)
{
}

void Node110::event_RotationHaut(bool acceleration)
{
	// ...
	if (acceleration)
		angleRotation = DegreesToRadians(-4.);
	else
		angleRotation = 0.;
}

void Node110::event_RotationBas(bool acceleration)
{
	// ...
	if (acceleration)
		angleRotation = DegreesToRadians(4.);
	else
		angleRotation = 0.;
}

void Node110::event_RotationGauche(bool acceleration)
{
	// ...
	if (acceleration)
		angleRotation = DegreesToRadians(-4.);
	else
		angleRotation = 0.;
}

void Node110::event_RotationDroite(bool acceleration)
{
	// ...
	if (acceleration)
		angleRotation = DegreesToRadians(4.);
	else
		angleRotation = 0.;
}


