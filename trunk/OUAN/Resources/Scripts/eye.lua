EYE_STATE_IDLE=0
EYE_STATE_PATROL=1
EYE_STATE_CHASE=2
EYE_STATE_ESCAPE=3
EYE_STATE_ATTTACK=4
EYE_STATE_DEAD=5

function eyeLogic(pEye,state)
	print(state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pEye:getName()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pEye:getLineOfSight()
	local myHP = pEye:getHP()
	local maxHPHalved = pEye:getMaxHP()/2
	
	if state==EYE_STATE_IDLE and playerDistance<60 then
		state=EYE_STATE_PATROL
	elseif state==EYE_STATE_PATROL then
		if playerDistance<=myLOS then
			state=EYE_STATE_CHASE			
		elseif playerDistance<=myLOS/3 then
			state=EYE_STATE_ATTACK
		end		
	elseif state==EYE_STATE_ATTACK and myHP<maxHPHalved then
		state=EYE_STATE_ESCAPE
	elseif state==EYE_STATE_PATROL then
		state=EYE_STATE_CHASE
	end
	return state
end
