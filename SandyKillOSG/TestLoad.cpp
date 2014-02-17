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
