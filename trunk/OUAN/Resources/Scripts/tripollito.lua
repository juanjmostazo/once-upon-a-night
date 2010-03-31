TRIPOLLITO_STATE_IDLE=0
TRIPOLLITO_STATE_PATROL=1
TRIPOLLITO_STATE_CHASE=2
TRIPOLLITO_STATE_ESCAPE=3
TRIPOLLITO_STATE_ATTTACK=4
TRIPOLLITO_STATE_DEAD=5

function tripollitoLogic(pTripollito,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pTripollito:getName()
	local playerDistance=pTripollito:getPlayerDistance(myName)
	local myLOS = pTripollito:getLineOfSight()
	local myHP = pTripollito:getHP()
	local maxHPHalved = pTripollito:getMaxHP()/2
	
	if state==TRIPOLLITO_STATE_IDLE and playerDistance<=myLOS then
		state=TRIPOLLITO_STATE_PATROL
	elseif myHP==0 and myLives==0 then
		state=TRIPOLLITO_STATE_DEAD
	elseif state==TRIPOLLITO_STATE_PATROL then
		state=TRIPOLLITO_STATE_CHASE
	end
	return state
	
end