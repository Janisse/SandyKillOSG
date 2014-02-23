#include "CONSTANTES_LITTERALES.h"
#include "Subdivisor.h"


void subdivide(ref_ptr<Node110> node110)
{
	//Init
	ref_ptr<DrawElementsUInt> face = new DrawElementsUInt(PrimitiveSet::POINTS);

	//Vide les faces de la geometry
	node110->getGeometry()->getPrimitiveSetList().clear();
	ref_ptr<Vec3Array> newFaces = new Vec3Array;

	//On parcourt toutes les faces
	for(int i=0; i<node110->getFaces()->size(); i++)
	{
		//On parcourt les 3 points de la face
		Vec3 pt1 = node110->getVertexs()->at(node110->getFaces()->at(i).x());
		Vec3 pt2 = node110->getVertexs()->at(node110->getFaces()->at(i).y());
		Vec3 pt3 = node110->getVertexs()->at(node110->getFaces()->at(i).z());

		//On crée les 3 nouveaux points
		Vec3 pt4 = middlePoint(pt1, pt2);
		Vec3 pt5 = middlePoint(pt2, pt3);
		Vec3 pt6 = middlePoint(pt1, pt3);

		//On ajoute les nouveaux points a la geometry
		node110->getVertexs()->push_back(pt4);
		node110->getVertexs()->push_back(pt5);
		node110->getVertexs()->push_back(pt6);

		//On creer les 4 nouvelles faces
		//Face 1 (pt1, pt4, pt6)
		face->push_back(node110->getFaces()->at(i).x());
		face->push_back(node110->getVertexs()->size()-3);
		face->push_back(node110->getVertexs()->size()-1);
		newFaces->push_back(Vec3(node110->getFaces()->at(i).x(), node110->getVertexs()->size()-3, node110->getVertexs()->size()-1));

		//Face 2 (pt4, pt2, pt5)
		face->push_back(node110->getVertexs()->size()-3);
		face->push_back(node110->getFaces()->at(i).y());
		face->push_back(node110->getVertexs()->size()-2);
		newFaces->push_back(Vec3(node110->getVertexs()->size()-3, node110->getFaces()->at(i).y(), node110->getVertexs()->size()-2));

		//Face 3 (pt4, pt5, pt6)
		face->push_back(node110->getVertexs()->size()-3);
		face->push_back(node110->getVertexs()->size()-2);
		face->push_back(node110->getVertexs()->size()-1);
		newFaces->push_back(Vec3(node110->getVertexs()->size()-3, node110->getVertexs()->size()-2, node110->getVertexs()->size()-1));

		//Face 4 (pt6, pt5, pt3)
		face->push_back(node110->getVertexs()->size()-1);
		face->push_back(node110->getVertexs()->size()-2);
		face->push_back(node110->getFaces()->at(i).z());
		newFaces->push_back(Vec3(node110->getVertexs()->size()-1, node110->getVertexs()->size()-2, node110->getFaces()->at(i).z()));
	}

	//On ajoute les faces mises a jour a la geometry
	node110->getGeometry()->addPrimitiveSet(face);
	node110->setFaces(newFaces);
}

Vec3f middlePoint(Vec3f pt1, Vec3f pt2)
{
	return (pt1+pt2)/2.0;
}