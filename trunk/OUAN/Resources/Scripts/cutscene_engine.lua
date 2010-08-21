-- cutscenes.lua
function helloWorldSkip()
	--local any=getAny()
	--if any then
		--any:setOuternMovement(...)
	--end	
end

TRACK_TIME=10

SENTENCE1_TIME = 3
SENTENCE2_TIME = 3

function helloWorld(timer)
	setCameraTrajectory("LEVEL_START")
	while not isCameraTrajectoryFinished() and not skip() do		
		coroutine.yield(COROUTINE_ONGOING)		
	end
	log ("Switching to tracking camera!!")
	setAnyTrackingCamera()
	
	log ("narrative pause")
	busyWait(timer,TRACK_TIME)
	
--[[	timer:reset()
	local elapsedTime=timer:getTime()
	while(elapsedTime<TRACK_TIME and not skip()) do
		elapsedTime=timer:getTime()
		coroutine.yield(COROUTINE_ONGOING)
	end
--]]	

	local any=getAny()	
	timedSay(any,"CUTSCENE_HELLOWORLD_INTRO",1,timer,SENTENCE1_TIME)	
	log ("Any message 1")
	timedSay(any,"CUTSCENE_HELLOWORLD_SECOND",1,timer,SENTENCE2_TIME)
	log ("Any message 2")	
	timedSay(any,"CUTSCENE_HELLOWORLD_LAST", 0.5,timer,SENTENCE1_TIME)
	log ("Any message 3")
	
--[[	any:changeAnimation("die02")
	log ("Animation changed")
	while not skip() and not any:animLooping("die02") and not any:animFinished("die02") do
		coroutine.yield(COROUTINE_ONGOING)
	end
--]]	
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
