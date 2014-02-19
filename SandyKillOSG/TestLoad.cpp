#include "TestLoad.h"


TestLoad::TestLoad(void)
{
}

bool TestLoad::loadOBJ(const char * path, ref_ptr<Geometry> &model)
{
	model = new Geometry;

	temp_vertices = new Vec3Array;
	temp_uvs = new Vec2Array;
	temp_normals = new Vec3Array;

	FILE * file = fopen(path, "r");
	if( file == NULL )
	{
		printf("Impossible to open the file !\n");
		return false;
	}

	while( 1 )
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			return true;  // EOF = End Of File. Quit the loop.
		}

		// else : parse lineHeader
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			float x;
			float y;
			float z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			Vec3f vertex(x, y, z);
			temp_vertices->push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			float x;
			float y;
			fscanf(file, "%f %f\n", &x, &y);
			Vec2 uv(x, y);
			temp_uvs->push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			float x;
			float y;
			float z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			Vec3f normal(x, y, z);
			temp_normals->push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
			if (matches != 6)
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);


			// Modèle chargé
			model->setVertexArray(temp_vertices);
			model->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, temp_vertices->size()));
		}
	}
}

osg::StateSet* TestLoad::makeStateSet(float size)
{
	osg::StateSet *set = new osg::StateSet();

	/// Setup cool blending
	set->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::BlendFunc *fn = new osg::BlendFunc();
	fn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::DST_ALPHA);
	set->setAttributeAndModes(fn, osg::StateAttribute::ON);

	/// Setup the point sprites
	osg::PointSprite *sprite = new osg::PointSprite();
	set->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	/// Give some size to the points to be able to see the sprite
	osg::Point *point = new osg::Point();
	point->setSize(size);
	set->setAttribute(point);

	/// Disable depth test to avoid sort problems and Lighting
	set->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	/// The texture for the sprites
	osg::Texture2D *tex = new osg::Texture2D();
	tex->setImage(osgDB::readImageFile("resources/star.bmp"));
	set->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);
	return set;
}

/*
void TestLoad::parametrerPickMove( Vec3 posDep, Vec3 posArr, double angle, Vec3 axe, AnimationPath::LoopMode repetition)
{

	Vec3d pos = _patDemineur->getPosition();
	Quat orientationDeb= _patDemineur->getAttitude();
	double distance = (posArr-posDep).length();


	//Etape 1 : paramétrage du déplacement
	ref_ptr<AnimationPath> apd = new AnimationPath();
	apd->setLoopMode(repetition);
	AnimationPath::ControlPoint cp0(posDep, orientationDeb*Quat(DegreesToRadians(angle), axe));
	AnimationPath::ControlPoint cp1(posArr, orientationDeb*Quat(DegreesToRadians(angle), axe));
	apd->insert(0 ,cp0);
	apd->insert(moveDuration ,cp1);

	//Etape 2 : paramétrage de la rotation
	ref_ptr<AnimationPath> apr = new AnimationPath();
		// définir l’animation et ses 3 points de contrôle
	apr->setLoopMode(repetition);
	apr->insert(0 ,AnimationPath::ControlPoint(pos,orientationDeb));
	apr->insert(rotationDuration/2,AnimationPath::ControlPoint(pos,orientationDeb*Quat(DegreesToRadians(angle/2), axe)));
	apr->insert(rotationDuration,AnimationPath::ControlPoint(pos,orientationDeb*Quat(DegreesToRadians(angle), axe)));


	// le callback qui va se charger de "jouer" l'animation
	depandrotCallback = new DoubleAnimationPathCallback(apr, apd);
}


void TestLoad::demarerPickMove(bool reinitialiser)
{
	_patDemineur->setUpdateCallback( depandrotCallback.get() );
}


void TestLoad::stopperPickMove()
{
	_patDemineur->removeUpdateCallback(apcAnimationCallBack.get());
}




void TestLoad::rotationAutomatique( ref_ptr<PositionAttitudeTransform> noeud, float angle, Vec3d axe, double duree, AnimationPath::LoopMode repetition)
{
	Vec3d pos = noeud->getPosition();
	Quat orientationDeb= noeud->asPositionAttitudeTransform()->getAttitude();
	// definir l’animation et ses 3 points de contrôle
	ref_ptr<osg::AnimationPath> animationPath(new osg::AnimationPath);
	animationPath->setLoopMode(repetition);
	animationPath->insert(0 ,AnimationPath::ControlPoint(pos,orientationDeb));
	animationPath->insert(duree/2,AnimationPath::ControlPoint(pos,orientationDeb*Quat(DegreesToRadians(angle/2), axe)));
	animationPath->insert(duree,AnimationPath::ControlPoint(pos,orientationDeb*Quat(DegreesToRadians(angle), axe)));
	// Creer le callback
	ref_ptr<AnimationPathCallback> apCallBack = new osg::AnimationPathCallback( animationPath.get() );
	// associer le callback au noeud de transformation
	noeud->setUpdateCallback( apCallBack.get() );
}


void TestLoad::evnmtIHM_Avancer(bool acceleration)
{
	// ...
	if (acceleration) vitesseDeplacementIHM=Vec3f(0.2,0,0);
	else vitesseDeplacementIHM=Vec3f(0,0,0);
}

void TestLoad::evnmtIHM_TournerDroite(bool acceleration)
{
	// ...
	if (acceleration)
		angleRotationIHM = DegreesToRadians(-4.);
	else
		angleRotationIHM = 0.;
}

void TestLoad::evnmtIHM_TournerGauche(bool acceleration)
{
	// ...
	if (acceleration)
		angleRotationIHM = DegreesToRadians(4.);
	else
		angleRotationIHM = 0.;
}

void TestLoad::evnmtIHM_Reculer(bool acceleration)
{
	// ...
	if (acceleration) vitesseDeplacementIHM=Vec3f(-0.2,0,0);
	else vitesseDeplacementIHM=Vec3f(0,0,0);
}

void TestLoad::actualiserPositionIHM()
{
	_patDemineur->setPosition(_patDemineur->getPosition() + _patDemineur->getAttitude()*vitesseDeplacementIHM);
	_patDemineur->setAttitude(_patDemineur->getAttitude() * Quat(angleRotationIHM, Vec3d(0,0,1)));
}
*/