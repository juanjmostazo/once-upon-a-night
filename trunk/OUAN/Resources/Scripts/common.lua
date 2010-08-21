
STATE_NAME_VOID="Invalid"


COROUTINE_FINISHED=1
COROUTINE_ONGOING=0


function getStateName(state,stateNames)
	local retVal
	if stateNames[state] then
		retVal=stateNames[state]
	else
		retVal=STATE_NAME_VOID
	end
	return retVal
end

function busyWait(timer,limit)
	timer:reset()
	elapsedTime=timer:getTime()
	while elapsedTime<limit and not skip() do
		elapsedTime=timer:getTime()
		coroutine.yield(COROUTINE_ONGOING)
	end
end

function timedSay(obj,msg, textLimit,timer, limit)
	if obj then
		obj:say(msg,textLimit)
	end
	busyWait(timer,limit)
end

function animationWait(obj,animationName)
	while not skip() and not obj:animFinished(animationName) do
		coroutine.yield(COROUTINE_ONGOING)
	end
end

function trajectoryCamWait()
	while not isCameraTrajectoryFinished() and not skip() do		
		coroutine.yield(COROUTINE_ONGOING)		
	end
end
	