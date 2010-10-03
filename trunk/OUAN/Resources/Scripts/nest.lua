NEST_STATE_IDLE=0
NEST_STATE_SHAKING=1
NEST_STATE_HATCHING=2

SP_STATE_NAMES= {}
SP_STATE_NAMES[NEST_STATE_IDLE]="IDLE"
SP_STATE_NAMES[NEST_STATE_SHAKING]="SHAKING"
SP_STATE_NAMES[NEST_STATE_HATCHING]="HATCHING"


function nestLogic(pNest,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pNest:getName()
	local playerDistance=getPlayerDistance(myName)
	local approachDistance=pNest:getApproachDistance()
	local delay=pNest:getDelay()
	local timeSpent=pNest:getTimeSpent()
	
	local newState=state
	
	if state==NEST_STATE_IDLE and playerDistance<=approachDistance then
		newState=NEST_STATE_SHAKING
	elseif state==NEST_STATE_SHAKING and timeSpent>=delay then
		newState=NEST_STATE_HATCHING
	end
	return newState
end
