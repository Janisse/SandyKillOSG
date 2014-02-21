#pragma once

#include "CONSTANTES_LITTERALES.h"

class Node110 :
	public Group
{
public :

	//	Constantes & Enumerations	================================================================================================================
	
	
private:
	//	Variables membres			================================================================================================================
	
	ref_ptr<PositionAttitudeTransform> _trf;
	ref_ptr<Geode> _gde;
	ref_ptr<Geometry> _geom;

public:


	//	Constructeurs & Destructeur	================================================================================================================

	Node110(ref_ptr<Geometry> geom);
	~Node110(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	

	//	Fonctionnalités				================================================================================================================
	
	void Node110::event_RotationHaut(bool acceleration);
	void Node110::event_RotationBas(bool acceleration);
	void Node110::event_RotationGauche(bool acceleration);
	void Node110::event_RotationDroite(bool acceleration);
};

