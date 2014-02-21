#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "Viewer110.h"

class KeyboardEventhandler : public osgGA::GUIEventHandler
{

private:
	ref_ptr<osg::Node> _picked;
	ref_ptr<Viewer110> _viewer;
	
public:
	KeyboardEventhandler(ref_ptr<Viewer110> v);

	bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);
	osg::NodePath pickCible (osgViewer::Viewer* viewer, float mx,float my);

	ref_ptr<osg::Node> getPicked(){ return _picked;}
};

