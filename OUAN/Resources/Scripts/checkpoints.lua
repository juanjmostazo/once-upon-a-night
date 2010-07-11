-- CHECKPOINT 1
function enterCheckPoint1(pOny)
	log ("enterCheckPoint1")
	setCheckPoint("StaticCamera#tower1_3",1);
return
end

function conditionCheckPoint1(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<1
end

-- CHECKPOINT 2
function enterCheckPoint2(pOny)
	log ("enterCheckPoint2")
	setCheckPoint("StaticCamera#towerback1",2);
return
end

function conditionCheckPoint2(pOny)
    local checkpointNumber=getCheckPointNumber();
	return checkpointNumber<2
end
