-- State ids
TRIPOLLO_STATE_IDLE = 0
TRIPOLLO_STATE_PATROL = 1
TRIPOLLO_STATE_SURPRISE = 2
TRIPOLLO_STATE_FIND = 3
TRIPOLLO_STATE_FALSE_ALARM = 4
TRIPOLLO_STATE_ALERT = 5
TRIPOLLO_STATE_CHASE = 6
TRIPOLLO_STATE_TIRED = 7
TRIPOLLO_STATE_ATTACK = 8
TRIPOLLO_STATE_FLEE = 9
TRIPOLLO_STATE_DEAD = 10
TRIPOLLO_STATE_HIT = 11
TRIPOLLO_STATE_CALL_TO_ARMS = 12
TRIPOLLO_STATE_TREMBLING = 13
TRIPOLLO_STATE_IDLE1 = 14
TRIPOLLO_STATE_STATUE = 15
TRIPOLLO_STATE_CALL_TO_CHASE = 16
TRIPOLLO_STATE_DIVING_ATTACK=17

-- State names
TRIPOLLO_STATE_NAMES= {}
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_IDLE]="IDLE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_PATROL]="PATROL"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_FIND]="FIND"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_CHASE]="CHASE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_ATTACK]="ATTACK"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_FLEE]="FLEE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_DEAD]="DEAD"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_HIT]="HIT"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_SURPRISE]="SURPRISE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_ALERT]="ALERT"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_FALSE_ALARM]="FALSE_ALARM"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_TIRED]="TIRED"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_CALL_TO_ARMS]="CALL_TO_ARMS"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_TREMBLING]="TREMBLING"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_STATUE]="STATUE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_CALL_TO_CHASE]="CALL_TO_CHASE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_DIVING_ATTACK]="DIVING_ATTACK"

-- CONSTANTS TO PERFORM SOME RANDOM STATE CHANGES
PATROL_TO_IDLE_CHANCE = 0.15
IDLE_TO_PATROL_CHANCE = 0.05
IDLE_TO_IDLE1_CHANCE = 0.4
TREMBLING_TO_CALL_CHANCE = 0.05
BACK_FROM_CALL_TO_CHASE_CHANCE = 0.1

-- Unused for the moment: Modify the value for the field on tripollo.ctp instead
-- key: (AttackComponent::attack0#attackRange)
MELEE_RANGE = 40

NEIGHBOURS_RANGE = 220

FIND_DISTANCE = 180
CHASE_DISTANCE = 100

function tripolloLogic(pTripollo,state)

	local myName=pTripollo:getName()	
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pTripollo:getLineOfSight()
	local any = getAny()
	local world = getWorld();
	local isFlying = pTripollo:isFlying();
	
	-- DEATH CHECK
	if pTripollo:hasDied() then
		return TRIPOLLO_STATE_DEAD
	end
	
	-- STATUE CHECK
	if pTripollo:isStatueEnabled() then
		return TRIPOLLO_STATE_STATUE
	elseif state == TRIPOLLO_STATE_STATUE then
		return TRIPOLLO_STATE_CHASE
	end
	
	-- HIT CHECK
	if pTripollo:hasBeenHit() then
		return TRIPOLLO_STATE_HIT
	end	
	
	-- IDLE 1 CHECK
	if pTripollo:isIdle1Finished() and state == TRIPOLLO_STATE_IDLE1 then
		--log(myName.." : CHANGED STATE TO PATROL")
		return TRIPOLLO_STATE_PATROL
	end
	
	-- HIT RECOVERY:
	if not pTripollo:hasBeenHit() and state == TRIPOLLO_STATE_HIT then
		return TRIPOLLO_STATE_CHASE
	end
		
	-- PATROL TRANSITION:
	if state==TRIPOLLO_STATE_PATROL then
		if playerDistance<=FIND_DISTANCE then
			return TRIPOLLO_STATE_SURPRISE
		end
	end
	
	-- TIRED CHECK
	if pTripollo:isTiredFinished() and state == TRIPOLLO_STATE_TIRED then
		--log(myName.." : CHANGED STATE TO FIND")
		return TRIPOLLO_STATE_FIND
	end
	
	-- SURPRISE CHECK
	if pTripollo:isSurpriseFinished() and state == TRIPOLLO_STATE_SURPRISE then
		return TRIPOLLO_STATE_FIND
	end
	
	-- FIND TRANSITIONS:
	if state==TRIPOLLO_STATE_FIND then
		if playerDistance>FIND_DISTANCE then
			return TRIPOLLO_STATE_PATROL
		elseif playerDistance<=CHASE_DISTANCE then
			return TRIPOLLO_STATE_CHASE	
		end
	end
	
	-- CHASE TRANSITIONS
	if state==TRIPOLLO_STATE_CHASE then
		if playerDistance>CHASE_DISTANCE then
			--log (myName.." CHANGED STATE TO TIRED")
			return TRIPOLLO_STATE_TIRED
		elseif pTripollo:hasHitOny() then
			--log (myName.." CHANGED STATE TO ATTACK")
			return TRIPOLLO_STATE_ATTACK
		end
	end
	
    -- ATTACK CHECK
    if pTripollo:isAttackFinished() and state == TRIPOLLO_STATE_ATTACK then
            --log(myName.." : CHANGED STATE TO CHASE")
            return TRIPOLLO_STATE_CHASE     
    end


	return state

end
--[[
function tripolloNightmaresLogic(pTripollo,state)
	return state
end

function tripolloLogic(pTripollo,state)
	local world = getWorld()
	local newState = -1
	if world == OUAN_WORLD_DREAMS then
		log("Exec. tripollo dreams logic")
		newState = tripolloDreamsLogic(	pTripollo,state)
	else
		log("Exec. tripollo nightmares logic")
		newState = tripolloNightmaresLogic(pTripollo,state)
	end
	return newState
end
--]]	
