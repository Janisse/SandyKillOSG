#pragma once

#include <time.h>
#include <windows.h> 
#include <osgViewer/Viewer>
#include <osg/PointSprite>
#include <osg/BlendFunc>
#include <osg/StateAttribute>
#include <osg/Point>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <osg/GLExtensions>
#include <osg/TexEnv>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osg/Node>
#include <RefPtrCo.h>

#include <stdio.h> //pour printf, sscanf, stderr, fprintf, fopen, fseek, fread, ftell, fclose, FILE
#include <stdlib.h>//pour malloc, free
#include <string.h>//pour strstr
#include <conio.h>//pour getch
#include <time.h>

using namespace std;
using namespace osg;
using namespace osgGA;

float TAILLE_SPRITES = 2.f;
double TEMPS = 10;