#include "BufferManager.h"
#include "JuliaManager.h"
#include "../../Application.h"
#include "../../Graphics/RenderSubsystem.h"

using namespace OUAN;

BufferManager* BufferManager::mInstance = 0;

BufferManager::BufferManager()
{
	mTexture3DName = "";
	mVCut = 0;
	mVScale = 0;
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

void BufferManager::setBuffer(std::string texture3DName, double vCut, double vScale, double juliaGlobalReal, double juliaGlobalImag, double juliaGlobalTheta)
{
	if (mTexture3DName.compare(texture3DName) != 0 ||
		mVCut != vCut ||
		mVScale != vScale)
	{
		Logger::getInstance()->log("[BUFFER MANAGER] Re-Setting buffer");

		Julia julia = JuliaManager::getInstance()->getJulia(juliaGlobalReal, juliaGlobalImag, juliaGlobalTheta);

		Ogre::TexturePtr texture3D = 
			Application::getInstance()->getRenderSubsystem()->getTexture3D(texture3DName);

		Ogre::HardwarePixelBufferSharedPtr buffer = texture3D->getBuffer(0, 0);

		buffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);

		const Ogre::PixelBox &pb = buffer->getCurrentLock();

		double vCutInv = 1.0f / vCut;

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

						Ogre::PixelUtil::packColour(
							//(float)(tRenderComponentFractalVolumeParameters.colorR < 0 ? x/pb.getWidth() : tRenderComponentFractalVolumeParameters.colorR), 
							//(float)(tRenderComponentFractalVolumeParameters.colorG < 0 ? y/pb.getHeight() : tRenderComponentFractalVolumeParameters.colorG), 
							//(float)(tRenderComponentFractalVolumeParameters.colorB < 0 ? z/pb.getDepth() : tRenderComponentFractalVolumeParameters.colorB), 
							(float)x/pb.getWidth(), 
							(float)y/pb.getHeight(), 
							(float)z/pb.getDepth(),
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

		mTexture3DName = texture3DName;
		mVCut = vCut;
		mVScale = vScale;
	}
}