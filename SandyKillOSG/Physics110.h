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
public:
	Physics110(void);
	virtual ~Physics110(void);
	virtual void run(double temps, ref_ptr<Node110> node110) = 0;
};
