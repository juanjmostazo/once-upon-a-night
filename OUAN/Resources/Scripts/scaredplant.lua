SP_STATE_IDLE=0
SP_STATE_ALERT=1
SP_STATE_CAUTION=2

SP_STATE_NAMES= {}
SP_STATE_NAMES[SP_STATE_IDLE]="IDLE"
SP_STATE_NAMES[SP_STATE_ALERT]="ALERT"
SP_STATE_NAMES[SP_STATE_CAUTION]="CAUTION"


function scaredplantLogic(pScaredPlant,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pScaredPlant:getName()
	local playerDistance=getPlayerDistance(myName)	
	local approachDistance=pScaredPlant:getApproachDistance()
	local delay=pScaredPlant:getDelay()
	local timeSpent=pScaredPlant:getTimeSpent()
	
	local newState=state
	
	if state==SP_STATE_IDLE and playerDistance<=approachDistance then
		newState=SP_STATE_ALERT
	elseif state==SP_STATE_ALERT then
		if playerDistance>approachDistance then
			newState=SP_STATE_CAUTION
		end
	elseif state==SP_STATE_CAUTION then
		if playerDistance<=approachDistance then
			newState=SP_STATE_ALERT			
		elseif timeSpent>=delay then		
			newState=SP_STATE_IDLE
		end		
	end	
	return newState
end
