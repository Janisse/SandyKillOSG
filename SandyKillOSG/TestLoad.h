#pragma once
#include "CONSTANTES_LITTERALES.h"

class TestLoad
{
public:
	TestLoad(void);//constructor

	bool loadOBJ(const char * path);

private :
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< Vec3 > temp_vertices;
	std::vector< Vec2 > temp_uvs;
	std::vector< Vec3 > temp_normals;
};