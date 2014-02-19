#pragma once

#include "CONSTANTES_LITTERALES.h"

class KeyboardEventhandler : public osgGA::GUIEventHandler
{

private:
	ref_ptr<osg::Node> _picked;

public:
	KeyboardEventhandler(void);

	bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);
	osg::NodePath pickCible (osgViewer::Viewer* viewer, float mx,float my);

	ref_ptr<osg::Node> getPicked(){ return _picked;}
};

