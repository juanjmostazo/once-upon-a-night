COROUTINE_ONGOING=0

-- CLOCK CUTSCENES

CUTSCENE_1_CLOCK_INTRO="CLOCK_INTRO";
CUTSCENE_2_LEVEL_ENTRANCE="LEVEL_ENTRANCE_2";

-- CLOCK EVENTS

-- CUTSCENE 1: CLOCK_INTRO
function startCutScene1(pOny)
	addExecutedLevelEvent(CUTSCENE_1_CLOCK_INTRO);
	-- launchCutScene("cutscenes_level_clock.lua","cutScene1");
	return
end

function conditionCutScene1(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_1_CLOCK_INTRO);
end

function cutScene1(timer)
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_CLOCK_INTRO);
	-- setCameraTrajectory(CUTSCENE_1_CLOCK_INTRO);
	return COROUTINE_FINISHED
end

-- CUTSCENE 2: LEVEL_ENTRANCE
function startCutScene2(pOny)
	addExecutedLevelEvent(CUTSCENE_2_LEVEL_ENTRANCE);
	-- launchCutScene("cutscenes_level_clock.lua","cutScene2");
	return
end

function conditionCutScene2(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_2_LEVEL_ENTRANCE);
end

function cutScene2(timer)
	log ("CUTSCENE 2: ");
	log (CUTSCENE_2_LEVEL_ENTRANCE);
	setCameraTrajectory(CUTSCENE_2_LEVEL_ENTRANCE);
	while not isCameraTrajectoryFinished() do		
		coroutine.yield(COROUTINE_ONGOING)		
	end
	return COROUTINE_FINISHED
end