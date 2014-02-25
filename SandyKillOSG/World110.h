#pragma once

#include "CONSTANTES_LITTERALES.h"

#include "Node110.h"


class World110 : public Group
{
private:

	//	Constantes & Enumerations	================================================================================================================
	
	ref_ptr<Group> _scenegraph;
	ref_ptr<Node110> _selected;
	ref_ptr<Node> _skybox;

	//	Variables membres			================================================================================================================

public:

	//	Constructeurs & Destructeur	================================================================================================================

	World110(void);
	~World110(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	ref_ptr<Group> getScenegraph() {return _scenegraph;}
	ref_ptr<Node110> getSelected() {return _selected;}
	void setSelected(ref_ptr<Node110> s) { _selected = s;}

	//	Fonctionnalités				================================================================================================================

};

