#include "GameObjectPlataform.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectPlataform::GameObjectPlataform(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PLATAFORM)
{

}

GameObjectPlataform::~GameObjectPlataform()
{

}

void GameObjectPlataform::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectPlataform::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectPlataform::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectPlataform::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectPlataform::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectPlataform::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectPlataform::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectPlataform::getPhysicsComponentComplexConvex()
{
	return mPhysicsComponentComplexConvex;
}

void GameObjectPlataform::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->destroy();
			}
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->destroy();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}	
		break;
	default:break;
	}
}
//-------------------------------------------------------------------------------------------
TGameObjectPlataformParameters::TGameObjectPlataformParameters() : TGameObjectParameters()
{

}

TGameObjectPlataformParameters::~TGameObjectPlataformParameters()
{

}
