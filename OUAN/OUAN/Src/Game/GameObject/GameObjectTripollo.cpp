#include "OUAN_Precompiled.h"

#include "GameObjectTripollo.h"
#include "GameObjectOny.h"
#include "GameObjectSwitch.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLO)
{
	
}

GameObjectTripollo::~GameObjectTripollo()
{

}
/// Set logic component
void GameObjectTripollo::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectTripollo::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}
void GameObjectTripollo::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTripollo::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTripollo::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTripollo::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTripollo::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTripollo::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTripollo::setRenderComponentParticleSystemDieDreams(RenderComponentParticleSystemPtr pRenderComponentParticleSystemDieDreams)
{
	mRenderComponentParticleSystemDieDreams = pRenderComponentParticleSystemDieDreams;
}

void GameObjectTripollo::setRenderComponentParticleSystemDieNightmares(RenderComponentParticleSystemPtr pRenderComponentParticleSystemDieNightmares)
{
	mRenderComponentParticleSystemDieNightmares = pRenderComponentParticleSystemDieNightmares;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemDieDreams() const
{
	return mRenderComponentParticleSystemDieDreams;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemDieNightmares() const
{
	return mRenderComponentParticleSystemDieNightmares;
}

void GameObjectTripollo::setRenderComponentParticleSystemShock(RenderComponentParticleSystemPtr pRenderComponentParticleSystemShock)
{
	mRenderComponentParticleSystemShock = pRenderComponentParticleSystemShock;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemShock() const
{
	return mRenderComponentParticleSystemShock;
}

void GameObjectTripollo::setRenderComponentParticleSystemSurprise(RenderComponentParticleSystemPtr pRenderComponentParticleSystemSurprise)
{
	mRenderComponentParticleSystemSurprise = pRenderComponentParticleSystemSurprise;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemSurprise() const
{
	return mRenderComponentParticleSystemSurprise;
}

void GameObjectTripollo::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripollo::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectTripollo::setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon)
{
	mPhysicsComponentWeapon=pPhysicsComponentWeapon;
}

PhysicsComponentWeaponPtr GameObjectTripollo::getPhysicsComponentWeapon() const
{
	return mPhysicsComponentWeapon;
}


bool GameObjectTripollo::activateTrajectory(int newWorld)
{
	std::string trajectoryName = getPatrolTrajectoryName(newWorld);
	if(mTrajectoryComponent->predefinedTrajectoryExists(trajectoryName))
	{
		mTrajectoryComponent->activatePathfindingToPredefinedTrajectory(trajectoryName,newWorld,true);
		return true;
	}
	else
	{
		mTrajectoryComponent->activateIdle(getName(),newWorld);
		return false;
	}
}

void GameObjectTripollo::activateFlying(bool flying)
{
	mPhysicsComponentCharacter->setFlyingCharacter(flying);
	mLogicComponentEnemy->setFlyingEnabled(flying);
	if(flying)
	{
		mTrajectoryComponent->setAs3DTrajectory();
	}
	else
	{
		mTrajectoryComponent->setAs2DTrajectory();
	}
}

void GameObjectTripollo::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	checkDeathParticleSystem(elapsedSeconds);

	if (isEnabled())
	{
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		int currentState=mLogicComponentEnemy->getState();

		if (mPhysicsComponentCharacter.get())
		{
			int world = mGameWorldManager->getWorld();

			RenderComponentEntityPtr entity;
			if (world == DREAMS && mRenderComponentEntityDreams.get())
				entity = mRenderComponentEntityDreams;
			else if (world ==NIGHTMARES && mLogicComponentEnemy->existsInNightmares() &&
					mRenderComponentEntityNightmares.get())
				entity = mRenderComponentEntityNightmares;

			if (entity.get())
			{
				std::string onyName = mGameWorldManager->getGameObjectOny()->getName();


				if (currentState!=logicSS->getGlobalInt(TRIPOLLO_STATE_ATTACK) && mLogicComponentEnemy->isStateChanged())
				{
					mPhysicsComponentWeapon->endAttack();
				}

				if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE) && 
					mLogicComponentEnemy->isStateChanged())
				{
					std::string nextAnim=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
						?TRIPOLLO_ANIM_FNM_STATUE
						:TRIPOLLO_ANIM_STATUE;
					changeAnimation(nextAnim);
					mTrajectoryComponent->activateIdle(getName(),world);
				}
				//Check for state changes and update things appropriately
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_IDLE;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
								?TRIPOLLO_ANIM_FNM_WALK
								:TRIPOLLO_ANIM_NM_IDLE;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else if (currentState == logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE1))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{

						std::string animationName=TRIPOLLO_ANIM_IDLE1;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_IDLE
							:TRIPOLLO_ANIM_NM_IDLE1;
						entity->changeAnimation(animationName);
						
						//mAudioComponent->playSound(TRIPOLLO_SOUND_WINGS);
						//Idle 1 can only come from idle, so there is no trajectory change
					}
				}
				else if (currentState == logicSS->getGlobalInt(TRIPOLLO_STATE_SURPRISE))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_SURPRISE;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_SURPRISE
							:TRIPOLLO_ANIM_NM_SURPRISE;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setSurpriseFinished(false);
						mRenderComponentParticleSystemSurprise->start();
						//mAudioComponent->playSound(TRIPOLLO_SOUND_SURPRISE);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_PATROL))
				{				
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string walkAnim=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_WALK
							:TRIPOLLO_ANIM_NM_WALK;
						activateTrajectory(mGameWorldManager->getWorld());
						entity->changeAnimation(walkAnim);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FIND))
				{
					//Logger::getInstance()->log("FIND");
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_WALK_FAST;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_WALK_FAST
							:TRIPOLLO_ANIM_NM_WALK_FAST;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activatePathFinding(onyName,world);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FALSE_ALARM))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_FALSE_ALARM;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_FALSE_ALARM
							:TRIPOLLO_ANIM_NM_FALSE_ALARM;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setFalseAlarmFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_ALERT))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_ALERT;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_ALERT
							:TRIPOLLO_ANIM_NM_ALERT;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setAlertFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
				{			
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_RUN;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_RUN
							:TRIPOLLO_ANIM_NM_RUN;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateChase(onyName);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_TIRED))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						std::string animationName=TRIPOLLO_ANIM_TIRED;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_FNM_TIRED
							:TRIPOLLO_ANIM_NM_TIRED;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setTiredFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_ATTACK))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(Utils::Random::getInstance()->getRandomDouble()>0.5
							?TRIPOLLO_ANIM_ATTACK_00
							:TRIPOLLO_ANIM_ATTACK_01);
						mTrajectoryComponent->activateIdle(getName(),world);
						mPhysicsComponentWeapon->startAttack();
						mLogicComponentEnemy->setAttackFinished(false);
						mAudioComponent->playSound(TRIPOLLO_SOUND_ATTACK);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FLEE))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(mGameWorldManager->getWorld()==NIGHTMARES
							?TRIPOLLO_ANIM_NM_RUN
							:TRIPOLLO_ANIM_RUN);
						mTrajectoryComponent->activateFlee(onyName, mLogicComponentEnemy->getLineOfSight()*0.3);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_HIT))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						mRenderComponentParticleSystemShock->start();
						mAudioComponent->playSound(TRIPOLLO_SOUND_HIT);

						std::string hitAnimation = 
							Utils::Random::getInstance()->getRandomDouble()>0.5
								?TRIPOLLO_ANIM_HIT01
								:TRIPOLLO_ANIM_HIT02;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
						{
							hitAnimation=mLogicComponentEnemy->getEnemyType()
								==ENEMY_TYPE_FLYING
								?TRIPOLLO_ANIM_FNM_HIT01
								:TRIPOLLO_ANIM_NM_HIT01;
						}

						entity->changeAnimation(hitAnimation);

						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CALL_TO_ARMS))
				{
					//Logger::getInstance()->log("CHASE");
					if (mLogicComponentEnemy->isStateChanged())
					{
						if(mGameWorldManager->getPlayerDistance(getName())<CALL_TO_ARMS_SOUND_DISTANCE)
						{
							mAudioComponent->playSound(TRIPOLLO_SOUND_CALL_TO_ARMS);
						}
						entity->changeAnimation(TRIPOLLO_ANIM_CALL_TO_ARMS);
						double range = logicSS->getGlobalReal("MELEE_RANGE");
						bool callHeard = callNeighboursInRange(range);
						mLogicComponentEnemy->setCallWasHeard(callHeard);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setCallToArmsFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_TREMBLING))
				{
					//Logger::getInstance()->log("CHASE");
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(
							mGameWorldManager->getWorld()==NIGHTMARES
							?TRIPOLLO_ANIM_NM_AFRAID
							:TRIPOLLO_ANIM_AFRAID);					
						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CALL_TO_CHASE))
				{
					//Logger::getInstance()->log("CHASE");
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_RUN);
						mTrajectoryComponent->activateChase(onyName);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_DEAD))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{

						mAudioComponent->playSound(TRIPOLLO_SOUND_DIE);
						std::string animationName=TRIPOLLO_ANIM_DIE;
						if (mGameWorldManager->getWorld()==NIGHTMARES)
							animationName=mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_FLYING
							?TRIPOLLO_ANIM_NM_DIE
							:TRIPOLLO_ANIM_FNM_DIE;
						entity->changeAnimation(animationName);
						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else
				{
					//DO NOTHING
				}

				if(currentState!=logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE))
				{
					entity->update(elapsedSeconds);
				}

			}			

			mTrajectoryComponent->update(elapsedSeconds);

			if (mPhysicsComponentCharacter->isInUse())
			{
				Ogre::Vector3 movement = mTrajectoryComponent->getNextMovementAbsolute();				
				mPhysicsComponentCharacter->setOuternMovement(movement);
			}
			if (mPhysicsComponentWeapon->isInUse())
			{
				Ogre::Vector3 pos;
				if (entity.get() && entity->getEntity()->hasSkeleton()
					&& entity->getEntity()->getSkeleton()->hasBone(HEAD_BONE_NAME))
				{
					Ogre::Entity* ent = entity->getEntity();
					Ogre::Node* bone = ent->getSkeleton()->getBone(HEAD_BONE_NAME);
					pos=Utils::getNodeWorldPosition(ent,bone);			
				}
				else
				{
					mRenderComponentPositional->getPosition();			
				}
				mPhysicsComponentWeapon->setPosition(pos);			
				mPhysicsComponentWeapon->setDisplayYaw(mPhysicsComponentCharacter->getDisplayYaw());
				mPhysicsComponentWeapon->update(elapsedSeconds);
			}
		}
	}
	else
	{		
		if (mRenderComponentEntityDreams.get())
			mRenderComponentEntityDreams->setVisible(false);
		if (mRenderComponentEntityNightmares.get())
			mRenderComponentEntityNightmares->setVisible(false);
		if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->destroy();
		}
	}
}

void GameObjectTripollo::checkTripolloPlataformPuzzleActivations()
{
	GameObjectPtr obj;
	if(getName().compare("tripollo#"+CUTSCENE_7_1_TRIPOLLOS_PLATFORM)==0)
	{
		obj=getGameWorldManager()->getObject("switch#"+CUTSCENE_7_1_TRIPOLLOS_PLATFORM);
	}
	else if(getName().compare("tripollo#"+CUTSCENE_7_2_TRIPOLLOS_PLATFORM)==0)
	{
		obj=getGameWorldManager()->getObject("switch#"+CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
	}
	else if(getName().compare("tripollo#"+CUTSCENE_7_3_TRIPOLLOS_PLATFORM)==0)
	{
		obj=getGameWorldManager()->getObject("switch#"+CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
	}
	else if(getName().compare("tripollo#satue1")==0)
	{
		getGameWorldManager()->addExecutedLevelEvent(TRIPOLLO_1_STATUE_DEFEATED);
	}
	else if(getName().compare("tripollo#satue2")==0)
	{
		getGameWorldManager()->addExecutedLevelEvent(TRIPOLLO_2_STATUE_DEFEATED);
	}
	else if(getName().compare("tripollo#satue3")==0)
	{
		getGameWorldManager()->addExecutedLevelEvent(TRIPOLLO_3_STATUE_DEFEATED);
	}
	else if(getName().compare("tripollo#satue4")==0)
	{
		getGameWorldManager()->addExecutedLevelEvent(TRIPOLLO_4_STATUE_DEFEATED);
	}
	else
	{
		Logger::getInstance()->log("tripollo "+getName()+" defeated");
	}

	if(obj.get())
	{
		GameObjectSwitchPtr obj_switch= 
			BOOST_PTR_CAST(GameObjectSwitch,obj);
		obj_switch->makePushable();
	}
}

void GameObjectTripollo::postUpdate()
{
	GameObject::postUpdate();
}

AttackComponentPtr GameObjectTripollo::getAttackComponent() const
{
	return mAttackComponent;
}

void GameObjectTripollo::setAttackComponent(AttackComponentPtr attackComponent)
{
	mAttackComponent=attackComponent;
}

std::string GameObjectTripollo::getDefaultAttack()
{
	return TRIPOLLO_ATTACK_PECK;
}

void GameObjectTripollo::reset()
{
	mDeathTime = -1;

	if((getName().compare("tripollo#"+CUTSCENE_7_1_TRIPOLLOS_PLATFORM)==0 ||
		getName().compare("tripollo#"+CUTSCENE_7_2_TRIPOLLOS_PLATFORM)==0 || 
		getName().compare("tripollo#"+CUTSCENE_7_3_TRIPOLLOS_PLATFORM)==0) &&
		getGameWorldManager()->hasExecutedLevelEvent(TRIPOLLO_PLATFORM_PUZZLE_END))
	{
		return;
	}

	GameObject::reset();

	LogicSubsystemPtr logicSS = getGameWorldManager()->getParent()->getLogicSubsystem();

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->reset();
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueDegrees());
		mLogicComponentEnemy->setHasDied(false);
		mLogicComponentEnemy->setHasBeenHit(false);
		//TODO DO THAT PROPERLY
		mLogicComponentEnemy->setInitialHealthPoints(3);

	}		
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
		mLogicComponentEnemy->setHasDied(false);
		mLogicComponentEnemy->setHasBeenHit(false);
		//TODO DO THAT PROPERLY
		mLogicComponentEnemy->setInitialHealthPoints(3);
	}
}

void GameObjectTripollo::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityDreams->setDreamsMaterials();
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(false);
	}	
}

void GameObjectTripollo::setNightmaresRender()
{
	if (!isEnabled()) return;

	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(false);
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(true);
		mRenderComponentEntityNightmares->setNightmaresMaterials();
	}	
}

void GameObjectTripollo::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->setChangeWorldFactor(factor);
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setChangeWorldFactor(factor);
	}
}

void GameObjectTripollo::setChangeWorldRender()
{
	if (!isEnabled()) return;
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponentEnemy->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			if(mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
			}	
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(false);
			}
			if(mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}	
			break;
		default:break;
	}
}

void GameObjectTripollo::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			mLogicComponentEnemy->setStatueEnabled(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			setNightmaresRender();
			if (mLogicComponentEnemy->isStatueEnabled())
				mLogicComponentEnemy->setStatueEnabled(false);
			else mLogicComponentEnemy->setState(Application::getInstance()->getLogicSubsystem()->getGlobalInt(TRIPOLLO_STATE_IDLE));
			break;
		default:break;
	}

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{

			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->create();
				}
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->destroy();
				}
			}
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->destroy();
				}
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->create();
				}
			}	
			break;
		default:break;
	}
}

void GameObjectTripollo::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			break;
		case NIGHTMARES:
			break;
		default:break;
	}

}

void GameObjectTripollo::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			break;
		case NIGHTMARES:	
			break;
		default:
			break;
	}
}


void GameObjectTripollo::setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent)
{
	mTrajectoryComponent=pTrajectoryComponent;
}

TrajectoryComponentPtr GameObjectTripollo::getTrajectoryComponent()
{
	return mTrajectoryComponent;
}

bool GameObjectTripollo::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTripollo::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTripollo::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTripollo::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectTripollo::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject, pNormal);
	}

	if(mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse() && pGameObject->getType().compare(GAME_OBJECT_TYPE_WATER)!=0)
	{
		mPhysicsComponentCharacter->calculateSliding(pNormal);
	}
}

void GameObjectTripollo::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectTripollo::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

bool GameObjectTripollo::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTripollo::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//
void GameObjectTripollo::processAnimationEnded(const std::string& animationName)
{
	if (isHitAnimation(animationName))
	{
		mLogicComponentEnemy->setHasBeenHit(false);
	}
	if (isDieAnimation(animationName))
	{
		disableDisplayMsg();
		std::string msg="Enemy ";
		msg.append(getName()).append(" died");
		Logger::getInstance()->log(msg);
		mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
		mAudioComponent->playSound(TRIPOLLO_SOUND_EXPLODE);

		switch(mWorld)
		{
			case DREAMS: mRenderComponentParticleSystemDieDreams->start(); break;
			case NIGHTMARES: mRenderComponentParticleSystemDieNightmares->start(); break;
		}

		mDeathTime = 0;
		Logger::getInstance()->log("Check death PS :: mDeathTime set to 0 :: " + getName() + " :: " + Ogre::StringConverter::toString(Ogre::Real(mDeathTime)) + " :: " + Ogre::StringConverter::toString(Ogre::Real(MAX_TIME_DEATH_PARTICLE_SYSTEM)));

		checkTripolloPlataformPuzzleActivations();

		disable();		
	}
	if (isAlertAnimation(animationName))
	{
		mLogicComponentEnemy->setAlertFinished(true);
	}
	if (animationName.compare(TRIPOLLO_ANIM_ATTACK_00)==0 || 
		animationName.compare(TRIPOLLO_ANIM_ATTACK_01)==0)
	{
		mLogicComponentEnemy->setAttackFinished(true);
		mPhysicsComponentWeapon->endAttack();
	}
	if (animationName.compare(TRIPOLLO_ANIM_CALL_TO_ARMS)==0)
	{
		mLogicComponentEnemy->setCallToArmsFinished(true);
	}
	if (isSurpriseAnimation(animationName))
	{
		mLogicComponentEnemy->setSurpriseFinished(true);
	}
	if (isFalseAlarmAnimation(animationName))
	{
		mLogicComponentEnemy->setFalseAlarmFinished(true);
	}
	if (isTiredAnimation(animationName))
	{
		mLogicComponentEnemy->setTiredFinished(true);
	}
}

bool GameObjectTripollo::hasBeenHit() const
{
	if (mLogicComponentEnemy.get())	
		return mLogicComponentEnemy->hasBeenHit();
	return false;
}

bool GameObjectTripollo::hasDied() const
{
	if (mLogicComponentEnemy.get())
		return mLogicComponentEnemy->hasDied();
	return false;
}

AudioComponentPtr GameObjectTripollo::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectTripollo::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

AudioComponentPtr GameObjectTripollo::getAudioComponentInstance() const
{
	return mAudioComponent;
}

bool GameObjectTripollo::hasAudioComponent() const
{
	return true;
}
void GameObjectTripollo::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponentEnemy->existsInDreams())
		{
			mRenderComponentEntityDreams->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentEnemy->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
bool GameObjectTripollo::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTripollo::getLogicComponent() const
{
	if (mGameWorldManager->getWorld()==DREAMS && mLogicComponentEnemy->existsInDreams()
		|| mGameWorldManager->getWorld()==NIGHTMARES && mLogicComponentEnemy->existsInNightmares())
		return mLogicComponentEnemy;
	return LogicComponentPtr();
}

double GameObjectTripollo::getMeleeRange() const
{
	if (mAttackComponent.get())
	{
		return mAttackComponent->getSelectedAttack()->attackRange;
	}
	return 0;
}

int GameObjectTripollo::countNeighboursInRange(double range, bool call) const
{
	std::string name= getName();
	TGameObjectTripolloContainer* tripollos= mGameWorldManager->getGameObjectTripolloContainer();
	if (!tripollos->empty())
	{
		int neighbours=0;
		double currentDistance=0;
		GameObjectTripolloPtr tripollo;
		for (TGameObjectTripolloContainer::iterator it=tripollos->begin();it!=tripollos->end();++it)
		{
			tripollo = *it;
			currentDistance= computeDistanceTo(tripollo);
			if (tripollo->isEnabled() && currentDistance<range && 
				tripollo->getName().compare(name)!=0)
			{
				if (call) 
					tripollo->getLogicComponentEnemy()->setHasHeardCall(true);
				neighbours++;
			}
		}
		return neighbours;
	}
	return 0;
}
bool GameObjectTripollo::isStatueEnabled() const
{
	return mLogicComponentEnemy->isStatueEnabled();
}

void GameObjectTripollo::enable()
{
	GameObject::enable();
	LogicSubsystemPtr logicSS = Application::getInstance()->getLogicSubsystem();
	if(!mLogicComponentEnemy->isStatueEnabled())
	{
		mLogicComponentEnemy->setState(logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE));
	}
	else
	{
		mLogicComponentEnemy->setState(logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE));
	}
	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
}
bool GameObjectTripollo::hasPatrolTrajectory()
{
	return mTrajectoryComponent->predefinedTrajectoryExists(getPatrolTrajectoryName(
		mGameWorldManager->getWorld()));
}

std::string GameObjectTripollo::getPatrolTrajectoryName(int world)
{
	std::string trajectoryName = getName();
	trajectoryName.append(world==DREAMS?SUFFIX_DREAMS:SUFFIX_NIGHTMARES);
	return trajectoryName;
}

bool GameObjectTripollo::isHitAnimation(const std::string& animationName) const
{
	return 
		animationName.compare(TRIPOLLO_ANIM_HIT01)==0 || 
		animationName.compare(TRIPOLLO_ANIM_HIT02)==0 ||
		animationName.compare(TRIPOLLO_ANIM_NM_HIT01) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_FNM_HIT01)==0;
}

bool GameObjectTripollo::isDieAnimation(const std::string& animationName) const
{
	return animationName.compare(TRIPOLLO_ANIM_DIE)==0 ||
		animationName.compare(TRIPOLLO_ANIM_NM_DIE)==0 ||
		animationName.compare(TRIPOLLO_ANIM_FNM_DIE)==0;

}

bool GameObjectTripollo::isAlertAnimation(const std::string& animationName) const
{
	return animationName.compare(TRIPOLLO_ANIM_ALERT)==0 ||
		animationName.compare(TRIPOLLO_ANIM_NM_ALERT)==0 ||
		animationName.compare(TRIPOLLO_ANIM_FNM_ALERT)==0;
}

bool GameObjectTripollo::isFalseAlarmAnimation(const std::string& animationName) const
{
	return animationName.compare(TRIPOLLO_ANIM_FALSE_ALARM) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_NM_FALSE_ALARM) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_FNM_FALSE_ALARM) ==0;
}

bool GameObjectTripollo::isSurpriseAnimation(const std::string& animationName) const
{
	return animationName.compare(TRIPOLLO_ANIM_SURPRISE) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_NM_SURPRISE) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_FNM_SURPRISE) ==0;
}

bool GameObjectTripollo::isTiredAnimation(const std::string& animationName) const
{
	return animationName.compare(TRIPOLLO_ANIM_TIRED) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_NM_TIRED) ==0 ||
		animationName.compare(TRIPOLLO_ANIM_FNM_TIRED) ==0;
}

void GameObjectTripollo::checkDeathParticleSystem(double elapsedSeconds)
{
	if (mDeathTime >= 0)
	{
		Logger::getInstance()->log("Check death PS :: mDeathTime is > 0 :: " + getName() + " :: ES " + Ogre::StringConverter::toString(Ogre::Real(elapsedSeconds)) + " :: DT " + Ogre::StringConverter::toString(Ogre::Real(mDeathTime)) + " :: MDT " + Ogre::StringConverter::toString(Ogre::Real(MAX_TIME_DEATH_PARTICLE_SYSTEM)));
		mDeathTime += elapsedSeconds;	

		if (mDeathTime >= MAX_TIME_DEATH_PARTICLE_SYSTEM)
		{
			Logger::getInstance()->log("Check death PS :: mDeathTime border crossed :: " + getName());

			if(mLogicComponentEnemy->existsInDreams())
			{
				Logger::getInstance()->log("Check death PS :: stopping dreams die PS :: " + getName());
				mRenderComponentParticleSystemDieDreams->stop();	
			}

			if(mLogicComponentEnemy->existsInNightmares())
			{
				Logger::getInstance()->log("Check death PS :: stopping nightmares die PS :: " + getName());
				mRenderComponentParticleSystemDieNightmares->stop();
			}	

			mDeathTime = -1;
		}
	}
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{

}