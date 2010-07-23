TRIPOLLO_NIGHTMARES_STATE_IDLE=0
TRIPOLLO_NIGHTMARES_STATE_PATROL=1
TRIPOLLO_NIGHTMARES_STATE_CHASE=2
TRIPOLLO_NIGHTMARES_STATE_ESCAPE=3
TRIPOLLO_NIGHTMARES_STATE_ATTTACK=4
TRIPOLLO_NIGHTMARES_STATE_DEAD=5

function tripolloLogic(pTripolloNightmares,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pTripolloNightmares:getName()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pTripolloNightmares:getLineOfSight()
	local myHP = pTripolloNightmares:getHP()
	local maxHPHalved = pTripolloNightmares:getMaxHP()/2
	
	if state==TRIPOLLO_NIGHTMARES_STATE_IDLE and playerDistance<=myLOS then
		state=TRIPOLLO_NIGHTMARES_STATE_PATROL
	elseif myHP==0 and myLives==0 then
		state=TRIPOLLO_NIGHTMARES_STATE_DEAD
	elseif state==TRIPOLLO_NIGHTMARES_STATE_PATROL then
		state=TRIPOLLO_NIGHTMARES_STATE_CHASE
	end
	return state
	
end
