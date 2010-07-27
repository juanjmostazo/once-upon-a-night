PORTAL_STATE_IDLE=0
PORTAL_STATE_ONY_APPROACHING=1
PORTAL_STATE_HIT=2
PORTAL_STATE_CHANGING_WORLD=3

PORTAL_STATE_NAMES = {}
PORTAL_STATE_NAMES[PORTAL_STATE_IDLE]="IDLE"
PORTAL_STATE_NAMES[PORTAL_STATE_ONY_APPROACHING]="ONY_APPROACHING"
PORTAL_STATE_NAMES[PORTAL_STATE_HIT]="HIT"
PORTAL_STATE_NAMES[PORTAL_STATE_CHANGING_WORLD]="CHANGING_WORLD"

function portalLogic(pPortal,state)
	local myName=pPortal:getName()
	local approachDistance=pPortal:getApproachDistance()
	local hit=pPortal:hasTakenHit()
	local playerDistance=getPlayerDistance(myName)
	local cworld=isChangingWorld()
	local newState=state
	
	if state==PORTAL_STATE_IDLE then
		if playerDistance<=approachDistance then
			newState=PORTAL_STATE_ONY_APPROACHING
		end
	elseif state==PORTAL_STATE_ONY_APPROACHING and hit then
		newState=PORTAL_STATE_HIT
	elseif state==PORTAL_STATE_HIT and not hit then
		newState=PORTAL_STATE_CHANGING_WORLD
	elseif state==PORTAL_STATE_CHANGING_WORLD and hit then
		newState=PORTAL_STATE_HIT
	elseif state==PORTAL_STATE_CHANGING_WORLD and not cworld then
		if playerDistance<=approachDistance then
			newState=PORTAL_STATE_ONY_APPROACHING
		else
			newState=PORTAL_STATE_IDLE
		end
	end
	
--[[	if (state ~= newState) then
		log (myName .. " changed its state from " .. getStateName(state,PORTAL_STATE_NAMES) .. " to " .. getStateName(newState,PORTAL_STATE_NAMES))
	end
--]]
		
	return newState
end

