#include "Loader110.h"


Loader110::Loader110(void)
{
}


Loader110::~Loader110(void)
{
}


bool Loader110::loadFromFile(const char * path, ref_ptr<Node110>& node110)
{

	node110 = new Node110;
	//node110->getGeometry() = new Geometry();
	ref_ptr<Geometry> newGeom = new Geometry();
	//node110->setGeometry(newGeom);

	ref_ptr<Vec3Array> vertices = new Vec3Array();
	ref_ptr<Vec3Array> faces = new Vec3Array();
	ref_ptr<Vec3Array> normals = new Vec3Array();
	ref_ptr<Vec4Array> colors = new Vec4Array();

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
		// Lecture de la première ligne
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			quitLoop = true; // EOF = End Of File. Quit the loop.
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
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			float x;
			float y;
			float z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			normals->push_back(Vec3f(x, y, z));
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
	node110->getGeometry()->setVertexArray(vertices);
	node110->getGeometry()->setNormalArray(normals);

	Vec4 couleur(1,0,1,1);

	for (int i=0; i<faces->size(); i++)
	{
		ref_ptr<DrawElementsUInt> face =
			new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
		face->push_back(faces->at(i).x());
		face->push_back(faces->at(i).y());
		face->push_back(faces->at(i).z());

		colors->push_back(couleur);

		//newGeom->addPrimitiveSet(face);
		node110->getGeometry()->addPrimitiveSet(face);
	}

	node110->getGeometry()->setColorArray(colors);
	node110->getGeometry()->setColorBinding(Geometry::BIND_PER_PRIMITIVE_SET);
	//node110->getGde()->addDrawable(node110->getGeometry());

	return true;
}