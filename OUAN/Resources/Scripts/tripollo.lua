TRIPOLLO_STATE_IDLE = 0
TRIPOLLO_STATE_PATROL = 1
TRIPOLLO_STATE_CHASE = 2
TRIPOLLO_STATE_ATTACK = 3
TRIPOLLO_STATE_FLEE = 4
TRIPOLLO_STATE_DEAD = 5

TRIPOLLO_STATE_NAMES= {}
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_IDLE]="IDLE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_PATROL]="PATROL"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_CHASE]="CHASE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_ATTACK]="ATTACK"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_FLEE]="FLEE"
TRIPOLLO_STATE_NAMES[TRIPOLLO_STATE_DEAD]="DEAD"

TRIPOLLO_STATE_NAME_VOID="Invalid!"

function getStateName(state)
	local retVal
	if TRIPOLLO_STATE_NAMES[state] then
		retVal=TRIPOLLO_STATE_NAMES[state]
	else
		retVal=TRIPOLLO_STATE_NAME_VOID
	end
	return retVal
end

function tripolloLogic(pTripollo,state)
	local myName=pTripollo:getName()	
	local myLives=pTripollo:getNumLives()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pTripollo:getLineOfSight()
	local myHP = pTripollo:getHP()
	
	local newState=state
	
	if state==TRIPOLLO_STATE_IDLE and playerDistance<=myLOS then
		newState=TRIPOLLO_STATE_PATROL
	elseif state==TRIPOLLO_STATE_PATROL then
		if playerDistance>myLOS then
			newState=TRIPOLLO_STATE_IDLE
		elseif playerDistance<(myLOS/2) then
			newState=TRIPOLLO_STATE_CHASE
		end
	elseif state==TRIPOLLO_STATE_CHASE then
		if playerDistance>=(myLOS/2) then
			newState=TRIPOLLO_STATE_PATROL
		end
	elseif myHP==0 and myLives==0 then
		newState=TRIPOLLO_STATE_DEAD
	end
	if (state ~= newState) then
		log (pTripollo:getName() .. " changed its state from " .. getStateName(state) .. " to " .. getStateName(newState))
	end
	return newState
end