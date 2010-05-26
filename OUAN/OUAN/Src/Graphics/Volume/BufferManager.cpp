#include "BufferManager.h"
#include "JuliaManager.h"
#include "../../Application.h"
#include "../../Graphics/RenderSubsystem.h"

using namespace OUAN;

BufferManager* BufferManager::mInstance = 0;

BufferManager::BufferManager()
{
	mTexture3DName_1 = "";
	mTexture3DName_2 = "";
}

BufferManager::~BufferManager()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = 0;
	}
}

BufferManager* BufferManager::getInstance()
{
	if (!mInstance)
	{
		mInstance = new BufferManager();
	}

	return mInstance;
}

//TODO IMPROVE TEXTURES USING A POOL
void BufferManager::setBuffer(std::string texture3DName, double vCut, double vScale, 
							  double juliaGlobalReal, double juliaGlobalImag, double juliaGlobalTheta,
							  double initColorR, double initColorG, double initColorB,
							  double endColorR, double endColorG, double endColorB)
{
	if (mTexture3DName_1.compare(texture3DName) == 0 || 
		mTexture3DName_2.compare(texture3DName) == 0)
	{
		//DO NOTHING
	}
	else
	{
		Logger::getInstance()->log("[BUFFER MANAGER] Setting buffer for " + texture3DName);
		Logger::getInstance()->log("COLOR INIT: " + Ogre::StringConverter::toString(Ogre::Real(initColorR)) + "," + Ogre::StringConverter::toString(Ogre::Real(initColorG)) + "," + Ogre::StringConverter::toString(Ogre::Real(initColorB)));
		Logger::getInstance()->log("COLOR END: " + Ogre::StringConverter::toString(Ogre::Real(endColorR)) + "," + Ogre::StringConverter::toString(Ogre::Real(endColorG)) + "," + Ogre::StringConverter::toString(Ogre::Real(endColorB)));

		Julia julia = JuliaManager::getInstance()->getJulia(juliaGlobalReal, juliaGlobalImag, juliaGlobalTheta);

		Ogre::TexturePtr texture3D = 
			Application::getInstance()->getRenderSubsystem()->getTexture3D(texture3DName);

		Ogre::HardwarePixelBufferSharedPtr buffer = texture3D->getBuffer(0, 0);

		buffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);

		const Ogre::PixelBox &pb = buffer->getCurrentLock();

		double vCutInv = 1.0f / vCut;
		float colorR, colorG, colorB;

		unsigned int* pbptr = static_cast<unsigned int*>(pb.data);
		for(size_t z=pb.front; z<pb.back; z++) 
		{
			for(size_t y=pb.top; y<pb.bottom; y++)
			{
				for(size_t x=pb.left; x<pb.right; x++)
				{
					if(z==pb.front || z==(pb.back-1) || y==pb.top|| y==(pb.bottom-1) || x==pb.left || x==(pb.right-1))
					{
						pbptr[x] = 0; // On border, must be zero
					} 
					else
					{
						float val = julia.eval(
							((float)x/pb.getWidth()-0.5f) * vScale, 
							((float)y/pb.getHeight()-0.5f) * vScale, 
							((float)z/pb.getDepth()-0.5f) * vScale);

						if(val > vCut)
						{
							val = vCut;
						}

						colorR = (float)x/pb.getWidth();
						colorG = (float)y/pb.getHeight();
						colorB = (float)z/pb.getDepth();
						
						colorR = ((endColorR - initColorR) * colorR) + initColorR;
						colorG = ((endColorG - initColorG) * colorG) + initColorG;
						colorB = ((endColorB - initColorB) * colorB) + initColorB;

						//Logger::getInstance()->log(Ogre::StringConverter::toString(Ogre::Real(x)) + "," + Ogre::StringConverter::toString(Ogre::Real(y)) + "," + Ogre::StringConverter::toString(Ogre::Real(z)) + " : " + Ogre::StringConverter::toString(Ogre::Real(colorR)) + "," + Ogre::StringConverter::toString(Ogre::Real(colorG)) + "," + Ogre::StringConverter::toString(Ogre::Real(colorB)));

						Ogre::PixelUtil::packColour(
							colorR, 
							colorG, 
							colorB,
							(1.0f-(val*vCutInv))*0.7f, 
							Ogre::PF_A8R8G8B8, 
							&pbptr[x]);
					}	
				}

				pbptr += pb.rowPitch;
			}

			pbptr += pb.getSliceSkip();
		}

		buffer->unlock();

		if (texture3DName.find("texture3D_1") != std::string::npos)
		{
			mTexture3DName_1 = texture3DName;
		}
		else if (texture3DName.find("texture3D_2") != std::string::npos)
		{
			mTexture3DName_2 = texture3DName;
		}
	}
}