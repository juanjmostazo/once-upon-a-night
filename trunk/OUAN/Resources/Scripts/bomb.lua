BOMB_STATE_IDLE=0
BOMB_STATE_HIT=1

BOMB_STATE_NAMES= {}
BOMB_STATE_NAMES[BOMB_STATE_IDLE]="IDLE"
BOMB_STATE_NAMES[BOMB_STATE_HIT]="HIT"

function bombLogic(pBomb,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pBomb:getName()
	local hit=pBomb:hasTakenHit()	
	local newState=state
	
	if state==BOMB_STATE_IDLE and hit then
		log("BOMB transitioning to hit")
		newState=BOMB_STATE_HIT
	elseif state==BOMB_STATE_HIT and not hit then
		log("BOMB transitioning to idle")	
		newState=BOMB_STATE_IDLE
	end
	return newState
end