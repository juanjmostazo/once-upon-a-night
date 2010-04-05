#include "PhysicsSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectTerrainConvex.h"
#include "../Game/GameObject/GameObjectTerrainTriangle.h"
#include "../Game/GameObject/GameObjectLight.h"
#include "../Game/GameObject/GameObjectBillboardSet.h"
#include "../Game/GameObject/GameObjectParticleSystem.h"
#include "../Game/GameObject/GameObjectScene.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Game/GameObject/GameObjectTripollito.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectTentetieso.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Game/GameObject/GameObjectCamera.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectHeart.h"
#include "../Game/GameObject/GameObjectDiamond.h"
#include "../Game/GameObject/GameObjectClockPiece.h"
#include "../Game/GameObject/GameObjectStoryBook.h"
#include "../Game/GameObject/GameObjectScaredPlant.h"
#include "../Game/GameObject/GameObjectTree.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Event/Event.h"
#include "PhysicsComponent/PhysicsComponent.h"
#include "PhysicsComponent/PhysicsComponentCharacter.h"
#include "PhysicsComponent/PhysicsComponentComplex.h"
#include "PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "PhysicsComponent/PhysicsComponentSimple.h"
#include "PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "PhysicsComponent/PhysicsComponentVolumeBox.h"

using namespace OUAN;

PhysicsSubsystem::PhysicsSubsystem()
{
	mNxOgreWorld = NULL;
	mNxOgreScene = NULL;
	mNxOgreRenderSystem = NULL;
	mNxOgreTimeController = NULL;
	mNxOgreControllerManager = NULL;
}

PhysicsSubsystem::~PhysicsSubsystem()
{

}

void PhysicsSubsystem::init(ApplicationPtr app,OUAN::ConfigurationPtr config)
{
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL INIT STARTED]");

	loadConfig();

	mApp=app;
	mConfig=config;

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL INIT FINISHED]");
}

void PhysicsSubsystem::cleanUp()
{
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL CLEANUP STARTED]");

	clear();

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL CLEANUP FINISHED]");
}

void PhysicsSubsystem::initLevel(std::string sceneName)
{	
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL INIT STARTED]");

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating NxOgre::World");
	mNxOgreWorld = NxOgre::World::createWorld();

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Loading nxs resources");
	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Setting up scene description");
	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = mGravity;
	sceneDesc.mName = NxOgre::String(sceneName.c_str());

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating scene");
	mNxOgreScene = mNxOgreWorld->createScene(sceneDesc);
	
	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating render system");
	mNxOgreRenderSystem = new OGRE3DRenderSystem(mNxOgreScene);

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating time controller");
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating controller manager");
	mNxOgreControllerManager = new NxOgre::ControllerManager();

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Setting up scene");
	mNxOgreScene->getMaterial(0)->setStaticFriction(mStaticFriction);
	mNxOgreScene->getMaterial(0)->setDynamicFriction(mDynamicFriction);
	mNxOgreScene->getMaterial(0)->setRestitution(mRestitution);

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating visual debugger");
	mApp->getRenderSubsystem()->createVisualDebugger(mConfig);
	
	//Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating debug floor");
	//NxOgre::PlaneGeometry* pDebugPlane = new NxOgre::PlaneGeometry(0, NxOgre::Vec3(0, 1, 0));
	//pDebugPlane->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
	//mNxOgreScene->createSceneGeometry(pDebugPlane, Matrix44_Identity);
	//mApp->getRenderSubsystem()->createDebugFloor(mConfig);

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL INIT FINISHED]");
}

void PhysicsSubsystem::clear()
{
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL CLEAR STARTED]");

	//We destroy the scene, is this needed?
	// TODO: Iterate over 
	// Application::getInstance()->getGameWorldManager()->getGameObjectPhysicsContainer() 
	// and call destroy() method

	if (mNxOgreControllerManager)
	{
		Ogre::LogManager::getSingleton().logMessage("PHYSICS: destroying controller manager");
		delete mNxOgreControllerManager;
		mNxOgreControllerManager=0;
	}

	if (mNxOgreRenderSystem)
	{
		Ogre::LogManager::getSingleton().logMessage("PHYSICS: render system");
		delete mNxOgreRenderSystem;
		mNxOgreRenderSystem=0;
	}
	
	//Visual Debugger should be destroyed?
	//mApp->getRenderSubsystem()->

	if (mNxOgreWorld)
	{
		if (mNxOgreScene)
		{
			Ogre::LogManager::getSingleton().logMessage("PHYSICS: destroying scene");
			mNxOgreWorld->destroyScene(mNxOgreScene);
			mNxOgreScene=0;
		}

		Ogre::LogManager::getSingleton().logMessage("PHYSICS: destroying world");
		mNxOgreWorld->destroyWorld();
		mNxOgreWorld=0;
	}

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL CLEAR FINISHED]");
}

void PhysicsSubsystem::update(double elapsedSeconds)
{
	/*
	std::stringstream out;
	out << elapsedSeconds;
	std::string elapsedTime = out.str();
	Ogre::LogManager::getSingleton().logMessage("Advancing " + elapsedTime + " seconds");
	*/
	mNxOgreTimeController->advance(elapsedSeconds);
}

bool PhysicsSubsystem::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(PHYSICS_CFG))
	{
		double gravityX, gravityY, gravityZ;

		config.getOption("GRAVITY_X", value); 
		gravityX = atof(value.c_str());

		config.getOption("GRAVITY_Y", value); 
		gravityY = atof(value.c_str());

		config.getOption("GRAVITY_Z", value); 
		gravityZ = atof(value.c_str());

		mGravity = NxOgre::Vec3(gravityX, gravityY, gravityZ);

		config.getOption("STATIC_FRICTION", value); 
		mStaticFriction = atof(value.c_str());

		config.getOption("DYNAMIC_FRICTION", value); 
		mDynamicFriction = atof(value.c_str());

		config.getOption("RESTITUTION", value); 
		mRestitution = atof(value.c_str());

		config.getOption("DISPLACEMENT_SCALE", value); 
		mDisplacementScale = atof(value.c_str());

		config.getOption("MIN_DISTANCE", value); 
		mMinDistance = atof(value.c_str());

		config.getOption("MOVEMENT_UNITS_PER_SECOND", value); 
		mMovementUnitsPerSecond = atof(value.c_str());

		config.getOption("MOVEMENT_LIMIT_UNITS_PER_SECOND", value); 
		mMovementLimitUnitsPerSecond = atof(value.c_str());

		config.getOption("TURN_DEGREES_PER_SECOND", value); 
		mTurnDegreesPerSecond = atof(value.c_str());

		config.getOption("INITIAL_JUMP_SPEED", value); 
		mInitialJumpSpeed = atof(value.c_str());

		config.getOption("MIN_ALLOWED_Y", value); 
		mMinAllowedY = atof(value.c_str());

		config.getOption("MIN_COLLISION_ANGLE", value); 
		mMinCollisionAngle = atof(value.c_str());

		config.getOption("MIN_SLIDING_ANGLE", value); 
		mMinSlidingAngle = atof(value.c_str());

		config.getOption("MIN_SLIDING_ANGLE_FALL", value); 
		mMinSlidingAngleFall = atof(value.c_str());

		config.getOption("SLIDING_FACTOR", value); 
		mSlidingFactor = atof(value.c_str());

		config.getOption("SLIDING_FACTOR_FALL", value); 
		mSlidingFactorFall = atof(value.c_str());

		success = true;
	} 
	else 
	{
		//Ogre::LogManager::getSingleton().logMessage(PHYSICS_CFG + " COULD NOT BE LOADED!");

		mGravity = NxOgre::Vec3(0,0,0);
		mStaticFriction = 0;
		mDynamicFriction = 0;
		mRestitution = 0;
		mDisplacementScale = 0;
		mMinDistance = 0;
		mMovementUnitsPerSecond = 0;
		mTurnDegreesPerSecond = 0;
		mInitialJumpSpeed = 0;
		mMinAllowedY = 0;
		mMinSlidingAngle = 0;
		mMinSlidingAngleFall = 0;
		mMinCollisionAngle = 0;
		mSlidingFactor = 0;
		mSlidingFactorFall = 0;

		success = false;
	}

	//	config.~Configuration();
	return success;
}

NxOgre::World* PhysicsSubsystem::getNxOgreWorld()
{
	return mNxOgreWorld;
}

NxOgre::Scene* PhysicsSubsystem::getNxOgreScene()
{
	return mNxOgreScene;
}

OGRE3DRenderSystem* PhysicsSubsystem::getNxOgreRenderSystem()
{
	return mNxOgreRenderSystem;
}

NxOgre::TimeController* PhysicsSubsystem::getNxOgreTimeController()
{
	return mNxOgreTimeController;
}

NxOgre::ControllerManager* PhysicsSubsystem::getNxOgreControllerManager()
{
	return mNxOgreControllerManager;	
}

//////////////////////////////////////////////////////////////////
// General physics callbacks

bool PhysicsSubsystem::onHitEvent(const NxOgre::RaycastHit& raycastHit)
{
	Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onHitEvent called!");
	return true;
}

void PhysicsSubsystem::onContact(const NxOgre::ContactPair& contactPair)
{
	Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onContact called!");
}

//////////////////////////////////////////////////////////////////
// Character physics callbacks

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	double normalAngle = acos(hit.mWorldNormal.y) * TO_DEGREES;
	setGameObjectSlidingFromController(hit.mController, hit.mWorldNormal, normalAngle);

	if (normalAngle > mMinCollisionAngle)
	{
		GameObjectPtr object1 = getGameObjectFromController(hit.mController);
		GameObjectPtr object2 = getGameObjectFromShape(hit.mShape);

		if (isAllowedCollision(object1, object2))
		{
			CharacterShapeFrontCollisionEventPtr evt = CharacterShapeFrontCollisionEventPtr(
				new CharacterShapeFrontCollisionEvent(object1,object2));

			mApp->getGameWorldManager()->addEvent(evt);
		}
	}

	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(NxOgre::Controller* controller, NxOgre::Controller* other)
{	
	GameObjectPtr object1 = getGameObjectFromController(controller);
	GameObjectPtr object2 = getGameObjectFromController(other);

	if (isAllowedCollision(object1, object2))
	{
		CharactersCollisionEventPtr evt = CharactersCollisionEventPtr(
			new CharactersCollisionEvent(object1, object2));

		mApp->getGameWorldManager()->addEvent(evt);
	}
	
	return NxOgre::Enums::ControllerAction_None;
}

void PhysicsSubsystem::onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, const std::string objectName, NxOgre::Vec3 objectPosition, double objectMass, unsigned int collisionEvent)
{
	int collisionType = COLLISION_TYPE_TRIGGER_UNKNOWN;	
	switch (collisionEvent)
	{
		case NxOgre::Enums::VolumeCollisionType_OnEnter: collisionType = COLLISION_TYPE_TRIGGER_ENTER; break;
		case NxOgre::Enums::VolumeCollisionType_OnExit: collisionType = COLLISION_TYPE_TRIGGER_EXIT; break;
		case NxOgre::Enums::VolumeCollisionType_OnPresence: collisionType = COLLISION_TYPE_TRIGGER_PRESENCE; break;
		default: collisionType = COLLISION_TYPE_TRIGGER_UNKNOWN; break;
	}	 
	/*
	Ogre::LogManager::getSingleton().logMessage("Volume Event Debug Init");
	Ogre::LogManager::getSingleton().logMessage("**********");
	Ogre::LogManager::getSingleton().logMessage(objectName);
	Ogre::LogManager::getSingleton().logMessage("*********");
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(objectPosition.x));
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(objectPosition.y));
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(objectPosition.z));
	Ogre::LogManager::getSingleton().logMessage("**********");
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->getNxOgreController()->getPosition().x));
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->getNxOgreController()->getPosition().y));
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->getNxOgreController()->getPosition().z));
	Ogre::LogManager::getSingleton().logMessage("**********");
	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(NxOgre::Real(objectMass)));
	Ogre::LogManager::getSingleton().logMessage("**********");
	Ogre::LogManager::getSingleton().logMessage("Volume Event Debug End");
	*/
	if (mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->getMass() == objectMass)
	{
		CharacterInTriggerEventPtr evt = CharacterInTriggerEventPtr(
			new CharacterInTriggerEvent(
			mApp->getGameWorldManager()->getGameObjectOny(), 
			getGameObjectFromVolume(volume),
			collisionType));

		mApp->getGameWorldManager()->addEvent(evt);
	}
}

//////////////////////////////////////////////////////////////////
// Auxiliar functions

bool PhysicsSubsystem::setGameObjectSlidingFromController(NxOgre::Controller* controller, NxOgre::Vec3 slideDiplacement, double normalAngle)
{
	bool found = false;
	bool isOny = false;

	TGameObjectPhysicsCharacterContainer container = 
		mApp->getGameWorldManager()->getGameObjectPhysicsCharacterContainer();

	for (unsigned int i=0; !found && i<container.size(); i++)
	{
		if (container[i]->getType().compare(GAME_OBJECT_TYPE_ONY) == 0)
		{
			GameObjectOnyPtr tmpObject = boost::dynamic_pointer_cast<GameObjectOny>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				tmpObject->getPhysicsComponentCharacter()->setSlidingValues(slideDiplacement, normalAngle);
				found = true;
				isOny = true;
			}
		}
		//TODO else if block
		//Same with the rest of game objects which hold a PhysicsComponentCharacter
	}	

	return isOny;
}

bool PhysicsSubsystem::areClose(NxOgre::Vec3 position1, NxOgre::Vec3 position2, double radius)
{
	double diffX = position1.x - position2.x;
	double diffY = position1.y - position2.y;
	double diffZ = position1.z - position2.z;
	
	double diffX2 = diffX * diffX;
	double diffY2 = diffY * diffY;
	double diffZ2 = diffZ * diffZ;

	return sqrt(diffX2 + diffY2 + diffZ2) < radius;
}

bool PhysicsSubsystem::isOnyCloseFromPosition(NxOgre::Vec3 position, double radius)
{
	return areClose(
		mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentPositional()->getPosition(), 
		position, 
		radius);
}

bool PhysicsSubsystem::isAllowedCollision(GameObjectPtr object1, GameObjectPtr object2)
{
	bool isAllowed = true;

	if ((object1->getType().compare(GAME_OBJECT_TYPE_ONY) != 0) ||
		(object2->getType().compare(GAME_OBJECT_TYPE_ONY) != 0))
	{
		isAllowed = false;
	}

	return isAllowed;
}

//////////////////////////////////////////////////////////////////
// Fetch functions

GameObjectPtr PhysicsSubsystem::getGameObjectFromController(NxOgre::Controller* controller)
{
	GameObjectPtr object = GameObject::Null;
	bool found = false;
	
	TGameObjectPhysicsCharacterContainer container = 
		mApp->getGameWorldManager()->getGameObjectPhysicsCharacterContainer();

	for (unsigned int i=0; !found && i<container.size(); i++)
	{
		if (container[i]->getType().compare(GAME_OBJECT_TYPE_ONY) == 0)
		{
			GameObjectOnyPtr tmpObject = boost::dynamic_pointer_cast<GameObjectOny>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_TRIPOLLO) == 0)
		{
			GameObjectTripolloPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTripollo>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_TRIPOLLITO) == 0)
		{
			GameObjectTripollitoPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTripollito>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_EYE) == 0)
		{
			GameObjectEyePtr tmpObject = boost::dynamic_pointer_cast<GameObjectEye>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_TENTETIESO) == 0)
		{
			GameObjectTentetiesoPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTentetieso>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_SCAREDPLANT) == 0)
		{
			GameObjectScaredPlantPtr tmpObject = boost::dynamic_pointer_cast<GameObjectScaredPlant>(container[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		//TODO else if block
		//Same with the rest of game objects which hold a PhysicsComponentCharacter
	}		
	
	return object;
}

GameObjectPtr PhysicsSubsystem::getGameObjectFromShape(NxOgre::Shape* shape)
{
	GameObjectPtr object = GameObject::Null;
	bool found = false;

	TGameObjectPhysicsContainer container[2];
	container[0] = mApp->getGameWorldManager()->getGameObjectPhysicsSimpleContainer();
	container[1] = mApp->getGameWorldManager()->getGameObjectPhysicsComplexContainer();

	for (unsigned int k=0; !found && k<2; k++)
	{
		for (unsigned int i=0; !found && i<container[k].size(); i++)
		{
			if (container[k][i]->getType().compare(GAME_OBJECT_TYPE_TERRAINCONVEX) == 0)
			{
				GameObjectTerrainConvexPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTerrainConvex>(container[k][i]);
				if (tmpObject->getPhysicsComponentComplexConvex()->isInUse() && 
					tmpObject->getPhysicsComponentComplexConvex()->getNxOgreConvex() == shape)
				{
					object= tmpObject;
					found = true;
					//Ogre::LogManager::getSingleton().logMessage(tmpObject->getName());
				}
			}
			else if (container[k][i]->getType().compare(GAME_OBJECT_TYPE_TERRAINTRIANGLE) == 0)
			{
				GameObjectTerrainTrianglePtr tmpObject = boost::dynamic_pointer_cast<GameObjectTerrainTriangle>(container[k][i]);
				if (tmpObject->getPhysicsComponentComplexTriangle()->isInUse() && 
					tmpObject->getPhysicsComponentComplexTriangle()->getNxOgreTriangleGeometry() == shape)
				{
					object= tmpObject;
					found = true;
					//Ogre::LogManager::getSingleton().logMessage(tmpObject->getName());
				}
			}
			else if (container[k][i]->getType().compare(GAME_OBJECT_TYPE_TREE) == 0)
			{
				GameObjectTreePtr tmpObject = boost::dynamic_pointer_cast<GameObjectTree>(container[k][i]);
				if (tmpObject->getPhysicsComponentSimpleBox()->isInUse())
				{
					NxOgre::Shapes shapes = tmpObject->getPhysicsComponentSimpleBox()->getNxOgreKinematicBody()->getShapes();
					for (unsigned int j=0; !found && j<shapes.size(); j++)
					{
						if (shapes[j] == shape)
						{
							object= tmpObject;
							found = true;
							//Ogre::LogManager::getSingleton().logMessage(tmpObject->getName());
						}
					}
				}
			}
		}
	}

	return object;
}

GameObjectPtr PhysicsSubsystem::getGameObjectFromVolume(NxOgre::Volume* volume)
{
	GameObjectPtr object = GameObject::Null;
	bool found = false;
	
	TGameObjectPhysicsVolumeContainer container = 
		mApp->getGameWorldManager()->getGameObjectPhysicsVolumeContainer();

	for (unsigned int i=0; !found && i<container.size(); i++)
	{
		if (container[i]->getType().compare(GAME_OBJECT_TYPE_TRIGGERBOX) == 0)
		{
			GameObjectTriggerBoxPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTriggerBox>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_TRIGGERCAPSULE) == 0)
		{
			GameObjectTriggerCapsulePtr tmpObject = boost::dynamic_pointer_cast<GameObjectTriggerCapsule>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeCapsule()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_ITEM_1UP) == 0)
		{
			GameObjectItem1UPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItem1UP>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_ITEM_MAXHP) == 0)
		{
			GameObjectItemMaxHPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItemMaxHP>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_HEART) == 0)
		{
			GameObjectHeartPtr tmpObject = boost::dynamic_pointer_cast<GameObjectHeart>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_DIAMOND) == 0)
		{
			GameObjectDiamondPtr tmpObject = boost::dynamic_pointer_cast<GameObjectDiamond>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_CLOCKPIECE) == 0)
		{
			GameObjectClockPiecePtr tmpObject = boost::dynamic_pointer_cast<GameObjectClockPiece>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_STORYBOOK) == 0)
		{
			GameObjectStoryBookPtr tmpObject = boost::dynamic_pointer_cast<GameObjectStoryBook>(container[i]);
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		//TODO else if block, same with rest of object which contains a volume
	}	
	
	return object;
}

//////////////////////////////////////////////////////////////////
// Raycast functions

bool PhysicsSubsystem::raycastFromPoint(const Vector3 &point,const Vector3 &normal,Vector3 &result,double maxDistance,QueryFlags flags)
{
	NxOgre::Vec3 StartPos( point );

	NxOgre::Vec3 Direction( normal );
	NxOgre::Ray CubeRay( StartPos, Direction );

	bool returnResult=false;

	NxOgre::RaycastHit mRayResult = getNxOgreScene()->raycastClosestShape( CubeRay, NxOgre::Enums::ShapesType_Static );

	if(mRayResult.mDistance<=maxDistance)
	{
		result=point+normal*mRayResult.mDistance;
		returnResult=true;
	}

	return returnResult;
}