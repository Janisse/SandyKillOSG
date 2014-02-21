#include "CONSTANTES_LITTERALES.h"
#include "Subdivisor.h"


void subdivide(ref_ptr<Node110> node110)
{
	ref_ptr<Geometry> node110Geometry = node110->getGeometry();
	ref_ptr<Geode> node110Geode = node110->getGde();
	ref_ptr<Vec3Array> vertexArray = (Vec3Array*)node110Geometry->getVertexArray();
	ref_ptr<osg::PrimitiveSet> nextPrimitiveSet;

	//node110Geometry->getVertexArray()->getNumElements();
	
	//On parcourt toute les faces
	for (int i=0; i<node110Geometry->getNumPrimitiveSets(); i++)
	{
		nextPrimitiveSet = node110Geometry->getPrimitiveSet(i);

		//On parcourt les 3 points de la face
		Vec3 pt1 = vertexArray->at(nextPrimitiveSet->index(0));
		Vec3 pt2 = vertexArray->at(nextPrimitiveSet->index(1));
		Vec3 pt3 = vertexArray->at(nextPrimitiveSet->index(2));

		//On crée les 3 nouveaux points
		Vec3 pt4 = middlePoint(pt1, pt2);
		Vec3 pt5 = middlePoint(pt1, pt3);
		Vec3 pt6 = middlePoint(pt3, pt2);

		//On ajoute les 3 nouveaux points à la geometry
		vertexArray->push_back(pt4);
		vertexArray->push_back(pt5);
		vertexArray->push_back(pt6);

		//On supprime la face actuelle
		node110Geometry->removePrimitiveSet(i);

		//On crée les 4 nouvelles faces
			//face 1 (pt1, pt4, pt6);
		DrawElementsUInt *face1 = new DrawElementsUInt(PrimitiveSet::TRIANGLES);
		face1->push_back(nextPrimitiveSet->index(0));
		face1->push_back(vertexArray->getNumElements()-3);
		face1->push_back(vertexArray->getNumElements()-1);
			//face 2 (pt4, pt2, pt5);
		DrawElementsUInt *face2 = new DrawElementsUInt(PrimitiveSet::TRIANGLES);
		face1->push_back(vertexArray->getNumElements()-3);
		face1->push_back(nextPrimitiveSet->index(1));
		face1->push_back(vertexArray->getNumElements()-2);
			//face 3 (pt4, pt5, pt6);
		DrawElementsUInt *face3 = new DrawElementsUInt(PrimitiveSet::TRIANGLES);
		face1->push_back(vertexArray->getNumElements()-3);
		face1->push_back(vertexArray->getNumElements()-2);
		face1->push_back(vertexArray->getNumElements()-1);
			//face 4 (pt6, pt5, pt3);
		DrawElementsUInt *face4 = new DrawElementsUInt(PrimitiveSet::TRIANGLES);
		face1->push_back(vertexArray->getNumElements()-1);
		face1->push_back(vertexArray->getNumElements()-2);
		face1->push_back(nextPrimitiveSet->index(2));

		//On ajoute les faces à la geometry
		node110Geometry->addPrimitiveSet(face1);
		node110Geometry->addPrimitiveSet(face2);
		node110Geometry->addPrimitiveSet(face3);
		node110Geometry->addPrimitiveSet(face4);

	}
}

Vec3f middlePoint(Vec3f pt1, Vec3f pt2)
{
	return (pt1+pt2)/2.0;
}