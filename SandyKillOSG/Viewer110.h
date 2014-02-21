#pragma once

#include "CONSTANTES_LITTERALES.h"
#include "Node110.h"
//#include "KeyboardEventhandler.h"
#include "MouseEvent.h"

class KeyboardEventhandler ;

class Viewer110 : public osgViewer::Viewer
{
private:
	ref_ptr<Group> _scenegraph;

	ref_ptr<Node110> _selected;

	ref_ptr<KeyboardEventhandler> _keyboardEventHandler;
	ref_ptr<MouseEvent> _mouseEventHandler;


public:
	Viewer110(void);
	~Viewer110(void);

	ref_ptr<Node110> getSelected() { return _selected; }
	ref_ptr<Group> getScenegraph() { return _scenegraph; }
};
