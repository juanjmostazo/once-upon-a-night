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
IDLE_TO_PATROL_CHANCE = 0.25
IDLE_TO_IDLE1_CHANCE = 0.4
TREMBLING_TO_CALL_CHANCE = 0.05
BACK_FROM_CALL_TO_CHASE_CHANCE = 0.1

-- Unused for the moment: Modify the value for the field on tripollo.ctp instead
-- key: (AttackComponent::attack0#attackRange)
MELEE_RANGE = 40

NEIGHBOURS_RANGE = 180


function tripolloLogic(pTripollo,state)

	local myName=pTripollo:getName()	
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pTripollo:getLineOfSight()
	local any = getAny()
	local world = getWorld();
	local isFlying = pTripollo:isFlying();
	
	--local newState=state
	
	-- DEATH CHECK
	if pTripollo:hasDied() then
		return TRIPOLLO_STATE_DEAD
	end
	
	-- STATUE CHECK
	if pTripollo:isStatueEnabled() then
		return TRIPOLLO_STATE_STATUE
	elseif state == TRIPOLLO_STATE_STATUE then
		return TRIPOLLO_STATE_IDLE
	end
	
	-- HIT CHECK
	if pTripollo:hasBeenHit() then
		return TRIPOLLO_STATE_HIT
	end	
	
	-- CALL RESPONSE
	
	if pTripollo:hasHeardCall() then
		log (myName.." says: I've heard the call!")
		log (myName.." : CHANGED STATE TO CALL_CHASE")
		return TRIPOLLO_STATE_CALL_TO_CHASE
	end
	
	-- SURPRISE CHECK
	if pTripollo:isSurpriseFinished() and state == TRIPOLLO_STATE_SURPRISE then
		return TRIPOLLO_STATE_FIND
	end
		
	-- FALSE ALARM CHECK
	if pTripollo:isFalseAlarmFinished() and state == TRIPOLLO_STATE_FALSE_ALARM then
		if pTripollo:hasPatrolTrajectory() then
			log(myName.." : CHANGED STATE TO PATROL")
			return TRIPOLLO_STATE_PATROL
		else
			log(myName.." doesn't have a patrol trajectory set: CHANGED STATE TO IDLE")
			return TRIPOLLO_STATE_IDLE
		end
	end
		
	-- ALERT CHECK
	if pTripollo:isAlertFinished() and state == TRIPOLLO_STATE_ALERT then
		return TRIPOLLO_STATE_CHASE
	end
	
	-- TIRED CHECK
	if pTripollo:isTiredFinished() and state == TRIPOLLO_STATE_TIRED then
		log(myName.." : CHANGED STATE TO FIND")
		return TRIPOLLO_STATE_FIND
	end
	
	-- IDLE 1 CHECK
	if pTripollo:isIdle1Finished() and state == TRIPOLLO_STATE_IDLE1 then
		log(myName.." : CHANGED STATE TO IDLE")
		return TRIPOLLO_STATE_IDLE
	end
	
	-- ATTACK CHECK
	if pTripollo:isAttackFinished() and state == TRIPOLLO_STATE_ATTACK then
		log(myName.." : CHANGED STATE TO CHASE")
		return TRIPOLLO_STATE_CHASE	
	end
	
	-- CALL TO ARMS CHECK
	if pTripollo:isCallToArmsFinished() and state == TRIPOLLO_STATE_CALL_TO_ARMS then
		if pTripollo:callWasHeard() then
			log(myName.." : Reinforcements are coming: CHANGED STATE TO ALERT")
			return TRIPOLLO_STATE_CHASE
		else
			log(myName.." : Back to hiding in a corner: CHANGED STATE TO TREMBLING")
			return TRIPOLLO_STATE_TREMBLING
		end
	end
	
	-- HIT RECOVERY:
	if not pTripollo:hasBeenHit() and state == TRIPOLLO_STATE_HIT then
		if pTripollo:getHP()==1 and any:getHP()>1 and pTripollo:getNeighboursInRange(NEIGHBOURS_RANGE)==0 then
			log(myName.." : Too weak to fight: CHANGING STATE TO FLEE")
			return TRIPOLLO_STATE_FLEE
		else
			local prevState=pTripollo:getPreviousState()
			log (myName.." Going back to "..getStateName(prevState,TRIPOLLO_STATE_NAMES))
			return prevState
		end
	end
			
	-- IDLE TRANSITIONS:		
	if state==TRIPOLLO_STATE_IDLE then
		if playerDistance<=myLOS then
			log (myName.." CHANGED STATE TO SURPRISE")
			return TRIPOLLO_STATE_SURPRISE
		elseif math.random()<=IDLE_TO_PATROL_CHANCE and pTripollo:hasPatrolTrajectory() then
			return TRIPOLLO_STATE_PATROL
		elseif math.random() <= IDLE_TO_IDLE1_CHANCE then
			return TRIPOLLO_STATE_IDLE1
		end
		return state
	end
		
	-- PATROL TRANSITION:
	if state==TRIPOLLO_STATE_PATROL then
		if math.random()<=PATROL_TO_IDLE_CHANCE then
			log (myName.." CHANGED STATE TO IDLE")
			return TRIPOLLO_STATE_IDLE
		end
		if playerDistance<=myLOS then
			log (myName.." CHANGED STATE TO SURPRISE")
			return TRIPOLLO_STATE_SURPRISE
		end
		return state
	end
	
	-- FIND TRANSITIONS:
	if state==TRIPOLLO_STATE_FIND then
		if playerDistance>(myLOS) then
			log (myName.." CHANGED STATE TO FALSE ALARM")
			return TRIPOLLO_STATE_FALSE_ALARM
		elseif playerDistance<(myLOS/3) then
			log (myName.." CHANGED STATE TO ALERT")
			return TRIPOLLO_STATE_ALERT	
		end
	end
	
	-- CHASE TRANSITIONS
	if state==TRIPOLLO_STATE_CHASE then
		local meleeRange =  pTripollo:getMeleeRange()

		log ("PLAYER DISTANCE: "..playerDistance..", LOS: "..(myLOS/3)..", Melée range: "..meleeRange)
		if playerDistance>=(myLOS/3) then
			log (myName.." CHANGED STATE TO TIRED")
			return TRIPOLLO_STATE_TIRED
		elseif playerDistance<=meleeRange then
			log (myName.." CHANGED STATE TO ATTACK")
			return TRIPOLLO_STATE_ATTACK
		end
	end
	
	-- CALL TO CHASE TRANSITIONS
	if state == TRIPOLLO_STATE_CALL_TO_CHASE then
		if playerDistance<(myLOS/3) then
			log (myName.." CHANGED STATE TO CHASE")
			return TRIPOLLO_STATE_CHASE
		elseif playerDistance<(myLOS) then
			log (myName.." CHANGED STATE TO FIND")
			return TRIPOLLO_STATE_FIND
		elseif math.random() <  BACK_FROM_CALL_TO_CHASE_CHANCE then
			log (myName.." CHANGED STATE TO WHATEVER I WAS DOING")
			return pTripollo:getPreviousState()
		end
	end
	
	-- ATTACK TRANSITIONS
	
	-- FLEE TRANSITIONS
	if state == TRIPOLLO_STATE_FLEE and playerDistance>= (myLOS/3) then
		log (myName.." CHANGED STATE TO TREMBLING")
		return TRIPOLLO_STATE_TREMBLING
	end
	
	-- TREMBLING TRANSITIONS
	if state == TRIPOLLO_STATE_TREMBLING then
		if any:getHP()==1 or pTripollo:getNeighboursInRange(NEIGHBOURS_RANGE)>0 then
			log (myName.." CHANGED STATE TO CHASE: GERONIMOOOOOO")
			return TRIPOLLO_STATE_CHASE
		elseif playerDistance<(myLOS/3) then
			log (myName.." CHANGED STATE TO FLEE")
			return TRIPOLLO_STATE_FLEE
		elseif math.random() < TREMBLING_TO_CALL_CHANCE then
			log (myName.." CHANGED STATE TO CALL_TO_ARMS")
			return TRIPOLLO_STATE_CALL_TO_ARMS		
		end
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
