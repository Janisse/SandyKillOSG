#pragma once

#include "CONSTANTES_LITTERALES.h"


class Loader110;
class Subdivisor;

class Node110 :
	public Group
{
public :

	//	Constantes & Enumerations	================================================================================================================
	
	
private:
	//	Variables membres			================================================================================================================
	
	ref_ptr<PositionAttitudeTransform> _trf;
	ref_ptr<Switch> _swh;
	ref_ptr<Geode> _gde;
	ref_ptr<Geometry> _geom;
	ref_ptr<Vec3Array> _vertexs;
	ref_ptr<Vec3Array> _faces;
	ref_ptr<Vec4Array> _colors;

	
	ref_ptr<Geode> _gdeSubSave;
	ref_ptr<Geometry> _geomSubSave;
	ref_ptr<Vec3Array> _vertexsSubSave;
	ref_ptr<Vec3Array> _facesSubSave;
	ref_ptr<Vec4Array> _colorsSubSave;

	ref_ptr<Geode> _gdeOriginal;
	ref_ptr<Geometry> _geomOriginal;
	ref_ptr<Vec3Array> _vertexsOriginal;
	ref_ptr<Vec3Array> _facesOriginal;
	ref_ptr<Vec4Array> _colorsOriginal;

	unsigned int _nbSubdivisions;
	bool _subdivided;

public:

	//	Constructeurs & Destructeur	================================================================================================================

	Node110(unsigned int nbSubs=2);
	Node110::Node110(ref_ptr<Geometry> geom, unsigned int nbSubs);
	~Node110(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	ref_ptr<PositionAttitudeTransform> getTrf() {return _trf;}
	ref_ptr<Geode> getGde() {return _gde;}
	ref_ptr<Geometry> getGeometry() {return _geom;}
	ref_ptr<Vec3Array> getVertexs() {return _vertexs;}
	ref_ptr<Vec3Array> getFaces() {return _faces;}
	ref_ptr<Vec4Array> getColors() {return _colors;}

	ref_ptr<Geode> getSubSave() {return _gdeSubSave;}
	ref_ptr<Geometry> getGeometrySubSave() {return _geomSubSave;}
	ref_ptr<Vec3Array> getVertexsSubSave() {return _vertexsSubSave;}
	ref_ptr<Vec3Array> getFacesSubSave() {return _facesSubSave;}
	ref_ptr<Vec4Array> getColorsSubSave() {return _colorsSubSave;}
	void setVertexsSubSave(ref_ptr<Vec3Array> vertexsSubSave) {_vertexsSubSave = vertexsSubSave;}
	void setFacesSubSave(ref_ptr<Vec3Array> facesSubSave) {_facesSubSave = facesSubSave;}

	ref_ptr<Geode> getOriginal() {return _gdeOriginal;}
	ref_ptr<Geometry> getGeometryOriginal() {return _geomOriginal;}
	ref_ptr<Vec3Array> getVertexsOriginal() {return _vertexsOriginal;}
	ref_ptr<Vec3Array> getFacesOriginal() {return _facesOriginal;}
	ref_ptr<Vec4Array> getColorsOriginal() {return _colorsOriginal;}
	void setVertexsOriginal(ref_ptr<Vec3Array> vertexsOriginal) {_vertexsOriginal = vertexsOriginal;}
	void setFacesOriginal(ref_ptr<Vec3Array> facesOriginal) {_facesOriginal = facesOriginal;}

	void setFaces(ref_ptr<Vec3Array> faces) {_faces = faces;}
	void setNbSubdivisions( unsigned int n) { _nbSubdivisions = n;}
	bool isSubdivided(){return _subdivided;}

	//	Fonctionnalités				================================================================================================================
	
	void event_RotationHaut(bool acceleration);
	void event_RotationBas(bool acceleration);
	void event_RotationGauche(bool acceleration);
	void event_RotationDroite(bool acceleration);
	void convertToSprites();
	void subdivide110();
	bool switchGeometry(int i);
	void restoreSubdivision();
};

