#pragma once

#include "Node110.h"

void subdivide(ref_ptr<Node110> node110, int nbSub);
Vec3f middlePoint(Vec3f pt1, Vec3f pt2);
int searchPoint(Vec3 pt, ref_ptr<Node110> node110, int endIndexOldArray);