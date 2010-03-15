#include "GameObjectParticleSystem.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectParticleSystem::GameObjectParticleSystem(const std::string& name)
:GameObject(name)
{

}

GameObjectParticleSystem::~GameObjectParticleSystem()
{

}

RenderComponentParticleSystemPtr GameObjectParticleSystem::getRenderComponentParticleSystem() const
{
	return mRenderComponentParticleSystem;
}

void GameObjectParticleSystem::setRenderComponentParticleSystem(RenderComponentParticleSystemPtr pRenderComponentParticleSystem)
{
	mRenderComponentParticleSystem=pRenderComponentParticleSystem;
}
void GameObjectParticleSystem::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectParticleSystem::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectParticleSystem::changeWorld(int world)
{
	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{
		mRenderComponentParticleSystem->setVisible(true);
	}
	else
	{
		switch(world)
		{
		case DREAMS:
			if(mLogicComponentWorldExistance->getExistsInDreams())
			{
				mRenderComponentParticleSystem->setVisible(true);
			}
			else
			{
				mRenderComponentParticleSystem->setVisible(false);

			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentWorldExistance->getExistsInNightmares())
			{
				mRenderComponentParticleSystem->setVisible(true);
			}
			else
			{
				mRenderComponentParticleSystem->setVisible(false);
			}
			break;
		default:
			break;
		}
	}
}

TGameObjectParticleSystemParameters::TGameObjectParticleSystemParameters() : TGameObjectParameters()
{

}

TGameObjectParticleSystemParameters::~TGameObjectParticleSystemParameters()
{

}