#pragma once

#include "CONSTANTES_LITTERALES.h"

class MouseEvent : public osgGA::GUIEventHandler
{
private:
	ref_ptr<osg::Node> _picked;
	ref_ptr<osgViewer::Viewer> _viewer;
	bool isDragging;

public:
	MouseEvent(void);

	//Récupération de l'événement, cette focntion appelle les autres méthodes de la classe
	bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);

private :
	//Au clic: récupération du node pointé par le curseur
	osg::NodePath pickCible (osgViewer::Viewer* viewer, float mx, float my);

	//Au clic : Début du drag n' drop
	void dragStart();

	//Au relachement : Fin du drag n' drop
	void dragStop();

	// Déplacement de la souris
	void move();

	ref_ptr<osg::Node> getPicked(){ return _picked; }
};

