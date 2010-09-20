-- State ids
BOSS_STATE_PATROL = 0
BOSS_STATE_ALERT = 1
BOSS_STATE_CHASE = 2
BOSS_STATE_TIRED = 3
BOSS_STATE_ATTACK = 4
BOSS_STATE_SP_ATTACK = 5
BOSS_STATE_FLASHLIGHT_HIT = 6
BOSS_STATE_STUNNED = 7
BOSS_STATE_LEAVING_NIGHTMARES = 8
BOSS_STATE_PILLOW_HIT = 9
BOSS_STATE_DIE = 10

-- State names
BOSS_STATE_NAMES= {}
BOSS_STATE_NAMES[BOSS_STATE_PATROL]="PATROL"
BOSS_STATE_NAMES[BOSS_STATE_ALERT]="ALERT"
BOSS_STATE_NAMES[BOSS_STATE_CHASE]="CHASE"
BOSS_STATE_NAMES[BOSS_STATE_TIRED]="TIRED"
BOSS_STATE_NAMES[BOSS_STATE_ATTACK]="ATTACK"
BOSS_STATE_NAMES[BOSS_STATE_SP_ATTACK]="SP_ATTACK"
BOSS_STATE_NAMES[BOSS_STATE_FLASHLIGHT_HIT]="FLASHLIGHT_HIT"
BOSS_STATE_NAMES[BOSS_STATE_STUNNED]="STUNNED"
BOSS_STATE_NAMES[BOSS_STATE_LEAVING_NIGHTMARES]="LEAVING_NIGHTMARES"
BOSS_STATE_NAMES[BOSS_STATE_PILLOW_HIT]="PILLOW_HIT"
BOSS_STATE_NAMES[BOSS_STATE_DIE]="DIE"

-- CONSTANTS TO PERFORM SOME RANDOM STATE CHANGES
SP_ATTACK_CHANCE = 0.2
IDLE_TO_PATROL_CHANCE = 0.25
IDLE_TO_IDLE1_CHANCE = 0.4
TREMBLING_TO_CALL_CHANCE = 0.05
BACK_FROM_CALL_TO_CHASE_CHANCE = 0.1

-- Unused for the moment: Modify the value for the field on boss.ctp instead
-- key: (AttackComponent::attack0#attackRange)
MELEE_RANGE = 40

NEIGHBOURS_RANGE = 180

OUAN_WORLD_DREAMS=0
OUAN_WORLD_NIGHTMARES=1

function bossLogic(pBoss,state)

	local myName=pBoss:getName()	
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pBoss:getLineOfSight()
	local any = getAny()
	local world = getWorld()
	
	--local newState=state
	
	-- DEATH CHECK
	if pBoss:hasDied() then
		return BOSS_STATE_DEAD
	end
	
	-- FLASHLIGHT HIT CHECK
	if pBoss:hasBeenHit() and world == OUAN_WORLD_NIGHTMARES then
		return BOSS_STATE_FLASHLIGHT_HIT
	end
		
	-- ALERT CHECK
	if pBoss:isAlertFinished() and state == BOSS_STATE_ALERT then
		return BOSS_STATE_CHASE
	end
	
	-- TIRED CHECK
	if pBoss:isTiredFinished() and state == BOSS_STATE_TIRED then
		log(myName.." : CHANGED STATE TO PATROL")
		return BOSS_STATE_PATROL
	end
	
	-- ATTACK CHECK
	if pBoss:isAttackFinished() and state == BOSS_STATE_ATTACK then
		log(myName.." : CHANGED STATE TO CHASE")
		return BOSS_STATE_CHASE	
	end
	
	-- SPECIAL ATTACK CHECK
	if pBoss:isAttackFinished() and state == BOSS_STATE_SP_ATTACK then
		log(myName.." : CHANGED STATE TO CHASE")
		return BOSS_STATE_CHASE	
	end
	
	-- PILLOW HIT CHECK
	if state == BOSS_STATE_STUNNED then
		if  pBoss:hasBeenHit() and world == OUAN_WORLD_DREAMS then
			return BOSS_STATE_PILLOW_HIT
		elseif pBoss:isStunnedFinished() then
			return BOSS_STATE_PATROL
		end
			return state
	end	
	
	if state == BOSS_STATE_FLASHLIGHT_HIT and pBoss:isFlashLightHitFinished() then
		return BOSS_STATE_STUNNED
	end	
		
	-- PATROL TRANSITION:
	if state==BOSS_STATE_PATROL then
		if playerDistance<=myLOS then
			log (myName.." CHANGED STATE TO ALERT")
			return BOSS_STATE_ALERT
		end
		return state
	end
	
	-- CHASE TRANSITIONS
	if state==BOSS_STATE_CHASE then
		local meleeRange =  pBoss:getMeleeRange()
		log ("PLAYER DISTANCE: "..playerDistance..", LOS: "..(myLOS/3)..", Melée range: "..meleeRange)
		if playerDistance>=(myLOS/3) then
			log (myName.." CHANGED STATE TO TIRED")
			return BOSS_STATE_TIRED
		elseif playerDistance<=meleeRange and math.random()<=SP_ATTACK_CHANCE then
			log (myName.." CHANGED STATE TO SP_ATTACK")
			return BOSS_STATE_SP_ATTACK
		elseif playerDistance<=meleeRange then
			log (myName.." CHANGED STATE TO ATTACK")
			return BOSS_STATE_ATTACK
		end
	end
	
	return state

end