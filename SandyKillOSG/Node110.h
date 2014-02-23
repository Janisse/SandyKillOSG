#pragma once

#include "CONSTANTES_LITTERALES.h"

class Loader110;

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
	ref_ptr<Vec3Array> _vertexs;
	ref_ptr<Vec3Array> _faces;

public:


	//	Constructeurs & Destructeur	================================================================================================================

	Node110();
	Node110::Node110(ref_ptr<Geometry> geom);
	~Node110(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	ref_ptr<PositionAttitudeTransform> getTrf() {return _trf;}
	ref_ptr<Geode> getGde() {return _gde;}
	ref_ptr<Geometry> getGeometry() {return _geom;}
	ref_ptr<Vec3Array> getVertexs() {return _vertexs;}
	ref_ptr<Vec3Array> getFaces() {return _faces;}

	//	Fonctionnalités				================================================================================================================
	
	void event_RotationHaut(bool acceleration);
	void event_RotationBas(bool acceleration);
	void event_RotationGauche(bool acceleration);
	void event_RotationDroite(bool acceleration);
	void convertToSprites();

	//bool loadFromFile(const char * path);
};

