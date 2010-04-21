PORTAL_STATE_IDLE=0
PORTAL_STATE_ONY_APPROACHING=1
PORTAL_STATE_ONY_MAY_ACTIVATE=2
PORTAL_STATE_CHANGING_WORLD=3

PORTAL_STATE_NAMES = {}
PORTAL_STATE_NAMES[PORTAL_STATE_IDLE]="IDLE"
PORTAL_STATE_NAMES[PORTAL_STATE_ONY_APPROACHING]="ONY_APPROACHING"
PORTAL_STATE_NAMES[PORTAL_STATE_ONY_MAY_ACTIVATE]="ONY_MAY_ACTIVATE"
PORTAL_STATE_NAMES[PORTAL_STATE_CHANGING_WORLD]="CHANGING_WORLD"

function portalLogic(pPortal,state)
	local myName=pPortal:getName()
	local approachDistance=pPortal:getApproachDistance()
	local activateDistance=pPortal:getActivateDistance()
	local playerDistance=getPlayerDistance(myName)
	local isActivated = pPortal:isActivated()
	
	local newState=state
	
	if state==PORTAL_STATE_IDLE then
		if playerDistance<=activateDistance then
			newState=PORTAL_STATE_ONY_MAY_ACTIVATE
		elseif playerDistance<=approachDistance then
			newState=PORTAL_STATE_ONY_APPROACHING
		end
	elseif state==PORTAL_STATE_ONY_APPROACHING then
		if playerDistance<=activateDistance then
			newState=PORTAL_STATE_ONY_MAY_ACTIVATE
		elseif playerDistance>approachDistance then		
			newState=PORTAL_STATE_IDLE
		end
	elseif state==PORTAL_STATE_ONY_MAY_ACTIVATE then
		if isActivated then
			log ("Now changing world!!")
			newState=PORTAL_STATE_CHANGING_WORLD
		elseif playerDistance>activateDistance then
			if playerDistance<=approachDistance then
				newState=PORTAL_STATE_ONY_APPROACHING
			else
				newState=PORTAL_STATE_IDLE
			end
		end
	elseif state==PORTAL_STATE_CHANGING_WORLD and not isActivated then
		if playerDistance<=activateDistance then
			newState=PORTAL_STATE_ONY_MAY_ACTIVATE
		elseif playerDistance<=approachDistance then
			newState=PORTAL_STATE_ONY_APPROACHING
		else
			newState=PORTAL_STATE_IDLE
		end
	end
	
	if (state ~= newState) then
		log (myName .. " changed its state from " .. getStateName(state,PORTAL_STATE_NAMES) .. " to " .. getStateName(newState,PORTAL_STATE_NAMES))
	end
		
	return newState
end

