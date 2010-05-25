
STATE_NAME_VOID="Invalid"

function getStateName(state,stateNames)
	local retVal
	if stateNames[state] then
		retVal=stateNames[state]
	else
		retVal=STATE_NAME_VOID
	end
	return retVal
end

function wait(seconds)
	local _start = os.time()
	local _end = _start+seconds
	while (_end ~= os.time()) do
	end
end