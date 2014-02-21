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

	//R�cup�ration de l'�v�nement, cette focntion appelle les autres m�thodes de la classe
	bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);

private :
	//Au clic: r�cup�ration du node point� par le curseur
	osg::NodePath pickCible (osgViewer::Viewer* viewer, float mx, float my);

	//Au clic : D�but du drag n' drop
	void dragStart();

	//Au relachement : Fin du drag n' drop
	void dragStop();

	// D�placement de la souris
	void move();

	ref_ptr<osg::Node> getPicked(){ return _picked; }
};

