CP_STATE_IDLE=0
CP_STATE_PATROL=1
CP_STATE_CHASE=2
CP_STATE_ESCAPE=3
CP_STATE_ATTTACK=4
CP_STATE_DEAD=5

function carnivorousPlantLogic(pCarnivorousPlant,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pCarnivorousPlant:getName()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pCarnivorousPlant:getLineOfSight()
	local myHP = pCarnivorousPlant:getHP()
	local maxHPHalved = pCarnivorousPlant:getMaxHP()/2
	
	if state==CP_STATE_IDLE and playerDistance<myLOS then
		state=CP_STATE_PATROL
	elseif state==CP_STATE_PATROL then
		if playerDistance<=myLOS then
			state=CP_STATE_CHASE			
		elseif playerDistance<=myLOS/3 then
			state=CP_STATE_ATTACK
		end		
	elseif state==CP_STATE_ATTACK and myHP<maxHPHalved then
		state=CP_STATE_ESCAPE
	elseif state==CP_STATE_PATROL then
		state=CP_STATE_CHASE
	end
	return state
end
