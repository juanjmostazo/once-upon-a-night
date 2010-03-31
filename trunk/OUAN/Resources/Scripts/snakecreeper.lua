SS_STATE_IDLE=0
SS_STATE_PATROL=1
SS_STATE_CHASE=2
SS_STATE_ESCAPE=3
SS_STATE_ATTTACK=4
SS_STATE_DEAD=5

function snakeCreeperLogic(pSnakeCreeper,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pSnakeCreeper:getName()
	local playerDistance=pSnakeCreeper:getPlayerDistance(myName)
	local myLOS = pSnakeCreeper:getLineOfSight()
	local myHP = pSnakeCreeper:getHP()
	local maxHPHalved = pSnakeCreeper:getMaxHP()/2
	
	if state==SS_STATE_IDLE and playerDistance<myLOS then
		state=SS_STATE_PATROL
	elseif state==SS_STATE_PATROL then
		if playerDistance<=myLOS then
			state=SS_STATE_CHASE			
		elseif playerDistance<=myLOS/3 then
			state=SS_STATE_ATTACK
		end		
	elseif state==SS_STATE_ATTACK and myHP<maxHPHalved then
		state=SS_STATE_ESCAPE
	elseif state==SS_STATE_PATROL then
		state=SS_STATE_CHASE
	end
	return state
end