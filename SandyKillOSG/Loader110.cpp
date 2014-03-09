#include "Loader110.h"


Loader110::Loader110(void)
{
}


Loader110::~Loader110(void)
{
}


bool Loader110::loadFromFile(const char * path, ref_ptr<Node110>& node110)
{
	//Init
	node110 = new Node110();
	ref_ptr<Vec3Array> vertices = node110->getVertexsOriginal();
	ref_ptr<Vec3Array> faces = node110->getFacesOriginal();
	ref_ptr<Vec3Array> facesPoints = node110->getFaces();
	ref_ptr<Vec4Array> colors = node110->getColorsOriginal();
	ref_ptr<Vec4Array> colorsPoints = node110->getColors();


	ref_ptr<DrawElementsUInt> face = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES);

	//On charge les elements du fichier
	FILE * file = fopen(path, "r");
	if( file == NULL )
	{
		printf("Impossible d'ouvrir le fichier!\n");
		return false;
	}

	//On lit et on charge le fichier
	bool quitLoop = false;
	while( quitLoop == false )
	{
		char lineHeader[128];
		// Lecture de la première ligne
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			quitLoop = true; // EOF = End Of File. Quitte la boucle.
			break;
		}
		// else : parse lineHeader
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			float x;
			float y;
			float z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			vertices->push_back(Vec3f(x, y, z));
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
			//On charge la face en cours dans la geometry
			face->push_back(vertexIndex[0]-1);
			face->push_back(vertexIndex[1]-1);
			face->push_back(vertexIndex[2]-1);
			faces->push_back(Vec3(vertexIndex[0]-1, vertexIndex[1]-1, vertexIndex[2]-1));
			facesPoints->push_back(Vec3(vertexIndex[0]-1, vertexIndex[1]-1, vertexIndex[2]-1));
			colors->push_back(Vec4(1.0,1.0,1.0,1.0));
			colorsPoints->push_back(Vec4(1.0,1.0,1.0,1.0));
		}
	}

	//On crée la geometry à partir des données chargées
	node110->getGeometryOriginal()->addPrimitiveSet(face);
	node110->getGeometry()->addPrimitiveSet(face);
	node110->getGeometryOriginal()->setVertexArray(vertices);
	node110->getGeometryOriginal()->setColorArray(colors, osg::Array::BIND_PER_PRIMITIVE_SET);
	node110->getGeometry()->setColorArray(colorsPoints, osg::Array::BIND_PER_PRIMITIVE_SET);

	return true;
}


// à mettre dans les physiques
osg::StateSet* Loader110::makeStateSet()
{
	osg::StateSet *set = new osg::StateSet();

	/// Setup cool blending
	set->setMode(GL_BLEND, osg::StateAttribute::ON);

	/// Setup the point sprites
	osg::PointSprite *sprite = new osg::PointSprite();
	set->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	/// Give some size to the points to be able to see the sprite
	osg::Point *point = new osg::Point();
	point->setSize(TAILLE_SPRITES);
	set->setAttribute(point);

	/// Disable depth test to avoid sort problems and Lighting
	set->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	/// Texture des sprites
	//osg::Texture2D *tex = new osg::Texture2D();
	//tex->setImage(osgDB::readImageFile("resources/star.bmp"));
	//set->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);
	return set;
}