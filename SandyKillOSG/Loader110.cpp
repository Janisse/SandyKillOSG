#include "Loader110.h"


Loader110::Loader110(void)
{
}


Loader110::~Loader110(void)
{
}


bool Loader110::loadFromFile(const char * path, ref_ptr<Node110> node110)
{
	//node110->getGeometry() = new Geometry();
	ref_ptr<Geometry> newGeom = new Geometry();
	//node110->setGeometry(newGeom);
	node110->getGeometry();

	ref_ptr<Vec3Array> vertices = new Vec3Array();
	ref_ptr<Vec3Array> faces = new Vec3Array();

	FILE * file = fopen(path, "r");
	if( file == NULL )
	{
		printf("Impossible to open the file !\n");
		return false;
	}

	//On lit et on charge le fichier
	bool quitLoop = false;
	while( quitLoop == false )
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			quitLoop = true;  // EOF = End Of File. Quit the loop.
			continue;
		}
		// else : parse lineHeader
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			float x;
			float y;
			float z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			Vec3f vertex(x, y, z);
			vertices->push_back(vertex);
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
			faces->push_back(Vec3(vertexIndex[0], vertexIndex[1], vertexIndex[2]));
		}
	}

	//On crée la geometry à partir des données chargées
	newGeom->setVertexArray(vertices);
	for (int i=0; i<faces->size(); i++)
	{
		ref_ptr<DrawElementsUInt> face =
			new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
		face->push_back(faces->at(i).x());
		face->push_back(faces->at(i).y());
		face->push_back(faces->at(i).z());

		newGeom->addPrimitiveSet(face);
	}

	node110->getGde()->addDrawable(newGeom);
	node110->getGde()->addDrawable(node110.get()->getGeometry());
	//return true;
}