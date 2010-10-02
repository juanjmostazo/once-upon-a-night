-- CLOCK CUTSCENES

-- LEVEL 2 CUTSCENES

CUTSCENE_1_LEVEL_START="LEVEL_START";
CUTSCENE_2_FIRST_CHANGE_WORLD="FIRST_CHANGE_WORLD";
CUTSCENE_3_BOMBS_PUZZLE_START="BOMBS_PUZZLE_START";
CUTSCENE_4_BOMBS_PUZZLE_END="BOMBS_PUZZLE_END";
CUTSCENE_5_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_6_NIGHT_GOBLIN_APPEARS="NIGHT_GOBLIN_APPEARS";
CUTSCENE_7_1_BOSSS_PLATFORM="1_BOSSS_PLATFORM";
CUTSCENE_7_2_BOSSS_PLATFORM="2_BOSSS_PLATFORM";
CUTSCENE_7_3_BOSSS_PLATFORM="3_BOSSS_PLATFORM";
CUTSCENE_8_BOSS_STATUES="BOSS_STATUES";
CUTSCENE_9_FINAL_BOSS_START="FINAL_BOSS_START";
CUTSCENE_10_FINAL_BOSS_END="FINAL_BOSS_END";

-- LEVEL 2 EVENTS
EVENT_FIRST_CHANGE_WORLD_ACTIVATED="FIRST_CHANGE_WORLD_ACTIVATED";
BOMB_EXPLODED_NEAR_BRIGDGE_ROCK="BOMB_EXPLODED_NEAR_BRIGDGE_ROCK";
NIGHT_GOBLIN_DEFEATED="NIGHT_GOBLIN_DEFEATED";
BOSS_1_SWITCH_ACTIVATED="BOSS_1_SWITCH_ACTIVATED";
BOSS_2_SWITCH_ACTIVATED="BOSS_2_SWITCH_ACTIVATED";
BOSS_3_SWITCH_ACTIVATED="BOSS_3_SWITCH_ACTIVATED";
FINAL_BOSS_DEFEATED="FINAL_BOSS_DEFEATED";

-- CHECKPOINT 1: AFTER FIRST BRIDGE
function enterCheckPoint1(pOny)
	log ("enterCheckPoint1");
	setCheckPoint("CheckPoint1",10);
return
end

function conditionCheckPoint1(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<10;
end

-- CHECKPOINT 2: BOMBS PUZZLE START
function enterCheckPoint2(pOny)
	log ("enterCheckPoint2");
	setCheckPoint("CheckPoint2",20);
return
end

function conditionCheckPoint2(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<20;
end

-- CHECKPOINT 3: BOMBS PUZZLE END
function enterCheckPoint3(pOny)
	log ("enterCheckPoint3");
	setCheckPoint("CheckPoint3",30);
return
end

function conditionCheckPoint3(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<30 and hasExecutedLevelEvent(CUTSCENE_4_BOMBS_PUZZLE_END);
end

-- CHECKPOINT 4: NOT USED!!!
function enterCheckPoint4(pOny)
	log ("enterCheckPoint4");
	setCheckPoint("CheckPoint4",40);
return
end

function conditionCheckPoint4(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<40;
end

-- CHECKPOINT 5: NIGHT GOBLIN APPEARS / DEFEATED
function enterCheckPoint5(pOny)
	log ("enterCheckPoint5");
	setCheckPoint("CheckPoint5",50);
return
end

function conditionCheckPoint5(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<50;
end

-- CHECKPOINT 55: BOOK
function enterCheckPoint55(pOny)
	log ("enterCheckPoint55");
	setCheckPoint("CheckPoint55",55);
return
end

function conditionCheckPoint55(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<55;
end


-- CHECKPOINT 6: BOSS'S PLATFORM START
function enterCheckPoint6(pOny)
	log ("enterCheckPoint6");
	setCheckPoint("CheckPoint6",60);
return
end

function conditionCheckPoint6(pOny)
    local checkpointNumber=getCheckPointNumber();
    return checkpointNumber<60;
end

-- CHECKPOINT 65: BOSS'S PLATFORM END
function enterCheckPoint65(pOny)
	log ("enterCheckPoint65");
	setCheckPoint("CheckPoint65",65);
return
end

function conditionCheckPoint65(pOny)
    local checkpointNumber=getCheckPointNumber();
    return checkpointNumber<65;
end

-- CHECKPOINT 7: BOSS_STATUES
function enterCheckPoint7(pOny)
	log ("enterCheckPoint7");
	setCheckPoint("CheckPoint7",70);
return
end

function conditionCheckPoint7(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<70;
end

-- CHECKPOINT 8: TOWER 3 ISLAND 2
function enterCheckPoint8(pOny)
	log ("enterCheckPoint8");
	setCheckPoint("CheckPoint8",80);
return
end

function conditionCheckPoint8(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<80;
end

-- CHECKPOINT 9: FINAL BOSS
function enterCheckPoint9(pOny)
	log ("enterCheckPoint9");
	setCheckPoint("CheckPoint9",90);
return
end

function conditionCheckPoint9(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<90;
end

-- CHECKPOINT 10: NOT USED
function enterCheckPoint10(pOny)
	log ("enterCheckPoint10");
	setCheckPoint("CheckPoint10",100);
return
end

function conditionCheckPoint10(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<100;
end

