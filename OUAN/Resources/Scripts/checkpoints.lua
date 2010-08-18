-- CHECKPOINT 1: AFTER FIRST BRIDGE
function enterCheckPoint1(pOny)
	log ("enterCheckPoint1")
	setCheckPoint("CheckPoint1",1);
return
end

function conditionCheckPoint1(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<1
end

-- CHECKPOINT 2: BOMBS PUZZLE START
function enterCheckPoint2(pOny)
	log ("enterCheckPoint2")
	setCheckPoint("CheckPoint2",2);
return
end

function conditionCheckPoint2(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<2
end

-- CHECKPOINT 3: BOMBS PUZZLE END
function enterCheckPoint3(pOny)
	log ("enterCheckPoint3")
	setCheckPoint("CheckPoint3",3);
return
end

function conditionCheckPoint3(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<3
end

-- CHECKPOINT 4: NOT USED!!!
function enterCheckPoint4(pOny)
	log ("enterCheckPoint4")
	setCheckPoint("CheckPoint4",4);
return
end

function conditionCheckPoint4(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<4
end

-- CHECKPOINT 5: NIGHT GOBLIN APPEARS / DEFEATED
function enterCheckPoint5(pOny)
	log ("enterCheckPoint5")
	setCheckPoint("CheckPoint5",5);
return
end

function conditionCheckPoint5(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<5
end

-- CHECKPOINT 6: TRIPOLLO'S PLATFORM COMPLETED
function enterCheckPoint6(pOny)
	log ("enterCheckPoint6")
	setCheckPoint("CheckPoint6",6);
return
end

function conditionCheckPoint6(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<6
end

-- CHECKPOINT 7: TENTETIESOS
function enterCheckPoint7(pOny)
	log ("enterCheckPoint7")
	setCheckPoint("CheckPoint7",7);
return
end

function conditionCheckPoint7(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<7
end

-- CHECKPOINT 8:
function enterCheckPoint8(pOny)
	log ("enterCheckPoint8")
	setCheckPoint("CheckPoint8",8);
return
end

function conditionCheckPoint8(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<8
end

-- CHECKPOINT 9:
function enterCheckPoint9(pOny)
	log ("enterCheckPoint9")
	setCheckPoint("CheckPoint9",9);
return
end

function conditionCheckPoint9(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<9
end

-- CHECKPOINT 10:
function enterCheckPoint10(pOny)
	log ("enterCheckPoint10")
	setCheckPoint("CheckPoint10",10);
return
end

function conditionCheckPoint10(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<10
end

