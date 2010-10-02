-- State ids
BOSS_STATE_IDLE = 0
BOSS_STATE_PATROL = 1
BOSS_STATE_SURPRISE = 2
BOSS_STATE_FIND = 3
BOSS_STATE_FALSE_ALARM = 4
BOSS_STATE_ALERT = 5
BOSS_STATE_CHASE = 6
BOSS_STATE_TIRED = 7
BOSS_STATE_ATTACK = 8
BOSS_STATE_FLEE = 9
BOSS_STATE_DEAD = 10
BOSS_STATE_HIT = 11
BOSS_STATE_CALL_TO_ARMS = 12
BOSS_STATE_TREMBLING = 13
BOSS_STATE_IDLE1 = 14
BOSS_STATE_STATUE = 15
BOSS_STATE_CALL_TO_CHASE = 16
BOSS_STATE_DIVING_ATTACK=17

-- State names
BOSS_STATE_NAMES= {}
BOSS_STATE_NAMES[BOSS_STATE_IDLE]="IDLE"
BOSS_STATE_NAMES[BOSS_STATE_PATROL]="PATROL"
BOSS_STATE_NAMES[BOSS_STATE_FIND]="FIND"
BOSS_STATE_NAMES[BOSS_STATE_CHASE]="CHASE"
BOSS_STATE_NAMES[BOSS_STATE_ATTACK]="ATTACK"
BOSS_STATE_NAMES[BOSS_STATE_FLEE]="FLEE"
BOSS_STATE_NAMES[BOSS_STATE_DEAD]="DEAD"
BOSS_STATE_NAMES[BOSS_STATE_HIT]="HIT"
BOSS_STATE_NAMES[BOSS_STATE_SURPRISE]="SURPRISE"
BOSS_STATE_NAMES[BOSS_STATE_ALERT]="ALERT"
BOSS_STATE_NAMES[BOSS_STATE_FALSE_ALARM]="FALSE_ALARM"
BOSS_STATE_NAMES[BOSS_STATE_TIRED]="TIRED"
BOSS_STATE_NAMES[BOSS_STATE_CALL_TO_ARMS]="CALL_TO_ARMS"
BOSS_STATE_NAMES[BOSS_STATE_TREMBLING]="TREMBLING"
BOSS_STATE_NAMES[BOSS_STATE_STATUE]="STATUE"
BOSS_STATE_NAMES[BOSS_STATE_CALL_TO_CHASE]="CALL_TO_CHASE"
BOSS_STATE_NAMES[BOSS_STATE_DIVING_ATTACK]="DIVING_ATTACK"

-- CONSTANTS TO PERFORM SOME RANDOM STATE CHANGES
PATROL_TO_IDLE_CHANCE = 0.15
IDLE_TO_PATROL_CHANCE = 0.25
IDLE_TO_IDLE1_CHANCE = 0.4
TREMBLING_TO_CALL_CHANCE = 0.05
BACK_FROM_CALL_TO_CHASE_CHANCE = 0.1

-- Unused for the moment: Modify the value for the field on BOSS.ctp instead
-- key: (AttackComponent::attack0#attackRange)
MELEE_RANGE = 40

NEIGHBOURS_RANGE = 220


function BOSSLogic(pBOSS,state)

	local myName=pBOSS:getName()	
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pBOSS:getLineOfSight()
	local any = getAny()
	local world = getWorld();
	local isFlying = pBOSS:isFlying();
	
	--local newState=state
	
	-- DEATH CHECK
	if pBOSS:hasDied() then
		return BOSS_STATE_DEAD
	end
	
	-- STATUE CHECK
	if pBOSS:isStatueEnabled() then
		return BOSS_STATE_STATUE
	elseif state == BOSS_STATE_STATUE then
		return BOSS_STATE_IDLE
	end
	
	-- HIT CHECK
	if pBOSS:hasBeenHit() then
		return BOSS_STATE_HIT
	end	
	
	-- CALL RESPONSE
	
	if pBOSS:hasHeardCall() then
		--log (myName.." says: I've heard the call!")
		--log (myName.." : CHANGED STATE TO CALL_CHASE")
		return BOSS_STATE_CALL_TO_CHASE
	end
	
	-- SURPRISE CHECK
	if pBOSS:isSurpriseFinished() and state == BOSS_STATE_SURPRISE then
		return BOSS_STATE_FIND
	end
		
	-- FALSE ALARM CHECK
	if pBOSS:isFalseAlarmFinished() and state == BOSS_STATE_FALSE_ALARM then
		if pBOSS:hasPatrolTrajectory() then
			--log(myName.." : CHANGED STATE TO PATROL")
			return BOSS_STATE_PATROL
		else
			--log(myName.." doesn't have a patrol trajectory set: CHANGED STATE TO IDLE")
			return BOSS_STATE_IDLE
		end
	end
		
	-- ALERT CHECK
	if pBOSS:isAlertFinished() and state == BOSS_STATE_ALERT then
		return BOSS_STATE_CHASE
	end
	
	-- TIRED CHECK
	if pBOSS:isTiredFinished() and state == BOSS_STATE_TIRED then
		--log(myName.." : CHANGED STATE TO FIND")
		return BOSS_STATE_FIND
	end
	
	-- IDLE 1 CHECK
	if pBOSS:isIdle1Finished() and state == BOSS_STATE_IDLE1 then
		--log(myName.." : CHANGED STATE TO IDLE")
		return BOSS_STATE_IDLE
	end
	
	-- ATTACK CHECK
	if pBOSS:isAttackFinished() and state == BOSS_STATE_ATTACK then
		--log(myName.." : CHANGED STATE TO CHASE")
		return BOSS_STATE_CHASE	
	end
	
	-- CALL TO ARMS CHECK
	if pBOSS:isCallToArmsFinished() and state == BOSS_STATE_CALL_TO_ARMS then
		if pBOSS:callWasHeard() then
			--log(myName.." : Reinforcements are coming: CHANGED STATE TO ALERT")
			return BOSS_STATE_CHASE
		else
			--log(myName.." : Back to hiding in a corner: CHANGED STATE TO TREMBLING")
			return BOSS_STATE_TREMBLING
		end
	end
	
	-- HIT RECOVERY:
	if not pBOSS:hasBeenHit() and state == BOSS_STATE_HIT then
		if pBOSS:getHP()==1 and any:getHP()>1 and pBOSS:getNeighboursInRange(NEIGHBOURS_RANGE)==0 then
			--log(myName.." : Too weak to fight: CHANGING STATE TO FLEE")
			return BOSS_STATE_FLEE
		else
			local prevState=pBOSS:getPreviousState()
			--log (myName.." Going back to "..getStateName(prevState,BOSS_STATE_NAMES))
			return prevState
		end
	end
			
	-- IDLE TRANSITIONS:		
	if state==BOSS_STATE_IDLE then
		if playerDistance<=myLOS then
			--log (myName.." CHANGED STATE TO SURPRISE")
			return BOSS_STATE_SURPRISE
		elseif math.random()<=IDLE_TO_PATROL_CHANCE and pBOSS:hasPatrolTrajectory() then
			return BOSS_STATE_PATROL
		elseif math.random() <= IDLE_TO_IDLE1_CHANCE then
			return BOSS_STATE_IDLE1
		end
		return state
	end
		
	-- PATROL TRANSITION:
	if state==BOSS_STATE_PATROL then
		if math.random()<=PATROL_TO_IDLE_CHANCE then
			--log (myName.." CHANGED STATE TO IDLE")
			return BOSS_STATE_IDLE
		end
		if playerDistance<=myLOS then
			--log (myName.." CHANGED STATE TO SURPRISE")
			return BOSS_STATE_SURPRISE
		end
		return state
	end
	
	-- FIND TRANSITIONS:
	if state==BOSS_STATE_FIND then
		if playerDistance>(myLOS) then
			--log (myName.." CHANGED STATE TO FALSE ALARM")
			return BOSS_STATE_FALSE_ALARM
		elseif playerDistance<(myLOS/3.5) then
			--log (myName.." CHANGED STATE TO ALERT")
			return BOSS_STATE_ALERT	
		end
	end
	
	-- CHASE TRANSITIONS
	if state==BOSS_STATE_CHASE then
		local meleeRange =  pBOSS:getMeleeRange()

		--log ("PLAYER DISTANCE: "..playerDistance..", LOS: "..(myLOS/3)..", Melée range: "..meleeRange)
		if playerDistance>=(myLOS/3.5) then
			--log (myName.." CHANGED STATE TO TIRED")
			return BOSS_STATE_TIRED
		elseif pBOSS:hasHitOny() then
			--log (myName.." CHANGED STATE TO ATTACK")
			return BOSS_STATE_ATTACK
		end
	end
	
	-- CALL TO CHASE TRANSITIONS
	if state == BOSS_STATE_CALL_TO_CHASE then
		if playerDistance<(myLOS/3.5) then
			--log (myName.." CHANGED STATE TO CHASE")
			return BOSS_STATE_CHASE
		elseif playerDistance<(myLOS) then
			--log (myName.." CHANGED STATE TO FIND")
			return BOSS_STATE_FIND
		elseif math.random() <  BACK_FROM_CALL_TO_CHASE_CHANCE then
			--log (myName.." CHANGED STATE TO WHATEVER I WAS DOING")
			return pBOSS:getPreviousState()
		end
	end
	
	-- ATTACK TRANSITIONS
	
	-- FLEE TRANSITIONS
	if state == BOSS_STATE_FLEE and playerDistance>= (myLOS/3) then
		--log (myName.." CHANGED STATE TO TREMBLING")
		return BOSS_STATE_TREMBLING
	end
	
	-- TREMBLING TRANSITIONS
	if state == BOSS_STATE_TREMBLING then
		if any:getHP()==1 or pBOSS:getNeighboursInRange(NEIGHBOURS_RANGE)>0 then
			--log (myName.." CHANGED STATE TO CHASE: GERONIMOOOOOO")
			return BOSS_STATE_CHASE
		elseif playerDistance<(myLOS/3) then
			--log (myName.." CHANGED STATE TO FLEE")
			return BOSS_STATE_FLEE
		elseif math.random() < TREMBLING_TO_CALL_CHANCE then
			--log (myName.." CHANGED STATE TO CALL_TO_ARMS")
			return BOSS_STATE_CALL_TO_ARMS		
		end
	end

	return state

end
--[[
function BOSSNightmaresLogic(pBOSS,state)
	return state
end

function BOSSLogic(pBOSS,state)
	local world = getWorld()
	local newState = -1
	if world == OUAN_WORLD_DREAMS then
		log("Exec. BOSS dreams logic")
		newState = BOSSDreamsLogic(	pBOSS,state)
	else
		log("Exec. BOSS nightmares logic")
		newState = BOSSNightmaresLogic(pBOSS,state)
	end
	return newState
end
--]]	
