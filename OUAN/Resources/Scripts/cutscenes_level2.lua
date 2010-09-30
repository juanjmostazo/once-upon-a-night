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
CUTSCENE_3_1_BOMBS_PUZZLE_PLACE_BOMB="BOMBS_PUZZLE_PLACE_BOMB";
CUTSCENE_4_BOMBS_PUZZLE_END="BOMBS_PUZZLE_END";
CUTSCENE_5_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_6_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_7_1_TRIPOLLOS_PLATFORM="1_TRIPOLLOS_PLATFORM";
CUTSCENE_7_2_TRIPOLLOS_PLATFORM="2_TRIPOLLOS_PLATFORM";
CUTSCENE_7_3_TRIPOLLOS_PLATFORM="3_TRIPOLLOS_PLATFORM";
CUTSCENE_8_TRIPOLLO_STATUES="TRIPOLLO_STATUES";
CUTSCENE_8_0_TRIPOLLO_STATUES_END="TRIPOLLO_STATUES_END";
CUTSCENE_8_1_PLATFORMS_TO_FINAL_BOSS="PLATFORMS_TO_FINAL_BOSS";
CUTSCENE_9_FINAL_BOSS_START="FINAL_BOSS_START";
CUTSCENE_10_1_FINAL_BOSS_HIT_1="FINAL_BOSS_HIT_1";
CUTSCENE_10_2_FINAL_BOSS_HIT_2="FINAL_BOSS_HIT_2";
CUTSCENE_10_3_FINAL_BOSS_HIT_3="FINAL_BOSS_HIT_3";

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
function cutScene1(timer)
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_LEVEL_START);
	addExecutedLevelEvent(CUTSCENE_1_LEVEL_START);
	local any=getAny()
	
	setCameraTrajectory(CUTSCENE_1_LEVEL_START,false,false)	
	trajectoryCamWait()
	timedMessage(any,"LEVEL_START#0",5,timer,6);
	timedMessage(any,"LEVEL_START#1",5,timer,6);
	
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
function cutScene2(timer)
	log ("CUTSCENE 2: ");
	log (CUTSCENE_2_FIRST_CHANGE_WORLD);
	addExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_2_FIRST_CHANGE_WORLD_1,false,true);
	trajectoryCamWait();
	timedMessage(any,"FIRST_CHANGE_WORLD#0",5,timer,4);
	timedMessage(any,"FIRST_CHANGE_WORLD#1",5,timer,7);
	timedMessage(any,"FIRST_CHANGE_WORLD#2",5,timer,4);

	changeWorld(OUAN_WORLD_NIGHTMARES);
	setCameraTrajectory(CUTSCENE_2_FIRST_CHANGE_WORLD_2,false,true);
	trajectoryCamWait();
	worldChangeWait();
	busyWait(timer,6);
	
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
	
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_1,false,true)	
	trajectoryCamWait();
	cryking:changeAnimation("cry_loop1_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#0",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#1",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#2",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#3",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#4",5,timer,5);
	cryking:changeAnimation("speak_loop1_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#5",5,timer,5);
	cryking:changeAnimation("idle03_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#6",5,timer,5);
	cryking:changeAnimation("speak_loop1_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#7",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#8",5,timer,5);
	cryking:changeAnimation("idle03_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#9",5,timer,5);
	cryking:changeAnimation("speak_loop1_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#10",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#11",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#12",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_START#13",5,timer,5);
	cryking:changeAnimation("idle02_Clip");
	timedMessage(any,"BOMBS_PUZZLE_START#14",5,timer,5);
	initBombPuzzle();
	timedMessage(any,"BOMBS_PUZZLE_START#15",5,timer,5);
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_2,false,false)
	trajectoryCamWait();
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_3,false,false)	
	trajectoryCamWait();
	busyWait(timer,5);

	cryking:changeAnimation("idle03_Clip");
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 3_1: BOMBS_PUZZLE_PLACE_BOMB
function startCutScene3_1(pOny)
	addExecutedLevelEvent(CUTSCENE_3_1_BOMBS_PUZZLE_PLACE_BOMB);
    launchCutScene("cutscenes_level2.lua","cutScene3_1");
	return
end

function conditionCutScene3_1(pOny)
	local bombDistance=getPlayerDistance("bomb#0");
	return not hasExecutedLevelEvent(CUTSCENE_3_1_BOMBS_PUZZLE_PLACE_BOMB) and bombDistance<=60;
end

function cutScene3_1(timer)
	log ("CUTSCENE 3_1: ");
	log (CUTSCENE_3_1_BOMBS_PUZZLE_PLACE_BOMB);
	local any=getAny()	
	local cryking=getCryKing()
	
	setCameraTrajectory(CUTSCENE_4_BOMBS_PUZZLE_END,false,true)	
	trajectoryCamWait();
	timedMessage(any,"BOMBS_PUZZLE_END#0",5,timer,5);
	timedMessage(any,"BOMBS_PUZZLE_END#1",5,timer,5);
	
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
	
	setCameraTrajectory(CUTSCENE_3_BOMBS_PUZZLE_START_3,false,true);
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
	busyWait(timer,14);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

function cutScene7_2(timer)
	log ("CUTSCENE 7_2: ");
	log (CUTSCENE_7_2_TRIPOLLOS_PLATFORM);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_7_2_TRIPOLLOS_PLATFORM,false,true);
	trajectoryCamWait();
	busyWait(timer,14);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

function cutScene7_3(timer)
	log ("CUTSCENE 7_3: ");
	log (CUTSCENE_7_3_TRIPOLLOS_PLATFORM);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_7_3_TRIPOLLOS_PLATFORM,false,true);
	trajectoryCamWait();
	busyWait(timer,14);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end


-- CUTSCENE 8: TRIPOLLO_STATUES
function cutScene8(timer)
	log ("CUTSCENE 8: ");
	log (CUTSCENE_8_TRIPOLLO_STATUES);
	local any=getAny()	
	addExecutedLevelEvent(CUTSCENE_8_TRIPOLLO_STATUES);
	
	setCameraTrajectory(CUTSCENE_8_TRIPOLLO_STATUES,false,true);
	trajectoryCamWait();
	changeWorld(OUAN_WORLD_NIGHTMARES);
	worldChangeWait();
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 8_0: TRIPOLLO_STATUES_END
function cutScene8_0(timer)
	log ("CUTSCENE 8_0: ");
	log (CUTSCENE_8_0_TRIPOLLO_STATUES_END);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_8_TRIPOLLO_STATUES,false,true);
	trajectoryCamWait();
	addExecutedLevelEvent(CUTSCENE_8_0_TRIPOLLO_STATUES_END);

	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 8_1: PLATFORMS_TO_FINAL_BOSS
function cutScene8_1(timer)
	log ("CUTSCENE 8: ");
	log (CUTSCENE_8_1_PLATFORMS_TO_FINAL_BOSS);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_8_1_PLATFORMS_TO_FINAL_BOSS,false,true);
	busyWait(timer,2);
	addExecutedLevelEvent(CUTSCENE_8_1_PLATFORMS_TO_FINAL_BOSS);
	trajectoryCamWait();
	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 9: FINAL BOSS START
function startCutScene9(pOny)
	addExecutedLevelEvent(CUTSCENE_9_FINAL_BOSS_START);
	launchCutScene("cutscenes_level2.lua","cutScene9");
	return
end

function conditionCutScene9(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_9_FINAL_BOSS_START) and getCheckPointNumber()>=90;
end

function cutScene9(timer)
	log ("CUTSCENE 9: ");
	log (CUTSCENE_9_FINAL_BOSS_START);
	local any=getAny()	
	
	setCameraTrajectory(CUTSCENE_9_FINAL_BOSS_START,false,true);
	trajectoryCamWait();
	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 10_1: CUTSCENE_10_1_FINAL_BOSS_HIT_1
function cutScene10_1(timer)
	log ("CUTSCENE 10_1: ");
	log (CUTSCENE_10_1_FINAL_BOSS_HIT_1);
	local any=getAny()	
	
	addExecutedLevelEvent(CUTSCENE_10_1_FINAL_BOSS_HIT_1);
	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 10_2: CUTSCENE_10_2_FINAL_BOSS_HIT_2
function cutScene10_2(timer)
	log ("CUTSCENE 10_2: ");
	log (CUTSCENE_10_2_FINAL_BOSS_HIT_2);
	local any=getAny()	
	
	addExecutedLevelEvent(CUTSCENE_10_2_FINAL_BOSS_HIT_2);
	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end

-- CUTSCENE 10_3: CUTSCENE_10_3_FINAL_BOSS_HIT_3
function cutScene10_3(timer)
	log ("CUTSCENE 10_3: ");
	log (CUTSCENE_10_3_FINAL_BOSS_HIT_3);
	local any=getAny()	
	
	addExecutedLevelEvent(CUTSCENE_10_3_FINAL_BOSS_HIT_3);
	setCameraTrajectory(CUTSCENE_10_3_FINAL_BOSS_HIT_3,false,true);
	trajectoryCamWait();
	busyWait(timer,3);
	
	setMyReturningToGameTransition(true);
	return COROUTINE_FINISHED
end