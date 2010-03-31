BB_STATE_IDLE=0
BB_STATE_PATROL=1
BB_STATE_CHASE=2
BB_STATE_ESCAPE=3
BB_STATE_ATTTACK=4
BB_STATE_DEAD=5

WORLD_DREAMS=0
WORLD_NIGHTMARES=1

function beeButterflyLogic(pBeeButterfly,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pBeeButterfly:getName()
	local playerDistance=pBeeButterfly:getPlayerDistance(myName)
	local myLOS = pBeeButterfly:getLineOfSight()
	local myHP = pBeeButterfly:getHP()
	local maxHPHalved = pBeeButterfly:getMaxHP()/2
	local world = getCurrentWorld()
	if (world==WORLD_DREAMS) then
		if state==BB_STATE_IDLE and playerDistance<myLOS then
			state=BB_STATE_PATROL
		elseif state==BB_STATE_PATROL then
			if playerDistance<=myLOS then
				state=BB_STATE_CHASE			
			elseif playerDistance<=myLOS/3 then
				state=BB_STATE_ATTACK
			end		
		elseif state==BB_STATE_ATTACK and myHP<maxHPHalved then
			state=BB_STATE_ESCAPE
		elseif state==BB_STATE_PATROL then
			state=BB_STATE_CHASE
		end
	end
	return state
end