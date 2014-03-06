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
	
	const unsigned int minSubs, maxSubs;

	//	Variables membres			================================================================================================================

	ref_ptr<Group> _scenegraph;
	ref_ptr<Node110> _selected;
	ref_ptr<Node> _skybox;

	std::string _model;
	ref_ptr<Physics110> _physicsEngine;

public:
		unsigned int nbSubdivisions;

	//	Constructeurs & Destructeur	================================================================================================================

	World110(void);
	~World110(void);

	//	Accesseurs & Mutateurs		================================================================================================================

	ref_ptr<Group> getScenegraph() {return _scenegraph;}
	ref_ptr<Node110> getSelected() {return _selected;}
	void setSelected(ref_ptr<Node110> s) { _selected = s;}
	void setModelName(std::string m){_model = m;}
	ref_ptr<Physics110> getPhysics(){return _physicsEngine;}

	//	Fonctionnalités				================================================================================================================

	void loadModel();
	void resetPhysics();

	void setSandWorld();
	void setFireworksWorld();
	void setExplosionWorld();
	void setWaveWorld();
	void setHeartWorld();
	void setWeirdWorld();

	void subPlus();
	void subMoins();
	void subOK();

};

