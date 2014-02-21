#include "APCallback.h"



void APCallback ::operator() ( osg::Node *node, osg::NodeVisitor *nv){ 

	// comportement original du AnimationPathCallback conservé 
	//en appelant la méthode originale (de la classe de base) 
	osg::AnimationPathCallback::operator()(node,nv); 

	// notre comportement particulier de de la classe dérivée commence ici 

	// si pas un visitor UPDATE , alors on ne fait rien ! 
	if ( ! dynamic_cast<osgUtil::UpdateVisitor*> (nv) ) return; 

	// si c'est un UPDATE visitor : 
	// à faire : redéfinition de la méthode opérator
	// si animation 1 terminée => charger et démarrer animation 2 
	// si animation 2 terminée => supprimer le callback du noeud 

	if(getAnimationTime() >= _duree_animation){
		//animation terminée
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
