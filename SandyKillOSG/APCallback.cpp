#include "APCallback.h"



void APCallback ::operator() ( osg::Node *node, osg::NodeVisitor *nv){ 

	// comportement original du AnimationPathCallback conserv� 
	//en appelant la m�thode originale (de la classe de base) 
	osg::AnimationPathCallback::operator()(node,nv); 

	// notre comportement particulier de de la classe d�riv�e commence ici 

	// si pas un visitor UPDATE , alors on ne fait rien ! 
	if ( ! dynamic_cast<osgUtil::UpdateVisitor*> (nv) ) return; 

	// si c'est un UPDATE visitor : 
	// � faire : red�finition de la m�thode op�rator
	// si animation 1 termin�e => charger et d�marrer animation 2 
	// si animation 2 termin�e => supprimer le callback du noeud 

	if(getAnimationTime() >= _duree_animation){
		//animation termin�e
		if(!_current_anim){
			_animationPath = _anim_suivante;
			_duree_animation = _animationPath->getPeriod();
			_current_anim = true;
			reset();
		}
		else{
			node->removeUpdateCallback(this);
		}
	}
} 
