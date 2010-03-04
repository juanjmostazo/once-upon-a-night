#include "GameObjectParticleSystem.h"

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

void GameObjectParticleSystem::setDreamsMode()
{

}

void GameObjectParticleSystem::setNightmaresMode()
{

}

TGameObjectParticleSystemParameters::TGameObjectParticleSystemParameters() : TGameObjectParameters()
{

}

TGameObjectParticleSystemParameters::~TGameObjectParticleSystemParameters()
{

}