#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "World110.h"

class HUD110
{
private:
	ref_ptr<World110> _world;
	vector<osgText::Text*> _tabLabel;

public:
	HUD110(void);
	~HUD110(void);

	void createLabel();
	osg::Camera* HUD110::createOrthoCamera(double width, double height);

	vector<osgText::Text*> getTabLabel() {return _tabLabel;}
};

