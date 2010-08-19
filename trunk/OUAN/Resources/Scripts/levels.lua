-- CLOCK CUTSCENES

CUTSCENE_1_CLOCK_INTRO="CLOCK_INTRO";
CUTSCENE_2_LEVEL_ENTRANCE="LEVEL_ENTRANCE_2";

-- CHANGE LEVEL 2
function enterChangeLevel2(pOny)
	log ("enterChangeLevel2")
	changeLevel("Level2");
return
end

function conditionChangeLevel2(pOny)
	return hasExecutedLevelEvent(CUTSCENE_2_LEVEL_ENTRANCE);
end
