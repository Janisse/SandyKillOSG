#include "CONSTANTES_LITTERALES.h"
#include "Subdivisor.h"

Subdivisor::Subdivisor(ref_ptr<Node110> in_node110)
{
	node110 = in_node110;
	geom = node110->getGeometry();
	vertexs = node110->getVertexs();
	faces = node110->getFaces();
}

void Subdivisor::subdivide(int nbSub)
{
	//Variable temps
	Timer time;
	for (int k = 0; k<nbSub; k++)
	{
		//Init
		ref_ptr<DrawElementsUInt> face = new DrawElementsUInt(PrimitiveSet::POINTS);

		//Vide les faces de la geometry
		geom->getPrimitiveSetList().clear();
		ref_ptr<Vec3Array> newFaces = new Vec3Array;

		endIndexOldArray = vertexs->size();
		endIndexArray = vertexs->size();

		//On parcourt toutes les faces
		for(int i=0; i<faces->size(); i++)
		{
			//printf("tour %d from thread %d\n", i, omp_get_thread_num());
			//On parcourt les 3 points de la face
			index1 = faces->at(i).x();
			pt1 = vertexs->at(index1);
			index2 = faces->at(i).y();
			pt2 = vertexs->at(index2);
			index3 = faces->at(i).z();
			pt3 = vertexs->at(index3);

			//On cr�e les 3 nouveaux points

			//Calcul du milieu des points
			pt4 = middlePoint(pt1, pt2);
			pt5 = middlePoint(pt2, pt3);
			pt6 = middlePoint(pt1, pt3);

			//Test si des points sont deja present dans la geometry
			searchPoint();

			//En fonction de vecRes, creation ou non des indexs
			if(index4 == -1)
			{
				index4 = endIndexArray;
				//On ajoute les nouveaux points a la geometry
				vertexs->push_back(pt4);
				endIndexArray++;
			}
			
			if(index5 == -1)
			{
				index5 = endIndexArray;
				//On ajoute les nouveaux points a la geometry
				vertexs->push_back(pt5);
				endIndexArray++;
			}

			if(index6 == -1)
			{
				index6 = endIndexArray;
				//On ajoute les nouveaux points a la geometry
				vertexs->push_back(pt6);
				endIndexArray++;
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
		geom->addPrimitiveSet(face);
		faces = newFaces;
		//node110->setFaces(newFaces);

		//Affichage console
		std::cout<<"Subdivision "<<k+1<<" Fait en "<<time.time_s()<<endl;
		std::cout<<vertexs->size()<<endl;
	}
}

Vec3f Subdivisor::middlePoint(Vec3f in_pt1, Vec3f in_pt2)
{
	return (in_pt1+in_pt2)/2.0;
}

void Subdivisor::searchPoint()
{
	index4 = -1;
	index5 = -1;
	index6 = -1;

	//Optimisation: Repartition de la recherche sur plusieur processeur
	#pragma omp parallel for schedule(dynamic)
	for (int i=endIndexOldArray; i<vertexs->size(); i++)
	{
		Vec3f vecTemp = vertexs->at(i);
		//test pt4
		if(pt4.x() == vecTemp.x())
			if(pt4.y() == vecTemp.y())	
				if(pt4.z() == vecTemp.z())
				{
					index4 = i;
				}

		//test pt5
		if(pt5.x() == vecTemp.x())
			if(pt5.y() == vecTemp.y())	
				if(pt5.z() == vecTemp.z())
				{
					index5 = i;
				}

		//test pt6
		if(pt6.x() == vecTemp.x())
			if(pt6.y() == vecTemp.y())	
				if(pt6.z() == vecTemp.z())
				{
					index6 = i;
				}
	}
}