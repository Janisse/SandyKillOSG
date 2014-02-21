#include "Viewer110.h"
#include "KeyboardEventhandler.h"

Viewer110::Viewer110(void)
{
	_scenegraph = new Group;
	_selected = 0;

	//création des teneurs d'évéements + affectation des événeemnts sur eux
	_keyboardEventHandler = new KeyboardEventhandler;
	_mouseEventHandler = new MouseEvent;
	addEventHandler(_keyboardEventHandler);
	addEventHandler(_mouseEventHandler);

	//paramétrage de la scène
	setSceneData(_scenegraph);
}


Viewer110::~Viewer110(void)
{
}
