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
	return checkpointNumber<30;
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

-- CHECKPOINT 6: TRIPOLLO'S PLATFORM COMPLETED
function enterCheckPoint6(pOny)
	log ("enterCheckPoint6");
	setCheckPoint("CheckPoint6",60);
return
end

function conditionCheckPoint6(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<60;
end

-- CHECKPOINT 7: TENTETIESOS
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

