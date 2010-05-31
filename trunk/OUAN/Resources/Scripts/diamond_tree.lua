DT_STATE_IDLE=0
DT_STATE_HIT=1
DT_STATE_RELOAD=2

DT_STATE_NAMES= {}
DT_STATE_NAMES[DT_STATE_IDLE]="IDLE"
DT_STATE_NAMES[DT_STATE_HIT]="HIT"
DT_STATE_NAMES[DT_STATE_RELOAD]="RELOAD"


function diamondTreeLogic(pDiamondTree,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pDiamondTree:getName()
	local delay=pDiamondTree:getDelay()	
	local timeSpent=pDiamondTree:getTimeSpent()
	local hit=pDiamondTree:hasTakenHit()	
	local reload = pDiamondTree:isReloadSet()
	local newState=state
	
	if state==DT_STATE_IDLE and hit then
		newState=DT_STATE_HIT
	elseif state==DT_STATE_HIT and reload then
		newState= DT_STATE_RELOAD
	elseif state==DT_STATE_RELOAD and timeSpent>=delay then
		newState=DT_STATE_IDLE		
	end	
	return newState
end
