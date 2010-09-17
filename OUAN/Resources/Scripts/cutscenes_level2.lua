-- LEVEL 2 CUTSCENES

CUTSCENE_1_LEVEL_START="LEVEL_START";
CUTSCENE_1_1_PLATFORM_TO_MOUNTAIN_1="PLATFORM_TO_MOUNTAIN_1";
CUTSCENE_2_FIRST_CHANGE_WORLD="FIRST_CHANGE_WORLD";
CUTSCENE_2_FIRST_CHANGE_WORLD_1="FIRST_CHANGE_WORLD#1";
CUTSCENE_2_FIRST_CHANGE_WORLD_2="FIRST_CHANGE_WORLD#2";
CUTSCENE_3_BOMBS_PUZZLE_START="BOMBS_PUZZLE_START";
CUTSCENE_3_BOMBS_PUZZLE_START_1="BOMBS_PUZZLE_START#1";
CUTSCENE_3_BOMBS_PUZZLE_START_2="BOMBS_PUZZLE_START#2";
CUTSCENE_3_BOMBS_PUZZLE_START_3="BOMBS_PUZZLE_START#3";
CUTSCENE_4_BOMBS_PUZZLE_END="BOMBS_PUZZLE_END";
CUTSCENE_5_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_6_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_7_1_TRIPOLLOS_PLATFORM="1_TRIPOLLOS_PLATFORM";
CUTSCENE_7_2_TRIPOLLOS_PLATFORM="2_TRIPOLLOS_PLATFORM";
CUTSCENE_7_3_TRIPOLLOS_PLATFORM="3_TRIPOLLOS_PLATFORM";
CUTSCENE_8_TRIPOLLO_STATUES="TRIPOLLO_STATUES";
CUTSCENE_9_FINAL_BOSS_START="FINAL_BOSS_START";
CUTSCENE_10_FINAL_BOSS_END="FINAL_BOSS_END";

-- LEVEL 2 EVENTS
EVENT_FIRST_CHANGE_WORLD_ACTIVATED="FIRST_CHANGE_WORLD_ACTIVATED";
BOMB_EXPLODED_NEAR_BRIGDGE_ROCK="BOMB_EXPLODED_NEAR_BRIGDGE_ROCK";
NIGHT_GOBLIN_DEFEATED="NIGHT_GOBLIN_DEFEATED";
TRIPOLLO_1_SWITCH_ACTIVATED="TRIPOLLO_1_SWITCH_ACTIVATED";
TRIPOLLO_2_SWITCH_ACTIVATED="TRIPOLLO_2_SWITCH_ACTIVATED";
TRIPOLLO_3_SWITCH_ACTIVATED="TRIPOLLO_3_SWITCH_ACTIVATED";
FINAL_BOSS_DEFEATED="FINAL_BOSS_DEFEATED";
TRIPOLLO_PLATFORM_PUZZLE_END="TRIPOLLO_PLATFORM_PUZZLE_END";

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

function cutScene1(timer)
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_LEVEL_START);
	local any=getAny()
	
	setCameraTrajectory(CUTSCENE_1_LEVEL_START,false,false)	
	trajectoryCamWait()
	timedMessage(any,"LEVEL_START#0",5,timer,3);
	timedMessage(any,"LEVEL_START#1",5,timer,3);
	timedMessage(any,"LEVEL_START#2",5,timer,3);
	timedMessage(any,"LEVEL_START#3",5,timer,3);
	
	setMyReturningToGameTransition(false);
	return COROUTINE_FINISHED
end

-- CUTSCENE 1_1: PLATFORM_TO_MOUNTAIN_1
function startCutScene1_1(pOny)
	addExecutedLevelEvent(CUTSCENE_1_1_PLATFORM_TO_MOUNTAIN_1);
	log ("CUTSCENE 1_1: ");
	log (CUTSCENE_1_1_PLATFORM_TO_MOUNTAIN_1);
	launchCutScene("cutscenes_level2.lua","cutScene1_1");
	return
end

function conditionCutScene1_1(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_1_1_PLATFORM_TO_MOUNTAIN_1);
end

function cutScene1_1(timer)
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_LEVEL_START);
	local any=getAny()
	
	setCameraTrajectory(CUTSCENE_1_1_PLATFORM_TO_MOUNTAIN_1,false,true)	
	trajectoryCamWait()
	busyWait(timer,5);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 2: FIRST CHANGE WORLD
function startCutScene2(pOny)
	log ("CUTSCENE 2 START");
	addExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD);
	launchCutScene("cutscenes_level2.lua","cutScene2");

	return
end

function conditionCutScene2(pOny)
	log ("CUTSCENE 2 CONDITION TRIGGER");
	return not hasExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD) and hasExecutedLevelEvent(EVENT_FIRST_CHANGE_WORLD_ACTIVATED);
end

function cutScene2(timer)
	log ("CUTSCENE 2: ");
	log (CUTSCENE_2_FIRST_CHANGE_WORLD);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_2_FIRST_CHANGE_WORLD_1,false,true);
	trajectoryCamWait();
	timedMessage(any,"FIRST_CHANGE_WORLD#0",5,timer,5);
	timedMessage(any,"FIRST_CHANGE_WORLD#1",5,timer,5);
	timedMessage(any,"FIRST_CHANGE_WORLD#2",5,timer,5);

	changeWorld(OUAN_WORLD_NIGHTMARES);
	setCameraTrajectory(CUTSCENE_2_FIRST_CHANGE_WORLD_2,false,true);
	trajectoryCamWait();
	timedMessage(any,"FIRST_CHANGE_WORLD#3",5,timer,5);
	timedMessage(any,"FIRST_CHANGE_WORLD#4",5,timer,5);
	timedMessage(any,"FIRST_CHANGE_WORLD#5",5,timer,5);
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 3: BOMBS PUZZLE START
function startCutScene3(pOny)
	addExecutedLevelEvent(CUTSCENE_3_BOMBS_PUZZLE_START);
    launchCutScene("cutscenes_level2.lua","cutScene3");
	return
end

function conditionCutScene3(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_3_BOMBS_PUZZLE_START) and getCheckPointNumber()>=20;
end

function cutScene3(timer)
	log ("CUTSCENE 3: ");
	log (CUTSCENE_3_BOMBS_PUZZLE_START);
	local any=getAny()	
	local cryking=getCryKing()
	
	cryking:changeAnimation("speak_loop1_Clip")
	
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_1,false,true)	
	trajectoryCamWait();
	timedMessage(any,"BOMBS_PUZZLE_START#0",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#1",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#2",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#3",5,timer,5);
	initBombPuzzle();
	timedMessage(any,"BOMBS_PUZZLE_START#4",5,timer,5);
	busyWait(timer,5);
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_2,false,false)
	timedMessage(any,"BOMBS_PUZZLE_START#4",5,timer,5);
	trajectoryCamWait();
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_3,false,false)	
	trajectoryCamWait();
	timedMessage(any,"BOMBS_PUZZLE_START#5",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#6",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#7",5,timer,5);
	
	cryking:changeAnimation("idle03_Clip");
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end


-- CUTSCENE 4: BOMBS PUZZLE END
function startCutScene4(pOny)
	addExecutedLevelEvent(CUTSCENE_4_BOMBS_PUZZLE_END);
	launchCutScene("cutscenes_level2.lua","cutScene4");
	return
end

function conditionCutScene4(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_4_BOMBS_PUZZLE_END) and hasExecutedLevelEvent(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK);
end

function cutScene4(timer)
	log ("CUTSCENE 4: ");
	log (CUTSCENE_4_BOMBS_PUZZLE_END);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_3,false,false);
	trajectoryCamWait();
	busyWait(timer,5);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
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
	if hasExecutedLevelEvent(TRIPOLLO_1_SWITCH_ACTIVATED) and not hasExecutedLevelEvent(CUTSCENE_7_1_TRIPOLLOS_PLATFORM) then
		log ("CUTSCENE 7 (1): ");
		log (CUTSCENE_7_1_TRIPOLLOS_PLATFORM);
		addExecutedLevelEvent(CUTSCENE_7_1_TRIPOLLOS_PLATFORM);
		launchCutScene("cutscenes_level2.lua","cutScene7_1");
	elseif hasExecutedLevelEvent(TRIPOLLO_2_SWITCH_ACTIVATED) and not hasExecutedLevelEvent(CUTSCENE_7_2_TRIPOLLOS_PLATFORM) then
		log ("CUTSCENE 7 (2): ");
		log (CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
		addExecutedLevelEvent(CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
		launchCutScene("cutscenes_level2.lua","cutScene7_2");
	elseif hasExecutedLevelEvent(TRIPOLLO_3_SWITCH_ACTIVATED) and not hasExecutedLevelEvent(CUTSCENE_7_3_TRIPOLLOS_PLATFORM) then
		log ("CUTSCENE 7 (3): ");
		log (CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
		addExecutedLevelEvent(CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
		launchCutScene("cutscenes_level2.lua","cutScene7_3");
	end
	return
end

function conditionCutScene7(pOny)
	return true;
end

function cutScene7_1(timer)
	log ("CUTSCENE 7_1: ");
	log (CUTSCENE_7_1_TRIPOLLOS_PLATFORM);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_7_1_TRIPOLLOS_PLATFORM,false,true);
	trajectoryCamWait();
	busyWait(timer,5);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

function cutScene7_2(timer)
	log ("CUTSCENE 7_2: ");
	log (CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_7_2_TRIPOLLOS_PLATFORM,false,true);
	trajectoryCamWait();
	busyWait(timer,5);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

function cutScene7_3(timer)
	log ("CUTSCENE 7_3: ");
	log (CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_7_3_TRIPOLLOS_PLATFORM,false,true);
	trajectoryCamWait();
	busyWait(timer,5);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end


-- CUTSCENE 8: TRIPOLLO_STATUES
function startCutScene8(pOny)
	addExecutedLevelEvent(CUTSCENE_8_TRIPOLLO_STATUES);
	launchCutScene("cutscenes_level2.lua","cutScene8");
	return
end

function conditionCutScene8(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_8_TRIPOLLO_STATUES) and getCheckPointNumber()>=70;
end

function cutScene8(timer)
	log ("CUTSCENE 8: ");
	log (CUTSCENE_8_TRIPOLLO_STATUES);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_8_TRIPOLLO_STATUES,false,true);
	trajectoryCamWait();
	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
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
