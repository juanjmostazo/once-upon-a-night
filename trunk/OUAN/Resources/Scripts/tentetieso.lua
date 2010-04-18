TENTETIESO_STATE_IDLE=0
TENTETIESO_STATE_PATROL=1
TENTETIESO_STATE_CHASE=2
TENTETIESO_STATE_ESCAPE=3
TENTETIESO_STATE_ATTTACK=4
TENTETIESO_STATE_DEAD=5

function tentetiesoLogic(pTentetieso,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pTentetieso:getName()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pTentetieso:getLineOfSight()
	local myHP = pTentetieso:getHP()
	local maxHPHalved = pTentetieso:getMaxHP()/2
	
	if state==TENTETIESO_STATE_IDLE and playerDistance<60 then
		state=TENTETIESO_STATE_PATROL
	elseif state==TENTETIESO_STATE_PATROL then
		if playerDistance<=myLOS then
			state=TENTETIESO_STATE_CHASE			
		elseif playerDistance<=myLOS/3 then
			state=TENTETIESO_STATE_ATTACK
		end		
	elseif state==TENTETIESO_STATE_ATTACK and myHP<maxHPHalved then
		state=TENTETIESO_STATE_ESCAPE
	elseif state==TENTETIESO_STATE_PATROL then
		state=TENTETIESO_STATE_CHASE
	end
	return state
end
