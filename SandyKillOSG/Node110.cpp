#include "Node110.h"

////////////// CODE A COMMENTER/DECOMMENTER POUR Chargement d'un cube A LA MAIN
Node110::Node110()
{
	_trf = new PositionAttitudeTransform;
	_gde = new Geode;
	_trf->addChild(_gde);
	this->addChild(_trf);
}
///////////////////////////////////////////////////////////////////////

////////////// CODE A COMMENTER/DECOMMENTER POUR Chargement d'un cube AUTOMATIQUE
/*
Node110::Node110(ref_ptr<Geometry> geom)
{
	_trf = new PositionAttitudeTransform;
	_gde = new Geode;
	_geom = geom;
	_gde->addDrawable(_geom);
	_trf->addChild(_gde);
	this->addChild(_trf);
}*/
///////////////////////////////////////////////////////////////////////

Node110::~Node110(void)
{
}

void Node110::event_RotationHaut(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(-1,0,0,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::event_RotationBas(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(1,0,0,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::event_RotationGauche(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(0,0,-1,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

void Node110::event_RotationDroite(bool acceleration)
{
	if (acceleration)
	{
		Quat rot(0,0,1,5);
		_trf->setAttitude(rot * _trf->getAttitude());
	}
}

bool Node110::loadFromFile(const char * path)
{
	//node110->getGeometry() = new Geometry();
	_geom = new Geometry();

	ref_ptr<Vec3Array> vertices = new Vec3Array();
	ref_ptr<Vec3Array> normals = new Vec3Array();
	ref_ptr<Vec3Array> colorVertices = new Vec3Array();
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
			vertices->push_back(Vec3(x, y, z));
			colorVertices->push_back(Vec3f(0.5, 0.5, 0.5));
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
	_geom->setVertexArray(vertices.get());
	_geom->setNormalArray(normals.get());
	_geom->setNormalBinding(Geometry::BIND_PER_VERTEX);
	_geom->setColorArray(colorVertices.get());
	_geom->setColorBinding(Geometry::BIND_PER_VERTEX);
	for (int i=0; i<faces->size(); i++)
	{
		ref_ptr<DrawElementsUInt> face = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
		face->push_back((int)faces->at(i).x());
		face->push_back((int)faces->at(i).y());
		face->push_back((int)faces->at(i).z());

		_geom->addPrimitiveSet(face.get());
	}

	//node110->getGde()->addDrawable(node110.get()->getGeometry());
	_geom->setUseDisplayList(true);
	_gde->addDrawable(_geom->asGeometry());
	return true;
}