#pragma once

#include "Node110.h"

class Subdivisor
{
public:
	void subdivide(int nbSub);
	Subdivisor(ref_ptr<Node110> in_node110);

private:
	void searchPoint();

	int endIndexOldArray;
	int endIndexArray;

	int index1;
	int index2;
	int index3;
	int index4;
	int index5;
	int index6;

	Vec3 pt1;
	Vec3 pt2;
	Vec3 pt3;
	Vec3 pt4;
	Vec3 pt5;
	Vec3 pt6;

	ref_ptr<Node110> node110;
	ref_ptr<Geometry> geomOriginal;
	ref_ptr<Vec3Array> vertexsOriginal;
	ref_ptr<Vec3Array> facesOriginal;
	ref_ptr<Geometry> geomSub;
	ref_ptr<Vec3Array> vertexsSub;
	ref_ptr<Vec3Array> facesSub;
};