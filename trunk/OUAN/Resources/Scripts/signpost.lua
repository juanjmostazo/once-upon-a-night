SIGN_STATE_IDLE=0
SIGN_STATE_HIT=1

SIGN_STATE_NAMES= {}
SIGN_STATE_NAMES[SIGN_STATE_IDLE]="IDLE"
SIGN_STATE_NAMES[SIGN_STATE_HIT]="HIT"

function signpostLogic(pSignpost,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pSignpost:getName()
	local hit=pSignpost:hasTakenHit()	
	local newState=state
	
	if state==SIGN_STATE_IDLE and hit then
		log("signpost transitioning to hit")
		newState=SIGN_STATE_HIT
	elseif state==SIGN_STATE_HIT and not hit then
		log("signpost transitioning to idle")	
		newState=SIGN_STATE_IDLE
	end
	return newState
end
