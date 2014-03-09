#include "CONSTANTES_LITTERALES.h"
#include "Subdivisor.h"

Subdivisor::Subdivisor(ref_ptr<Node110> in_node110)
{
	node110 = in_node110;
	geomOriginal = node110->getGeometryOriginal();
	vertexsOriginal = node110->getVertexsOriginal();
	facesOriginal = node110->getFacesOriginal();
	geomSub = node110->getGeometrySubSave();
	vertexsSub = node110->getVertexsSubSave();
	facesSub = node110->getFacesSubSave();
}

void Subdivisor::subdivide(int nbSub)
{
	//Variable temps
	Timer time;

	//Init
	ref_ptr<DrawElementsUInt> face = new DrawElementsUInt(PrimitiveSet::POINTS);

	//On copie la geometry original dans geometry subdivisé
	vertexsSub = dynamic_cast<Vec3Array*>(vertexsOriginal->clone(CopyOp(CopyOp::DEEP_COPY_ALL)));
	facesSub = dynamic_cast<Vec3Array*>(facesOriginal->clone(CopyOp(CopyOp::DEEP_COPY_ALL)));
	node110->setVertexsSubSave(vertexsSub);
	geomSub->setPrimitiveSetList(geomOriginal->getPrimitiveSetList());

	for (int k = 0; k<nbSub; k++)
	{
		//Vide les faces de la geometry
		geomSub->getPrimitiveSetList().clear();
		face->clear();
		ref_ptr<Vec3Array> newFaces = new Vec3Array;

		endIndexOldArray = vertexsSub->size();
		endIndexArray = vertexsSub->size();

		//On parcourt toutes les faces
		for(int i=0; i<facesSub->size(); i++)
		{
			//printf("tour %d from thread %d\n", i, omp_get_thread_num());
			//On parcourt les 3 points de la face
			index1 = facesSub->at(i).x();
			pt1 = vertexsSub->at(index1);
			index2 = facesSub->at(i).y();
			pt2 = vertexsSub->at(index2);
			index3 = facesSub->at(i).z();
			pt3 = vertexsSub->at(index3);

			//On crée les 3 nouveaux points

			//Calcul du milieu des points
			pt4 = (pt1+pt2)/2.0;
			pt5 = (pt2+pt3)/2.0;
			pt6 = (pt1+pt3)/2.0;

			//Test si des points sont deja present dans la geometry
			searchPoint();

			//En fonction de vecRes, creation ou non des indexs
			if(index4 == -1)
			{
				index4 = endIndexArray;
				//On ajoute les nouveaux points a la geometry
				vertexsSub->push_back(pt4);
				endIndexArray++;
			}
			
			if(index5 == -1)
			{
				index5 = endIndexArray;
				//On ajoute les nouveaux points a la geometry
				vertexsSub->push_back(pt5);
				endIndexArray++;
			}

			if(index6 == -1)
			{
				index6 = endIndexArray;
				//On ajoute les nouveaux points a la geometry
				vertexsSub->push_back(pt6);
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
		geomSub->addPrimitiveSet(face);
		facesSub = newFaces;
		//node110->setFaces(newFaces);

		//Affichage console
		std::cout<<"Subdivision "<<k+1<<" Fait en "<<time.time_s()<<endl;
		std::cout<<vertexsSub->size()<<endl;
	}

	node110->restoreSubdivision();
}

void Subdivisor::searchPoint()
{
	index4 = -1;
	index5 = -1;
	index6 = -1;

	//Optimisation: Repartition de la recherche sur plusieur processeur
	#pragma omp parallel for
	for (int i=endIndexOldArray; i<vertexsSub->size(); i++)
	{
		Vec3f vecTemp = vertexsSub->at(i);
		//test pt4
		if(pt4 == vecTemp)
			index4 = i;

		//test pt5
		if(pt5 == vecTemp)
			index5 = i;

		//test pt6
		if(pt6 == vecTemp)
			index6 = i;
	}
}