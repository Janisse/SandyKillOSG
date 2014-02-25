#include "CONSTANTES_LITTERALES.h"
#include "Subdivisor.h"


void subdivide(ref_ptr<Node110> node110, int nbSub)
{
	for (int k = 0; k<nbSub; k++)
	{
		//Init
		ref_ptr<DrawElementsUInt> face = new DrawElementsUInt(PrimitiveSet::POINTS);

		//Vide les faces de la geometry
		node110->getGeometry()->getPrimitiveSetList().clear();
		ref_ptr<Vec3Array> newFaces = new Vec3Array;

		int endIndexOldArray = node110->getVertexs()->size();

		//On parcourt toutes les faces
		for(int i=0; i<node110->getFaces()->size(); i++)
		{
			//On parcourt les 3 points de la face
			int index1 = node110->getFaces()->at(i).x();
			Vec3 pt1 = node110->getVertexs()->at(index1);
			int index2 = node110->getFaces()->at(i).y();
			Vec3 pt2 = node110->getVertexs()->at(index2);
			int index3 = node110->getFaces()->at(i).z();
			Vec3 pt3 = node110->getVertexs()->at(index3);

			//On crée les 3 nouveaux points
			int index4;
			Vec3 pt4 = middlePoint(pt1, pt2);
			int result4 = searchPoint(pt4, node110, endIndexOldArray);
			if(result4 != -1)
				index4 = result4;
			else
			{
				index4 = node110->getVertexs()->size();
				//On ajoute les nouveaux points a la geometry
				node110->getVertexs()->push_back(pt4);
			}
			int index5;
			Vec3 pt5 = middlePoint(pt2, pt3);
			int result5 = searchPoint(pt5, node110, endIndexOldArray);
			if(result5 != -1)
				index5 = result5;
			else
			{
				index5 = node110->getVertexs()->size();
				//On ajoute les nouveaux points a la geometry
				node110->getVertexs()->push_back(pt5);
			}
			int index6;
			Vec3 pt6 = middlePoint(pt1, pt3);
			int result6 = searchPoint(pt6, node110, endIndexOldArray);
			if(result6 != -1)
				index6 = result6;
			else
			{
				index6 = node110->getVertexs()->size();
				//On ajoute les nouveaux points a la geometry
				node110->getVertexs()->push_back(pt6);
			}

			//On creer les 4 nouvelles faces
			//Face 1 (pt1, pt4, pt6)
			face->push_back(index1);
			face->push_back(index4);
			face->push_back(index6);
			newFaces->push_back(Vec3(index1, index4, index6));

			//Face 2 (pt4, pt2, pt5)
			face->push_back(index4);
			face->push_back(index2);
			face->push_back(index5);
			newFaces->push_back(Vec3(index4, index2, index5));

			//Face 3 (pt4, pt5, pt6)
			face->push_back(index4);
			face->push_back(index5);
			face->push_back(index6);
			newFaces->push_back(Vec3(index4, index5, index6));

			//Face 4 (pt6, pt5, pt3)
			face->push_back(index6);
			face->push_back(index5);
			face->push_back(index3);
			newFaces->push_back(Vec3(index6, index5, index3));
		}

		//On ajoute les faces mises a jour a la geometry
		node110->getGeometry()->addPrimitiveSet(face);
		node110->setFaces(newFaces);

		//Affichage console
		std::cout<<"Subdivision "<<k<<" Fait"<<endl;
		std::cout<<node110->getVertexs()->size()<<endl;
	}
}

Vec3f middlePoint(Vec3f pt1, Vec3f pt2)
{
	return (pt1+pt2)/2.0;
}

int searchPoint(Vec3 pt, ref_ptr<Node110> node110, int endIndexOldArray)
{
	for (int i=endIndexOldArray; i<node110->getVertexs()->size(); i++)
	{
		if(pt.x() != node110->getVertexs()->at(i).x())
			continue;
		if(pt.y() != node110->getVertexs()->at(i).y())
			continue;
		if(pt.z() != node110->getVertexs()->at(i).z())
			continue;
		return i;
	}
	return -1;
}