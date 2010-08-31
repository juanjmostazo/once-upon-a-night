-- LEVEL 2 CUTSCENES

CUTSCENE_1_LEVEL_START="LEVEL_START";
CUTSCENE_2_FIRST_CHANGE_WORLD="FIRST_CHANGE_WORLD";
CUTSCENE_3_BOMBS_PUZZLE_START="BOMBS_PUZZLE_START";
CUTSCENE_4_BOMBS_PUZZLE_END="BOMBS_PUZZLE_END";
CUTSCENE_5_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_6_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_7_1_TRIPOLLOS_PLATFORM="1_TRIPOLLOS_PLATFORM";
CUTSCENE_7_2_TRIPOLLOS_PLATFORM="2_TRIPOLLOS_PLATFORM";
CUTSCENE_7_3_TRIPOLLOS_PLATFORM="3_TRIPOLLOS_PLATFORM";
CUTSCENE_8_TENTETIESOS="TENTETIESOS";
CUTSCENE_9_FINAL_BOSS_START="FINAL_BOSS_START";
CUTSCENE_10_FINAL_BOSS_END="FINAL_BOSS_END";

-- LEVEL 2 EVENTS
EVENT_FIRST_CHANGE_WORLD_ACTIVATED="FIRST_CHANGE_WORLD_ACTIVATED";
BOMB_EXPLODED_NEAR_BRIGDGE_ROCK="BOMB_EXPLODED_NEAR_BRIGDGE_ROCK";
NIGHT_GOBLIN_DEFEATED="NIGHT_GOBLIN_DEFEATED";
TRIPOLLO_1_PLATFORM_DEFEATED="TRIPOLLO_1_PLATFORM_DEFEATED";
TRIPOLLO_2_PLATFORM_DEFEATED="TRIPOLLO_2_PLATFORM_DEFEATED";
TRIPOLLO_3_PLATFORM_DEFEATED="TRIPOLLO_3_PLATFORM_DEFEATED";
FINAL_BOSS_DEFEATED="FINAL_BOSS_DEFEATED";

-- CUTSCENE 1: LEVEL START
function startCutScene1(pOny)
	addExecutedLevelEvent(CUTSCENE_1_LEVEL_START);
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_LEVEL_START);
	launchCutScene("cutscenes_level2.lua","cutScene1");
	return
end

function conditionCutScene1(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_1_LEVEL_START);
end

TRACK_TIME=2

SENTENCE1_TIME = 3
SENTENCE2_TIME = 3

function cutScene1(timer)
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_LEVEL_START);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_1_LEVEL_START,false,false)	
	trajectoryCamWait()

	return COROUTINE_FINISHED
end

-- CUTSCENE 2: FIRST CHANGE WORLD
function startCutScene2(pOny)
	addExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD);
	launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene2(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD) and hasExecutedLevelEvent(EVENT_FIRST_CHANGE_WORLD_ACTIVATED);
end

function cutScene2(timer)
	log ("CUTSCENE 2: ");
	log (CUTSCENE_2_FIRST_CHANGE_WORLD);
	setCameraTrajectory(CUTSCENE_2_FIRST_CHANGE_WORLD,false,true);
	changeWorld(OUAN_WORLD_NIGHTMARES);
	trajectoryCamWait();
	setDefaultThirdPersonCamera(false);
	return COROUTINE_FINISHED
end

-- CUTSCENE 3: BOMBS PUZZLE START
function startCutScene3(pOny)
	log ("CUTSCENE 3: ");
	log (CUTSCENE_3_BOMBS_PUZZLE_START);
	addExecutedLevelEvent(CUTSCENE_3_BOMBS_PUZZLE_START);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene3(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_3_BOMBS_PUZZLE_START) and getCheckPointNumber()>=20;
end

-- CUTSCENE 4: BOMBS PUZZLE END
function startCutScene4(pOny)
	log ("CUTSCENE 4: ");
	log (CUTSCENE_4_BOMBS_PUZZLE_END);
	addExecutedLevelEvent(CUTSCENE_4_BOMBS_PUZZLE_END);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene4(pOny)
	--when bombs are implemented shold check if a bomb has exploded the rock
	return not hasExecutedLevelEvent(CUTSCENE_4_BOMBS_PUZZLE_END) and hasExecutedLevelEvent(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK);
end

-- CUTSCENE 5: NIGHT GOBLIN APPEARS
function startCutScene5(pOny)
	log ("CUTSCENE 5: ");
	log (CUTSCENE_5_NIGHT_GOBLIN_APPEARS);
	addExecutedLevelEvent(CUTSCENE_5_NIGHT_GOBLIN_APPEARS);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene5(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_5_NIGHT_GOBLIN_APPEARS) and getCheckPointNumber()>=50;
end

-- CUTSCENE 6: NIGHT GOBLIN DEFEATED
function startCutScene6(pOny)
	log ("CUTSCENE 6: ");
	log (CUTSCENE_6_NIGHT_GOBLIN_APPEARS);
	addExecutedLevelEvent(CUTSCENE_6_NIGHT_GOBLIN_APPEARS);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene6(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_6_NIGHT_GOBLIN_APPEARS) and hasExecutedLevelEvent(NIGHT_GOBLIN_DEFEATED);
end

-- CUTSCENE 7: TRIPOLLO'S PLATFORM 
function startCutScene7(pOny)
	if hasExecutedLevelEvent(TRIPOLLO_1_PLATFORM_DEFEATED) and not hasExecutedLevelEvent(CUTSCENE_7_1_TRIPOLLOS_PLATFORM) then
		log ("CUTSCENE 7 (1): ");
		log (CUTSCENE_7_1_TRIPOLLOS_PLATFORM);
		addExecutedLevelEvent(CUTSCENE_7_1_TRIPOLLOS_PLATFORM);
		-- launchCutScene("cutscenes_level2.lua","cutScene2");
	elseif hasExecutedLevelEvent(TRIPOLLO_2_PLATFORM_DEFEATED) and not hasExecutedLevelEvent(CUTSCENE_7_2_TRIPOLLOS_PLATFORM) then
		log ("CUTSCENE 7 (2): ");
		log (CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
		addExecutedLevelEvent(CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
		-- launchCutScene("cutscenes_level2.lua","cutScene2");
	elseif hasExecutedLevelEvent(TRIPOLLO_3_PLATFORM_DEFEATED) and not hasExecutedLevelEvent(CUTSCENE_7_3_TRIPOLLOS_PLATFORM) then
		log ("CUTSCENE 7 (3): ");
		log (CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
		addExecutedLevelEvent(CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
		-- launchCutScene("cutscenes_level2.lua","cutScene2");
	end
	return
end

function conditionCutScene7(pOny)
	return true;
end

-- CUTSCENE 8: TENTETIESOS
function startCutScene8(pOny)
	log ("CUTSCENE 8: ");
	log (CUTSCENE_8_TENTETIESOS);
	addExecutedLevelEvent(CUTSCENE_8_TENTETIESOS);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene8(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_8_TENTETIESOS) and getCheckPointNumber()>=70;
end

-- CUTSCENE 9: FINAL BOSS START
function startCutScene9(pOny)
	log ("CUTSCENE 9: ");
	log (CUTSCENE_9_FINAL_BOSS_START);
	addExecutedLevelEvent(CUTSCENE_9_FINAL_BOSS_START);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene9(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_9_FINAL_BOSS_START) and getCheckPointNumber()>=90;
end

-- CUTSCENE 10: FINAL BOSS END
function startCutScene10(pOny)
	log ("CUTSCENE 10: ");
	log (CUTSCENE_10_FINAL_BOSS_END);
	addExecutedLevelEvent(CUTSCENE_10_FINAL_BOSS_END);
	-- launchCutScene("cutscenes_level2.lua","cutScene2");
	return
end

function conditionCutScene10(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_10_FINAL_BOSS_END) and hasExecutedLevelEvent(FINAL_BOSS_DEFEATED);
end
