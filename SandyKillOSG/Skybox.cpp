#include "Skybox.h"


SkyBox::SkyBox()
{
	//SkyBox::readCubeMap();
}
SkyBox::~SkyBox()
{

}


osg::TextureCubeMap* SkyBox::readCubeMap()
{
	osg::TextureCubeMap* cubemap = new osg::TextureCubeMap;
	//#define CUBEMAP_FILENAME(face) "nvlobby_" #face ".png"
	//#define CUBEMAP_FILENAME(face) "Cubemap_axis/" #face ".png"
//#define CUBEMAP_FILENAME(face) "CubemapFireworks/" #face ".bmp"
#define CUBEMAP_FILENAME(face) "CubemapSand/" #face ".bmp"
	try{
		osg::Image* imagePosX = osgDB::readImageFile(CUBEMAP_FILENAME(posx));
		osg::Image* imageNegX = osgDB::readImageFile(CUBEMAP_FILENAME(negx));
		osg::Image* imagePosY = osgDB::readImageFile(CUBEMAP_FILENAME(posy));
		osg::Image* imageNegY = osgDB::readImageFile(CUBEMAP_FILENAME(negy));
		osg::Image* imagePosZ = osgDB::readImageFile(CUBEMAP_FILENAME(posz));
		osg::Image* imageNegZ = osgDB::readImageFile(CUBEMAP_FILENAME(negz));

		if (imagePosX && imageNegX && imagePosY && imageNegY && imagePosZ && imageNegZ)
		{
			cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imagePosX);
			cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imageNegX);
			cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imagePosY);
			cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imageNegY);
			cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imagePosZ);
			cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imageNegZ);

			cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
			cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
			cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

			cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
			cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
		}
		//std::cout << "CubeMap ok." << std::endl;
		printf("Cube map ok\n");
	}
	catch(std::exception & e)
	{
		printf("%s",e.what());//std::cout << "Erreur cubeMap.(" << e.what() << ")" << std::endl; 
	}
	return cubemap;
}


// Update texture matrix for cubemaps
struct TexMatCallback : public osg::NodeCallback
{
public:

	TexMatCallback(osg::TexMat& tm) :
	  _texMat(tm)
	  {
	  }

	  virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	  {
		  osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		  if (cv)
		  {
			  const ref_ptr<osg::RefMatrix> MV = cv->getModelViewMatrix();
			  const osg::Matrix R = osg::Matrix::rotate( osg::DegreesToRadians(112.0f), 0.0f,0.0f,1.0f)*
				  osg::Matrix::rotate( osg::DegreesToRadians(90.0f), 1.0f,0.0f,0.0f);
			  
			  osg::Quat q = MV->getRotate();
			  const osg::Matrix C = osg::Matrix::rotate( q.inverse() );

			  _texMat.setMatrix( C*R );
		  }

		  traverse(node,nv);
	  }

	  osg::TexMat& _texMat;
};

class MoveEarthySkyWithEyePointTransform : public osg::Transform
{
public:
	virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix,osg::NodeVisitor* nv) const 
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			osg::Vec3 eyePointLocal = cv->getEyeLocal();
			matrix.preMult(osg::Matrix::translate(eyePointLocal));
		}
		return true;
	}

	virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix,osg::NodeVisitor* nv) const
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			osg::Vec3 eyePointLocal = cv->getEyeLocal();
			matrix.postMult(osg::Matrix::translate(-eyePointLocal));
		}
		return true;
	}
};


osg::Node* SkyBox::createSkyBox()
{

	osg::StateSet* stateset = new osg::StateSet();

	osg::TexEnv* te = new osg::TexEnv;
	te->setMode(osg::TexEnv::REPLACE);
	stateset->setTextureAttributeAndModes(0, te, osg::StateAttribute::ON);

	osg::TexGen *tg = new osg::TexGen;
	tg->setMode(osg::TexGen::NORMAL_MAP);
	stateset->setTextureAttributeAndModes(0, tg, osg::StateAttribute::ON);

	osg::TexMat *tm = new osg::TexMat;
	stateset->setTextureAttribute(0, tm);

	osg::TextureCubeMap* skymap = readCubeMap();
	stateset->setTextureAttributeAndModes(0, skymap, osg::StateAttribute::ON);

	stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	stateset->setMode( GL_CULL_FACE, osg::StateAttribute::OFF );

	// clear the depth to the far plane.
	osg::Depth* depth = new osg::Depth;
	depth->setFunction(osg::Depth::ALWAYS);
	depth->setRange(1.0,1.0);   
	stateset->setAttributeAndModes(depth, osg::StateAttribute::ON );

	stateset->setRenderBinDetails(6,"RenderBin");

	osg::Drawable* drawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),5));

	osg::Geode* geode = new osg::Geode;
	geode->setCullingActive(false);
	geode->setStateSet( stateset );
	geode->addDrawable(drawable);


	osg::Transform* transform = new MoveEarthySkyWithEyePointTransform;
	transform->setCullingActive(false);
	transform->addChild(geode);

	osg::ClearNode* clearNode = new osg::ClearNode;
	//  clearNode->setRequiresClear(false);
	clearNode->setCullCallback(new TexMatCallback(*tm));
	clearNode->addChild(transform);

	return clearNode;
}
