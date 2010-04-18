DRAGON_STATE_IDLE=0
DRAGON_STATE_CHASE=1
DRAGON_STATE_STUNNED=2
DRAGON_STATE_ATTTACK=4
DRAGON_STATE_DEAD=5

function dragonLogic(pDragon,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pDragon:getName()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pDragon:getLineOfSight()
	local myHP = pDragon:getHP()
	local maxHPHalved = pDragon:getMaxHP()/2
	local stunnedTime = pDragon:getTimeStunned()
	local totalStunTime=5
	
	if state==DRAGON_STATE_IDLE and playerDistance<myLOS then
		state=DRAGON_STATE_CHASE
	elseif state==DRAGON_STATE_STUNNED and stunnedTime>totalStunnedTime then
		if playerDistance<=myLOS then
			state=DRAGON_STATE_CHASE			
		elseif playerDistance<=myLOS/3 then
			state=DRAGON_STATE_ATTACK
		end		
	elseif state==DRAGON_STATE_ATTACK and myHP<maxHPHalved then
		state=DRAGON_STATE_ESCAPE
	end
	return state
end
