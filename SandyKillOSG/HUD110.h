#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "World110.h"

class HUD110 : public Referenced
{
private:
	ref_ptr<World110> _world;
	vector<osgText::Text*> _tabLabel;

	osgText::Text* labelNbSub;
	osgText::Text* labelSubInProgress;
	osgText::Text* labelLoad;
	osgText::Text* labelselectAPhysic;
	osgText::Text* labelPause;

public:
	HUD110(ref_ptr<World110> w);
	~HUD110(void);

	void createLabel();
	osg::Camera* HUD110::createOrthoCamera(double width, double height);

	vector<osgText::Text*> getTabLabel() {return _tabLabel;}

	void update();
	void subdivisionInProgress(bool inProgress);
	void loading(bool load);
	void selectAPhysic(bool on);
	void updatePause();
	void setColorHud(Vec4 newColor);
};

