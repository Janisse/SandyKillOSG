#include <windows.h > 
#include <osgViewer/Viewer>

using namespace osg;

int main()
{
	osgViewer::Viewer * viewer = new osgViewer::Viewer; 
	return viewer->run();
} 