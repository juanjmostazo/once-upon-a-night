SWITCH_STATE_OFF=0
SWITCH_STATE_PUSHABLE=1
SWITCH_STATE_PUSHED=2

SWITCH_STATE_NAMES = {}
SWITCH_STATE_NAMES[SWITCH_STATE_OFF]="OFF"
SWITCH_STATE_NAMES[SWITCH_STATE_PUSHABLE]="PUSHABLE"
SWITCH_STATE_NAMES[SWITCH_STATE_PUSHED]="PUSHED"

function switchLogic(pSwitch,state)

	local myName=pSwitch:getName()
	local hit=pSwitch:hasTakenHit()
	local newState=state
	
	if state==SWITCH_STATE_OFF then
	elseif state==SWITCH_STATE_PUSHABLE and hit then
		newState=SWITCH_STATE_PUSHED
	elseif state==SWITCH_STATE_PUSHED then
	end
	
--[[	if (state ~= newState) then
		log (myName .. " changed its state from " .. getStateName(state,SWITCH_STATE_NAMES) .. " to " .. getStateName(newState,PORTAL_STATE_NAMES))
	end
--]]
		
	return newState
end

