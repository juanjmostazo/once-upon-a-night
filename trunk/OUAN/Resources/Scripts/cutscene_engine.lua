-- cutscenes.lua
function helloWorldSkip()
	--local any=getAny()
	--if any then
		--any:setOuternMovement(...)
	--end	
end

TRACK_TIME=10
COROUTINE_FINISHED=1
COROUTINE_ONGOING=0
SENTENCE1_TIME = 3
SENTENCE2_TIME = 3

function helloWorld(timer)
	setCameraTrajectory("LEVEL_START")
	while not isCameraTrajectoryFinished() do		
		coroutine.yield(COROUTINE_ONGOING)		
	end
	log ("Switching to tracking camera!!")
	setAnyTrackingCamera()
	timer:reset()
	local elapsedTime=timer:getTime()
	log("elapsedTime: "..elapsedTime)
	while(elapsedTime<TRACK_TIME) do
		elapsedTime=timer:getTime()
		log("elapsedTime: "..elapsedTime)	
		coroutine.yield(COROUTINE_ONGOING)
	end
	local any=getAny()
	if any then
		any:say("CUTSCENE_HELLOWORLD_INTRO")
	end
	timer:reset()
	elapsedTime=timer:getTime()
	while elapsedTime<SENTENCE1_TIME do
		elapsedTime=timer:getTime()
		coroutine.yield(COROUTINE_ONGOING)
	end
	if any then
		any:say("CUTSCENE_HELLOWORLD_SECOND")
	end
	timer:reset()
	elapsedTime=timer:getTime()
	while elapsedTime<SENTENCE2_TIME do
		elapsedTime=timer:getTime()
		coroutine.yield(COROUTINE_ONGOING)
	end
	if any then
		any:say("CUTSCENE_HELLOWORLD_LAST")
	end

	--stage 3: PC MOVEMENT:
	-- any:walkToXYZ(), any:runToXYZ() -> make Any move to a given position
	-- any:walkToObject("poster#0",25), any:runToObject() -> make Any move to a short distance of a given gameObject
	-- any:walkPath("pathname"), any:runPath("pathname") -> make Any follow a predefined trajectory
	--while not any:hasArrivedToObject("poster#0") do
	--	coroutine.yield(0)
	--end
	--any:changeAnimation("look")
	--while any:isPlayingAnimation("look") do
	--	coroutine.yield(0)
	--end				
	return COROUTINE_FINISHED
end
