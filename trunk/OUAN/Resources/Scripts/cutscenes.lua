COROUTINE_ONGOING=0

-- CLOCK CUTSCENES

-- LEVEL 2 CUTSCENES

CUTSCENE_1_LEVEL_START="LEVEL_START";
CUTSCENE_2_FIRST_CHANGE_WORLD="FIRST_CHANGE_WORLD";

-- LEVEL 2 EVENTS
EVENT_FIRST_CHANGE_WORLD_ACTIVATED="FIRST_CHANGE_WORLD_ACTIVATED";

-- CUTSCENE 1: LEVEL START
function startCutScene1(pOny)
	log ("CUTSCENE 1: ");
	log (CUTSCENE_1_LEVEL_START);
	addExecutedLevelEvent(CUTSCENE_1_LEVEL_START);
	-- setCameraTrajectory(CUTSCENE_1_LEVEL_START);
return
end

function conditionCutScene1(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_1_LEVEL_START);
end

-- CUTSCENE 2: FIRST CHANGE WORLD
function startCutScene2(pOny)
	log ("CUTSCENE 2: ");
	log (CUTSCENE_2_FIRST_CHANGE_WORLD);
	addExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD);
	-- setCameraTrajectory(CUTSCENE_2_FIRST_CHANGE_WORLD);
return
end

function conditionCutScene2(pOny)
	return not hasExecutedLevelEvent(CUTSCENE_2_FIRST_CHANGE_WORLD);
end


-- CUTSCENE 3: BOMBS PUZZLE START
function startCutScene3(pOny)
	log ("CUTSCENE 3: BOMBS PUZZLE START");
return
end

function conditionCutScene3(pOny)
	return true;
end

-- CUTSCENE 4: BOMBS PUZZLE END
function startCutScene4(pOny)
	log ("CUTSCENE 4: BOMBS PUZZLE END");
return
end

function conditionCutScene4(pOny)
	return true;
end

-- CUTSCENE 5: NIGHT GOBLIN APPEARS
function startCutScene5(pOny)
	log ("CUTSCENE 5: NIGHT GOBLIN APPEARS");
return
end

function conditionCutScene5(pOny)
	return true;
end

-- CUTSCENE 6: NIGHT GOBLIN DEFEATED
function startCutScene6(pOny)
	log ("CUTSCENE 6: NIGHT GOBLIN DEFEATED");
return
end

function conditionCutScene6(pOny)
	return true;
end

-- CUTSCENE 7: TRIPOLLO'S PLATFORM 
function startCutScene7(pOny)
	log ("CUTSCENE 7: TRIPOLLO'S PLATFORM");
return
end

function conditionCutScene7(pOny)
	return true;
end

-- CUTSCENE 8: TENTETIESOS
function startCutScene8(pOny)
	log ("CUTSCENE 8: ");
return
end

function conditionCutScene8(pOny)
	return true;
end

-- CUTSCENE 9: FINAL BOSS START
function startCutScene9(pOny)
	log ("CUTSCENE 9: FINAL BOSS START");
return
end

function conditionCutScene9(pOny)
	return true;
end

-- CUTSCENE 10: FINAL BOSS END
function startCutScene10(pOny)
	log ("CUTSCENE 10: FINAL BOSS END");
return
end

function conditionCutScene10(pOny)
	return true;
end
