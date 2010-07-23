BOSS_STATE_IDLE=0
BOSS_STATE_CHASE=1
BOSS_STATE_STUNNED=2
BOSS_STATE_ATTTACK=4
BOSS_STATE_DEAD=5

function bossLogic(pBoss,state)
	-- local vars defined for legibility and to invoke as few c++ calls as possible
	local myName=pBoss:getName()
	local playerDistance=getPlayerDistance(myName)
	local myLOS = pBoss:getLineOfSight()
	local myHP = pBoss:getHP()
	local maxHPHalved = pBoss:getMaxHP()/2
	local stunnedTime = pBoss:getTimeStunned()
	local totalStunTime=5
	
	if state==BOSS_STATE_IDLE and playerDistance<myLOS then
		state=BOSS_STATE_CHASE
	elseif state==BOSS_STATE_STUNNED and stunnedTime>totalStunnedTime then
		if playerDistance<=myLOS then
			state=BOSS_STATE_CHASE			
		elseif playerDistance<=myLOS/3 then
			state=BOSS_STATE_ATTACK
		end		
	elseif state==BOSS_STATE_ATTACK and myHP<maxHPHalved then
		state=BOSS_STATE_ESCAPE
	end
	return state
end
