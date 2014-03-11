#include "HUD110.h"


HUD110::HUD110(ref_ptr<World110> w)
	: _world(w)
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
	static osg::Vec3 pos(10.0f, 10.0f, 0.0f);

	///////////////////////////// Effet Sable ///////////////////////////////////////////////
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

	///////////////////////////// Effet Explosion ///////////////////////////////////////////////
	osgText::Text* labelExplosionEffect = new osgText::Text();

    labelExplosionEffect->setFont(font);
    labelExplosionEffect->setCharacterSize(size);
    labelExplosionEffect->setFontResolution(size, size);
    labelExplosionEffect->setColor(color);
    labelExplosionEffect->setPosition(Vec3(20.0f, 870.0f, 0.0f));

	_tabLabel.push_back(labelExplosionEffect);

	///////////////////////////// Effet Vague ///////////////////////////////////////////////
	osgText::Text* labelWaveEffect = new osgText::Text();

    labelWaveEffect->setFont(font);
    labelWaveEffect->setCharacterSize(size);
    labelWaveEffect->setFontResolution(size, size);
    labelWaveEffect->setColor(color);
    labelWaveEffect->setPosition(Vec3(20.0f, 820.0f, 0.0f));

	_tabLabel.push_back(labelWaveEffect);

	///////////////////////////// Effet battement coeur ///////////////////////////////////////////////
	osgText::Text* labelHeartEffect = new osgText::Text();

    labelHeartEffect->setFont(font);
    labelHeartEffect->setCharacterSize(size);
    labelHeartEffect->setFontResolution(size, size);
    labelHeartEffect->setColor(color);
    labelHeartEffect->setPosition(Vec3(20.0f, 770.0f, 0.0f));

	_tabLabel.push_back(labelHeartEffect);
	
	///////////////////////////// Effet bizarre ///////////////////////////////////////////////
	osgText::Text* labelWeirdEffect = new osgText::Text();

    labelWeirdEffect->setFont(font);
    labelWeirdEffect->setCharacterSize(size);
    labelWeirdEffect->setFontResolution(size, size);
    labelWeirdEffect->setColor(color);
    labelWeirdEffect->setPosition(Vec3(20.0f, 720.0f, 0.0f));

	_tabLabel.push_back(labelWeirdEffect);

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

	///////////////////////////// Model coeur ///////////////////////////////////////////////
	osgText::Text* labelCoeur = new osgText::Text();

    labelCoeur->setFont(font);
    labelCoeur->setCharacterSize(size);
    labelCoeur->setFontResolution(size, size);
    labelCoeur->setColor(color);
    labelCoeur->setPosition(Vec3(1100.0f, 400.0f, 0.0f));

	_tabLabel.push_back(labelCoeur);

	///////////////////////////// Rotation ///////////////////////////////////////////////
	osgText::Text* labelRotation = new osgText::Text();

    labelRotation->setFont(font);
    labelRotation->setCharacterSize(size);
    labelRotation->setFontResolution(size, size);
    labelRotation->setColor(color);
    labelRotation->setPosition(Vec3(1000.0f, 50.0f, 0.0f));

	_tabLabel.push_back(labelRotation);

	///////////////////////////// Nombre subdivisions ///////////////////////////////////////////////
	labelNbSub = new osgText::Text();

    labelNbSub->setFont(font);
    labelNbSub->setCharacterSize(size);
    labelNbSub->setFontResolution(size, size);
    labelNbSub->setColor(color);
    labelNbSub->setPosition(Vec3(850.0f, 970.0f, 0.0f));

	_tabLabel.push_back(labelNbSub);

		///////////////////////////// Nombre sub OK ///////////////////////////////////////////////
	osgText::Text* labelOK = new osgText::Text();

    labelOK->setFont(font);
    labelOK->setCharacterSize(size);
    labelOK->setFontResolution(size, size);
    labelOK->setColor(color);
    labelOK->setPosition(Vec3(850.0f, 920.0f, 0.0f));

	_tabLabel.push_back(labelOK);

	///////////////////////////// Subdivision in Progress ///////////////////////////////////////////////
	labelSubInProgress = new osgText::Text();

    labelSubInProgress->setFont(font);
    labelSubInProgress->setCharacterSize(size*2);
    labelSubInProgress->setFontResolution(size*2, size*2);
    labelSubInProgress->setColor(color);
    labelSubInProgress->setPosition(Vec3(350.0f, 700.0f, 0.0f));

	_tabLabel.push_back(labelSubInProgress);

	///////////////////////////// Loading ///////////////////////////////////////////////
	labelLoad = new osgText::Text();

    labelLoad->setFont(font);
    labelLoad->setCharacterSize(size*2);
    labelLoad->setFontResolution(size*2, size*2);
    labelLoad->setColor(color);
    labelLoad->setPosition(Vec3(350.0f, 700.0f, 0.0f));

	_tabLabel.push_back(labelLoad);

	///////////////////////////// SelectAPhysic ///////////////////////////////////////////////
	labelselectAPhysic = new osgText::Text();

    labelselectAPhysic->setFont(font);
    labelselectAPhysic->setCharacterSize(size*1.5);
    labelselectAPhysic->setFontResolution(size*1.5, size*1.5);
    labelselectAPhysic->setColor(color);
    labelselectAPhysic->setPosition(Vec3(250.0f, 700.0f, 0.0f));

	_tabLabel.push_back(labelselectAPhysic);

	//Attribution des textes
	labelSableEffect->setText("a : Sable");
	labelFireworksEffect->setText("z : Feux d'artifice");
	labelExplosionEffect->setText("e : Explosion");
	labelWaveEffect->setText("r : Vague");
	labelHeartEffect->setText("t : Battement coeur");
	labelWeirdEffect->setText("y : ???");
    labelRejouerAnimation->setText("espace : Rejouer l'animation");
	labelCube->setText("w : Cube");
	labelIcosphere->setText("x : Icosphere");
	labelSuzanne->setText("c : Suzanne");
	labelCoeur->setText("v : Coeur");
	labelRotation->setText("fleches : Rotation");
	labelSubInProgress->setText("");
	labelLoad->setText("");
	labelselectAPhysic->setText("");

	std::stringstream stream;
	stream<<_world->nbSubdivisions;

	labelNbSub->setText("Nombre de subdivisions +/- : " + stream.str());
	labelOK->setText("Entrer : Subdiviser");

}

void HUD110::update()
{
	std::stringstream stream;
	stream<<_world->nbSubdivisions;
	labelNbSub->setText("Nombre de subdivisions +/- : " + stream.str());
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

void HUD110::subdivisionInProgress(bool inProgress)
{
	if(inProgress)
		labelSubInProgress->setText("Subdivision en cours...");
	else
		labelSubInProgress->setText("");
}

void HUD110::loading(bool load)
{
	if(load)
		labelLoad->setText("Chargement en cours...");
	else
		labelLoad->setText("");
}

void HUD110::selectAPhysic(bool on)
{
	if(on)
		labelselectAPhysic->setText("Veuillez selectionner une physique...");
	else
		labelselectAPhysic->setText("");
}