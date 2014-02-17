#pragma once
#include "CONSTANTES_LITTERALES.h"

class TestLoad
{
public:
	TestLoad(void);//constructor

	bool loadOBJ(const char * path, ref_ptr<Geometry> &model);
	osg::StateSet* TestLoad::makeStateSet(float size);

private :
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	ref_ptr<Vec3Array> temp_vertices;
	ref_ptr<Vec2Array> temp_uvs;
	ref_ptr<Vec3Array> temp_normals;

};