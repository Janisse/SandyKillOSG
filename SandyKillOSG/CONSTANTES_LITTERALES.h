#pragma once

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
#include <osgDB/ReadFile>

#include <stdio.h> //pour printf, sscanf, stderr, fprintf, fopen, fseek, fread, ftell, fclose, FILE
#include <stdlib.h>//pour malloc, free
#include <string.h>//pour strstr
#include <conio.h>//pour getch
#include <time.h>

#include <vector>

using namespace std;
using namespace osg;
using namespace osgGA;

//Initialisation de la fenêtre
const GLushort LARGEUR_FENETRE=400;
const GLushort HAUTEUR_FENETRE=400;
const GLubyte POS_X_ECRAN=200;
const GLubyte POS_Y_ECRAN=200;