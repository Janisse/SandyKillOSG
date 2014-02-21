#pragma once

#include "CONSTANTES_LITTERALES.h"

class APCallback: public AnimationPathCallback
{
protected :
	double _duree_animation; 
	osg::ref_ptr<osg::AnimationPath> _anim_suivante;
	bool _current_anim;

public :
	APCallback( osg::AnimationPath * anim_path_1, 
		osg::AnimationPath * anim_path_2) 
		: osg::AnimationPathCallback(anim_path_1), 
		_duree_animation(anim_path_1->getPeriod()), 
		_anim_suivante(anim_path_2) ,
		_current_anim(false)
	{} 
	// � faire : red�finition de la m�thode op�rator
	virtual void operator() (osg::Node *node, osg::NodeVisitor *nv); 
};
