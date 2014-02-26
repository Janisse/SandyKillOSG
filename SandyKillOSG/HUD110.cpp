#include "HUD110.h"


HUD110::HUD110()
{
}

HUD110::~HUD110(void)
{
}

void HUD110::createLabel()
{
	double size = 20;
	Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
    osgText::Font* font  = osgText::readFontFile("fonts/arial.ttf");

	///////////////////////////// Effet Sable ///////////////////////////////////////////////
	static osg::Vec3 pos(10.0f, 10.0f, 0.0f);
	osgText::Text* labelSableEffect = new osgText::Text();

    labelSableEffect->setFont(font);
    labelSableEffect->setCharacterSize(size);
    labelSableEffect->setFontResolution(size, size);
    labelSableEffect->setColor(color);
    labelSableEffect->setPosition(Vec3(20.0f, 970.0f, 0.0f));

	_tabLabel.push_back(labelSableEffect);

		///////////////////////////// Effet Feu d'artifice ///////////////////////////////////////////////
	osgText::Text* labelFireworksEffect = new osgText::Text();

    labelFireworksEffect->setFont(font);
    labelFireworksEffect->setCharacterSize(size);
    labelFireworksEffect->setFontResolution(size, size);
    labelFireworksEffect->setColor(color);
    labelFireworksEffect->setPosition(Vec3(20.0f, 920.0f, 0.0f));

	_tabLabel.push_back(labelFireworksEffect);
		///////////////////////////// Rejouer l'animation ///////////////////////////////////////////////
	osgText::Text* labelRejouerAnimation = new osgText::Text();

    labelRejouerAnimation->setFont(font);
    labelRejouerAnimation->setCharacterSize(size);
    labelRejouerAnimation->setFontResolution(size, size);
    labelRejouerAnimation->setColor(color);
    labelRejouerAnimation->setPosition(Vec3(20.0f, 50.0f, 0.0f));

	_tabLabel.push_back(labelRejouerAnimation);

		///////////////////////////// Model Cube ///////////////////////////////////////////////
	osgText::Text* labelCube = new osgText::Text();

    labelCube->setFont(font);
    labelCube->setCharacterSize(size);
    labelCube->setFontResolution(size, size);
    labelCube->setColor(color);
    labelCube->setPosition(Vec3(1100.0f, 700.0f, 0.0f));

	_tabLabel.push_back(labelCube);

	///////////////////////////// Model Icosphere ///////////////////////////////////////////////
	osgText::Text* labelIcosphere = new osgText::Text();

    labelIcosphere->setFont(font);
    labelIcosphere->setCharacterSize(size);
    labelIcosphere->setFontResolution(size, size);
    labelIcosphere->setColor(color);
    labelIcosphere->setPosition(Vec3(1100.0f, 600.0f, 0.0f));

	_tabLabel.push_back(labelIcosphere);

		///////////////////////////// Model Suzanne ///////////////////////////////////////////////
	osgText::Text* labelSuzanne = new osgText::Text();

    labelSuzanne->setFont(font);
    labelSuzanne->setCharacterSize(size);
    labelSuzanne->setFontResolution(size, size);
    labelSuzanne->setColor(color);
    labelSuzanne->setPosition(Vec3(1100.0f, 500.0f, 0.0f));

	_tabLabel.push_back(labelSuzanne);

		///////////////////////////// Model Requin ///////////////////////////////////////////////
	osgText::Text* labelRequin = new osgText::Text();

    labelRequin->setFont(font);
    labelRequin->setCharacterSize(size);
    labelRequin->setFontResolution(size, size);
    labelRequin->setColor(color);
    labelRequin->setPosition(Vec3(1100.0f, 400.0f, 0.0f));

	_tabLabel.push_back(labelRequin);

			///////////////////////////// Rotation ///////////////////////////////////////////////
	osgText::Text* labelRotation = new osgText::Text();

    labelRotation->setFont(font);
    labelRotation->setCharacterSize(size);
    labelRotation->setFontResolution(size, size);
    labelRotation->setColor(color);
    labelRotation->setPosition(Vec3(1000.0f, 50.0f, 0.0f));

	_tabLabel.push_back(labelRotation);

    // It seems to be important we do this last to get best results?
	labelSableEffect->setText("a : Effet Sable");
	labelFireworksEffect->setText("z : Effet Feux d'artifice");
    labelRejouerAnimation->setText("r : Rejouer l'animation");
	labelCube->setText("w : Cube");
	labelIcosphere->setText("x : Icosphere");
	labelSuzanne->setText("c : Suzanne");
	labelRequin->setText("v : Requin");
	labelRotation->setText("fleches : Rotation");

}

osg::Camera* HUD110::createOrthoCamera(double width, double height)
{
    osg::Camera* camera = new osg::Camera();

    camera->getOrCreateStateSet()->setMode(
        GL_LIGHTING,
        osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF
    );

    osg::Matrix m = osg::Matrix::ortho2D(0.0f, width, 0.0f, height);

    camera->setProjectionMatrix(m);
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);

    return camera;
}