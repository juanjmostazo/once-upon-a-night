TRIPOLLO_STATE_IDLE=0
TRIPOLLO_STATE_PATROL=1
TRIPOLLO_STATE_CHASE=2
TRIPOLLO_STATE_DEAD=3

function tripolloLogic(pTripollo,state)
	local myName=pTripollo:getName()	
	local myLives=pTripollo:getNumLives()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pTripollo:getLineOfSight()
	local myHP = pTripollo:getHP()
	
	if state==TRIPOLLO_STATE_IDLE and playerDistance<=myLOS then
		state=TRIPOLLO_STATE_PATROL
	elseif myHP==0 and myLives==0 then
		state=TRIPOLLO_STATE_DEAD
	elseif state==TRIPOLLO_STATE_PATROL then
		state=TRIPOLLO_STATE_CHASE
	end
	return state
end