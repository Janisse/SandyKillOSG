#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "Node110.h"

class Physics110CallBack : public osg::NodeCallback
{
public:
	Physics110CallBack(void);
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) ;
};

class Physics110
{
private:
	ref_ptr<Physics110CallBack> _update;

protected:
	ref_ptr<Node110> _node110;

public:
	Physics110(void);
	~Physics110(void);
	void startUpdate(ref_ptr<Node110> node110, Vec3 center);
	virtual void update(double time, ref_ptr<Node110> node110) = 0;
};
