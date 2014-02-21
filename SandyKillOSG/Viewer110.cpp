#include "Viewer110.h"
#include "KeyboardEventhandler.h"

Viewer110::Viewer110(void)
{
	_scenegraph = new Group;
	_selected = 0;

	//cr�ation des teneurs d'�v�ements + affectation des �v�neemnts sur eux
	_keyboardEventHandler = new KeyboardEventhandler;
	_mouseEventHandler = new MouseEvent;
	addEventHandler(_keyboardEventHandler);
	addEventHandler(_mouseEventHandler);

	//param�trage de la sc�ne
	setSceneData(_scenegraph);
}


Viewer110::~Viewer110(void)
{
}
