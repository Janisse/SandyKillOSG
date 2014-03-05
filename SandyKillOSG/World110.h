#pragma once

#include "CONSTANTES_LITTERALES.h"

#include "Node110.h"
#include "PhysicsSand.h"
#include "PhysicsFireworks.h"
#include "PhysicsExplosion.h"
#include "PhysicsWave.h"
#include "PhysicsHeart.h"
#include "PhysicsWeird.h"
#include "Loader110.h"


class World110 : public Group
{
private:

	//	Constantes & Enumerations	================================================================================================================
	
	ref_ptr<Group> _scenegraph;
	ref_ptr<Node110> _selected;
	ref_ptr<Node> _skybox;
	unsigned int _nbSubdivisions;
	std::string _model;
	ref_ptr<Physics110> _physicsEngine;

	//	Variables membres			================================================================================================================

public:

	//	Constructeurs & Destructeur	================================================================================================================

	World110(void);
	~World110(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	ref_ptr<Group> getScenegraph() {return _scenegraph;}
	ref_ptr<Node110> getSelected() {return _selected;}
	void setSelected(ref_ptr<Node110> s) { _selected = s;}
	void setNbSubdivisions( unsigned int n) { _nbSubdivisions = n;}
	void setModelName(std::string m){_model = m;}

	//	Fonctionnalités				================================================================================================================

	void loadModel();

	void setSandWorld();
	void setFireworksWorld();
	void setExplosionWorld();
	void setWaveWorld();
	void setHeartWorld();
	void setWeirdWorld();

	void setCubeWorld();
};

