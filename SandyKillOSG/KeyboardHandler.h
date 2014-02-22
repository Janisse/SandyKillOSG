#pragma once

#include "CONSTANTES_LITTERALES.h"

#include "World110.h"

class KeyboardHandler
	: public osgGA::GUIEventHandler
{
public :

	//	Constantes & Enumerations	================================================================================================================
	
	
private:
	//	Variables membres			================================================================================================================
	
	ref_ptr<World110> _world;		// Le graphe � visiter

public:


	//	Constructeurs & Destructeur	================================================================================================================

	KeyboardHandler(ref_ptr<World110> w);
	~KeyboardHandler(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	

	//	Fonctionnalit�s				================================================================================================================

	bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);
	osg::NodePath pickCible (osgViewer::Viewer* viewer, float mx,float my);


};
