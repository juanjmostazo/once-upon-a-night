#include "GameObjectTerrainTriangle.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrainTriangle::GameObjectTerrainTriangle(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TERRAINTRIANGLE)
{

}

GameObjectTerrainTriangle::~GameObjectTerrainTriangle()
{

}

void GameObjectTerrainTriangle::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectTerrainTriangle::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTerrainTriangle::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTerrainTriangle::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTerrainTriangle::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTerrainTriangle::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTerrainTriangle::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
	mPhysicsComponentComplexTriangle->create();
}

PhysicsComponentComplexTrianglePtr GameObjectTerrainTriangle::getPhysicsComponentComplexTriangle() const
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectTerrainTriangle::createChangeWorldMaterial(std::string cloneName,std::string changeWorldMaterialName,Ogre::TextureUnitState * source,Ogre::TextureUnitState * target)
{
	Ogre::Technique * technique;
	Ogre::MaterialPtr changeworld_clone;
	Ogre::MaterialPtr changeworld_material;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;

	if (!Ogre::MaterialManager::getSingleton().resourceExists(cloneName))
	{
		if (Ogre::MaterialManager::getSingleton().resourceExists(changeWorldMaterialName))
		{
			// Clone the material
			changeworld_material= Ogre::MaterialManager::getSingleton().getByName(changeWorldMaterialName);
			changeworld_clone=changeworld_material->clone(cloneName);

			technique=changeworld_clone->getTechnique(0);
			pass=technique->getPass(0);
			texture=pass->getTextureUnitState(0);
			texture->setTextureName(target->getTextureName());

			pass=technique->getPass(1);
			texture=pass->getTextureUnitState(0);
			texture->setTextureName(source->getTextureName());
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("[RenderComponentEntity] material "+changeWorldMaterialName+" does not exist.");
		}
	}

}

void GameObjectTerrainTriangle::setChangeWorldMaterials(std::string changeWorldMaterialName,RenderComponentEntityPtr source, RenderComponentEntityPtr target)
{
	unsigned int i;
	Ogre::Pass * pass;
	Ogre::Technique * technique;

	Ogre::SubEntity* subEnt;
	Ogre::Entity * pSourceEntity;
	Ogre::Entity * pTargetEntity;
	Ogre::MaterialPtr source_material;
	Ogre::MaterialPtr target_material;
	Ogre::MaterialPtr new_material;
	Ogre::TextureUnitState * source_texture;
	Ogre::TextureUnitState * target_texture;
	Ogre::MaterialPtr changeWorldMaterial;
	std::string materialName;

	//Ogre::LogManager::getSingleton().logMessage("SET MATERIAL "+getName()+" ");

	pSourceEntity=source->getEntity();
	pTargetEntity=target->getEntity();

	mChangeWorldMaterial.clear();

	bool create_material;

	for ( i = 0; (i < pSourceEntity->getNumSubEntities()) &&  (i < pTargetEntity->getNumSubEntities()) ; i++)
	{
		create_material=true;
		// Get source subentity texture
		subEnt = pSourceEntity->getSubEntity(i);
		source_material = subEnt->getMaterial();
		technique = source_material->getBestTechnique();
		pass = technique->getPass(0);
		if(pass->getTextureUnitStateIterator().hasMoreElements())
		{
			source_texture = pass->getTextureUnitState(0);
		}
		else
		{
			create_material=false;
		}

		// Get target subentity texture
		subEnt = pTargetEntity->getSubEntity(i);
		target_material = subEnt->getMaterial();
		technique = target_material->getBestTechnique();
		pass = technique->getPass(0);
		if(pass->getTextureUnitStateIterator().hasMoreElements())
		{
			target_texture = pass->getTextureUnitState(0);
		}
		else
		{
			create_material=false;
		}

		if(create_material)
		{

			std::string new_material_name=changeWorldMaterialName+"#"+source_texture->getTextureName()+"#"+target_texture->getTextureName();

			createChangeWorldMaterial(new_material_name,changeWorldMaterialName,
				source_texture,target_texture);


			new_material=Ogre::MaterialManager::getSingleton().getByName(new_material_name);
			subEnt = pSourceEntity->getSubEntity(i);
			subEnt->setMaterial(new_material);

			subEnt = pTargetEntity->getSubEntity(i);
			subEnt->setMaterial(new_material);

			mChangeWorldMaterial.push_back(new_material->getName());

		}

	}
}

void GameObjectTerrainTriangle::setChangeWorldFactor(double factor)
{
	Ogre::MaterialPtr material;
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;

	unsigned int i;

	//if(getName().compare("terrain#terrain1")==0)
	//{
	//	Ogre::LogManager::getSingleton().logMessage("setChangeWorldFactor "+Ogre::StringConverter::toString(Ogre::Real(factor)));
	//}

	for(i=0;i<mChangeWorldMaterial.size();i++)
	{
		material=Ogre::MaterialManager::getSingleton().getByName(mChangeWorldMaterial[i]);

		technique = material->getBestTechnique();
		pass = technique->getPass(1);
		texture = pass->getTextureUnitState(0);
		texture->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, factor);
	}
}

void GameObjectTerrainTriangle::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			break;
		case NIGHTMARES:

			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			break;
		default:break;
	}

	mRenderComponentEntityDreams->setOriginalMaterial();
	mRenderComponentEntityNightmares->setOriginalMaterial();

	//Ogre::LogManager::getSingleton().logMessage("changeWorldFinished"+getName()+" ");
}

void GameObjectTerrainTriangle::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	setChangeWorldMaterials("blending",mRenderComponentEntityDreams,mRenderComponentEntityNightmares);

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}

	//Ogre::LogManager::getSingleton().logMessage("changeWorldStarted"+getName()+" ");
}

void GameObjectTerrainTriangle::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setChangeWorldFactor(perc);
		break;
	case NIGHTMARES:
		setChangeWorldFactor(1.0f-perc);
		break;
	default:
		break;
	}
}

void GameObjectTerrainTriangle::reset()
{
	GameObject::reset();
}

bool GameObjectTerrainTriangle::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTerrainTriangle::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTerrainTriangle::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTerrainTriangle::getPhysicsComponent() const
{
	return getPhysicsComponentComplexTriangle();
}


/// Set logic component
void GameObjectTerrainTriangle::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTerrainTriangle::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectTerrainTriangle::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectTerrainTriangle::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTerrainTriangle::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTerrainTriangle::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectTerrainTriangle::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTerrainTriangle::getEntityComponent() const
{
	return (mGameWorldManager->getWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
TGameObjectTerrainTriangleParameters::TGameObjectTerrainTriangleParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainTriangleParameters::~TGameObjectTerrainTriangleParameters()
{

}
