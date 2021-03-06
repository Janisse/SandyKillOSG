#pragma once

#include "CONSTANTES_LITTERALES.h"

#include "World110.h"
#include "Node110.h"

class MouseHandler
	: public osgGA::GUIEventHandler
{

public :
	//	Constantes & Enumerations	================================================================================================================
	
	
private:
	//	Variables membres			================================================================================================================

	float _mX, _mY;

	ref_ptr<World110> _world;		// Le graphe � visiter
	ref_ptr<Node110> _picked;		// Le node qui a �t� click�

public:
	//	Constructeurs & Destructeur	================================================================================================================

	MouseHandler(ref_ptr<World110> w);
	~MouseHandler(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	ref_ptr<Node110> getPicked() {return _picked;}

	//	Fonctionnalit�s				================================================================================================================

	bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);

private :

	bool pickCible (osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter& ea);

};

