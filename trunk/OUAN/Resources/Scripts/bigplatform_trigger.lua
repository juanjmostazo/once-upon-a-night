-- Platform object
TRIGGER_NAME_BIG_PLATFORM="trigger-action#platform_big"
-- Portal name
PORTAL_NAME_BIG_PLATFORM="changeworld#platform_big"

-- Being a specific puzzle, it seems wiser and more intuitive to use directly
-- the names of the BOSSs Any has to kill instead of setting a radius
-- and parsing the whole container
BOSS1_NAME="BOSS#0"
BOSS2_NAME="BOSS#11"
BOSS3_NAME="BOSS#12"
BOSS4_NAME="BOSS#13"

-- TODO Define a function to return the length of a LUA table, 
-- so we can get rid of the global var
NUM_BOSSS=4

BOSSS={}

function initBOSSs()
	local varname=""
	for i=1,NUM_BOSSS do
		varname="BOSS"..i.."_NAME"
		BOSSS[i]=_G[varname]
	end
return
end

--initialize array.
initBOSSs()

function areAllBOSSsDisabled()
	local allDisabled=true
	local currentBOSS = nil
	local i=1
	while allDisabled and i<=NUM_BOSSS do
		currentBOSS = getObject(BOSSS[i])
		allDisabled = currentBOSS ==nil or not currentBOSS:enabled()
		i = i+1
	end
	return allDisabled
end

function bigPlatformEnterFunction(pOny)
	--Careful on casting!!
	local bigPlatform = getObject(PORTAL_NAME_BIG_PLATFORM)
	if bigPlatform ~= nil then		
		bigPlatform:setCurrentWorldVisible(areAllBOSSsDisabled())
	else
		log("BOX TRIGGER - Big platform portal not found!!")
	end
return
end
