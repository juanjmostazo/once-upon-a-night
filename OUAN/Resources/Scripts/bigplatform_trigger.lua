-- Platform object
TRIGGER_NAME_BIG_PLATFORM="trigger-action#platform_big"
-- Portal name
PORTAL_NAME_BIG_PLATFORM="changeworld#platform_big"

-- Being a specific puzzle, it seems wiser and more intuitive to use directly
-- the names of the tripollos Any has to kill instead of setting a radius
-- and parsing the whole container
TRIPOLLO1_NAME="tripollo#0"
TRIPOLLO2_NAME="tripollo#11"
TRIPOLLO3_NAME="tripollo#12"
TRIPOLLO4_NAME="tripollo#13"

-- TODO Define a function to return the length of a LUA table, 
-- so we can get rid of the global var
NUM_TRIPOLLOS=4

TRIPOLLOS={}

function initTripollos()
	local varname=""
	for i=1,NUM_TRIPOLLOS do
		varname="TRIPOLLO"..i.."_NAME"
		TRIPOLLOS[i]=_G[varname]
	end
return
end

--initialize array.
initTripollos()

function areAllTripollosDisabled()
	local allDisabled=true
	local currentTripollo = nil
	local i=1
	while allDisabled and i<=NUM_TRIPOLLOS do
		currentTripollo = getObject(TRIPOLLOS[i])
		allDisabled = currentTripollo ==nil or not currentTripollo:enabled()
		i = i+1
	end
	return allDisabled
end

function bigPlatformEnterFunction(pOny)
	--Careful on casting!!
	local bigPlatform = getObject(PORTAL_NAME_BIG_PLATFORM)
	if bigPlatform ~= nil then		
		bigPlatform:setCurrentWorldVisible(areAllTripollosDisabled())
	else
		log("BOX TRIGGER - Big platform portal not found!!")
	end
return
end
