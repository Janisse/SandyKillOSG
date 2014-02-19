#include "Picking_Select.h"


Picking_Select::Picking_Select()
{
}

bool Picking_Select::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(GUIEventAdapter::RELEASE):
		{
			osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
			if (!viewer) return false;
			//_picked = pickCible(viewer, ea.getX(), ea.getY());
			return true;
		}
	default:return false;
	}
}

osg::NodePath Picking_Select::pickCible(osgViewer::Viewer* viewer, float mx,float my)
{
	// définir le rayon pour l'intersection
	ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, mx, my);
	// définir le visitor
	osgUtil::IntersectionVisitor visitor_intersections(intersector.get());
	// exécuter le visitor : parcours du graph de scene pour connaître les objets intersectés par le rayon
	viewer->getCamera()->accept(visitor_intersections);
	// on traite les résultats obtenus
	if (intersector->containsIntersections())
	{

		//on prend le premier objet
		osgUtil::LineSegmentIntersector::Intersection intersection = intersector->getFirstIntersection();
		// on récupère le point d'intersection : nécessaire si objet sélectionnéest trés large , donc sa position pas utile
		osg::Vec3d pos_cible = intersection.getWorldIntersectPoint();
		osg::NodePath node_cible = intersection.nodePath;

		return node_cible;
	}
}