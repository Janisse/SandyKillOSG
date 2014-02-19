#pragma once
#include "CONSTANTES_LITTERALES.h"

class TestLoad
{
private :
	//offset deplacement
	Vec3f offsetDeplacement;

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	ref_ptr<Vec3Array> temp_vertices;
	ref_ptr<Vec2Array> temp_uvs;
	ref_ptr<Vec3Array> temp_normals;

	//Anim paths
	ref_ptr<AnimationPath> pthDeplacement;

public:
	TestLoad(void);//constructeur

	bool loadOBJ(const char * path, ref_ptr<Geometry> &model);
	osg::StateSet* TestLoad::makeStateSet(float size);

	void parametrerPickMove(Vec3 posDep, Vec3 posArr, double angle, Vec3 axe, AnimationPath::LoopMode repetition = AnimationPath::NO_LOOPING); 
	void demarerPickMove(bool reinitialiser = FALSE); 
	void stopperPickMove();
	
	Vec3f getMoveOffset(){return offsetDeplacement;}
	ref_ptr<AnimationPath> getPthDeplacement() {return pthDeplacement;}

	void evnmtIHM_Avancer(bool acceleration);
	void evnmtIHM_TournerDroite(bool acceleration);
	void evnmtIHM_TournerGauche(bool acceleration);
	void evnmtIHM_Reculer(bool acceleration);

	void actualiserPositionIHM();
	
};