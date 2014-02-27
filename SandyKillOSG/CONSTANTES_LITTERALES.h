#pragma once

#include <stdio.h> //pour printf, sscanf, stderr, fprintf, fopen, fseek, fread, ftell, fclose, FILE
#include <stdlib.h>//pour malloc, free
#include <string.h>//pour strstr
#include <conio.h>//pour getch
#include <time.h>
#include <windows.h> 
#include <RefPtrCo.h>
#include <sstream>
#include <iostream>
#include <omp.h>
#include <list>

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
#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/NodeCallback>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Transform>
#include <osg/Material>
#include <osg/Depth>
#include <osg/CullFace>
#include <osg/TexMat>
#include <osg/TexGen>
#include <osg/TexEnvCombine>
#include <osg/TextureCubeMap>
#include <osg/VertexProgram>
#include <osg/Projection>
#include <osg/MatrixTransform>

#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Optimizer>
#include <osgUtil/CullVisitor>

#include <osgText/Text>

using namespace std;
using namespace osg;
using namespace osgGA;

#define TAILLE_SPRITES 2.0
#define TEMPS 10
#define HAUTEUR_SOL -2.0