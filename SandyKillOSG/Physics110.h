#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "Node110.h"

class Physics110;



class Physics110CallBack : public osg::NodeCallback
{
private:
	ref_ptr<Physics110> _phys;
public:
	Physics110CallBack(ref_ptr<Physics110> ph);
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) ;
};


class Physics110
	: public Referenced
{
protected:
	Vec3 _gravity;						//Accélération de gravité
	ref_ptr<Vec3Array> _movement;		//Accélération de mouvement
	ref_ptr<Vec3Array> _projection;		//Accélération initiale
	ref_ptr<Vec3Array> _speed;			//Vitesse

	ref_ptr<Vec3Array> _vertices;		//Points à calculer
	ref_ptr<Vec3Array> _faces;
	unsigned long _nbVertices;
	unsigned long _nbFaces;
	float _speed_attenuation;
	float _mass;

public:
	Physics110(void);
	virtual ~Physics110(void);
	virtual void init(ref_ptr<Node110> node110) = 0;
	virtual void run(double temps) = 0;
	virtual osg::StateSet* makeStateSet();
};
