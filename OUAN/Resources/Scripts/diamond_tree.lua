DT_STATE_IDLE=0
DT_STATE_HIT=1
DT_STATE_MAY_HIT=2
DT_STATE_DEPLETED=3

DT_STATE_NAMES= {}
DT_STATE_NAMES[DT_STATE_IDLE]="IDLE"
DT_STATE_NAMES[DT_STATE_MAY_HIT]="MAY_HIT"
DT_STATE_NAMES[DT_STATE_HIT]="HIT"
DT_STATE_NAMES[DT_STATE_DEPLETED]="DEPLETED"

nHits = {}


function diamondTreeLogic(pDiamondTree,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pDiamondTree:getName()
	local delay=pDiamondTree:getDelay()	
	local timeSpent=pDiamondTree:getTimeSpent()
	local hit=pDiamondTree:hasTakenHit()	
	local recovered=pDiamondTree:isRecovered()	
	local newState=state
	
	if state==DT_STATE_IDLE and hit then
		newState=DT_STATE_HIT
	elseif state==DT_STATE_HIT and recovered then
		if timeSpent<delay then
			log("READY TO HIT!")
			newState=DT_STATE_MAY_HIT
		else
			log ("DEPLETED:")
			--log (""..nHits[myName].."")
			newState=DT_STATE_DEPLETED
		end
	elseif state==DT_STATE_MAY_HIT and hit then
		newState=DT_STATE_HIT
	end	 
	return newState
end
