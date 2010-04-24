#include "GameObjectPillow.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"

#include "../../Utils/Utils.h"

using namespace OUAN;

GameObjectPillow::GameObjectPillow(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PILLOW)
{

}

GameObjectPillow::~GameObjectPillow()
{

}
/// Set logic component
void GameObjectPillow::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectPillow::getLogicComponent()
{
	return mLogicComponent;
}
RenderComponentEntityPtr GameObjectPillow::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectPillow::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectPillow::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectPillow::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectPillow::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectPillow::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectPillow::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectPillow::getPhysicsComponentSimpleCapsule() const
{
	return mPhysicsComponentSimpleCapsule;
}

void GameObjectPillow::changeWorld(int world)
{
	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
		{
			mPhysicsComponentSimpleCapsule->create();
		}

		mRenderComponentEntity->setVisible(true);
		return;
	}
	else
	{
		switch(world)
		{
			case DREAMS:
				if(mLogicComponent->existsInDreams())
				{
					mRenderComponentEntity->setVisible(true);
					if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->create();
					}
				}
				else
				{
					mRenderComponentEntity->setVisible(false);
					if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->destroy();
					}
				}		
				break;
			case NIGHTMARES:
				if(mLogicComponent->existsInNightmares())
				{
					mRenderComponentEntity->setVisible(true);
					if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->create();
					}
				}
				else
				{
					mRenderComponentEntity->setVisible(false);
					if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->destroy();
					}
				}
				break;
			default:
				break;
		}
	}
}

void GameObjectPillow::reset()
{
	GameObject::reset();
}

bool GameObjectPillow::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectPillow::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectPillow::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectPillow::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleCapsule();
}

void GameObjectPillow::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectPillow::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectPillow::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectPillow::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
void GameObjectPillow::update(double elapsedSeconds)
{

	if (isEnabled()) //there is no point to updating the flashlight when it's not active
	{
		Ogre::Camera * camera;
		CameraManagerPtr cameraManager = getGameWorldManager()->getParent()->getCameraManager();
		Vector3 direction;

		GameObject::update(elapsedSeconds);

		camera=cameraManager->getActiveCamera();

		if(cameraManager->getActiveCameraControllerType()==CAMERA_THIRD_PERSON)
		{
			GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
			Ogre::Vector3 pos;
			Ogre::Quaternion orient;
			if (ony.get() && ony->getRenderComponentEntity()->getEntity()->hasSkeleton()
				&& ony->getRenderComponentEntity()->getEntity()->getSkeleton()->hasBone(ATTACH_BONE_NAME))
			{
				Ogre::Entity* ent = ony->getRenderComponentEntity()->getEntity();
				Ogre::Node* bone = ent->getSkeleton()->getBone(ATTACH_BONE_NAME);
				pos=Utils::getNodeWorldPosition(ent,bone);
				orient=Utils::getNodeWorldOrientation(ent,bone);
			}
			else
			{
				pos=ony->getRenderComponentPositional()->getPosition();
				orient=ony->getRenderComponentPositional()->getOrientation();
			}
			mRenderComponentPositional->setPosition(pos);
			mRenderComponentPositional->setOrientation(orient);

			if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
			{
				//OUCH! BUT FOR THE MOMENT WE LEAVE IT LIKE THIS as there's an error getting the orientation if not done that way
				/*mPhysicsComponentVolumeConvex->destroy();
				mPhysicsComponentVolumeConvex->create();*/

				mPhysicsComponentSimpleCapsule->setPosition(mRenderComponentPositional->getPosition());

				camera=cameraManager->getActiveCamera();
				mPhysicsComponentSimpleCapsule->setOrientation(mRenderComponentPositional->getOrientation());
			}
		}

	}
}
bool GameObjectPillow::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectPillow::getEntityComponent() const
{
	return mRenderComponentEntity;
}
TGameObjectPillowParameters::TGameObjectPillowParameters() : TGameObjectParameters()
{

}

TGameObjectPillowParameters::~TGameObjectPillowParameters()
{

}