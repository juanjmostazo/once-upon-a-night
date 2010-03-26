STATE_IDLE=0
STATE_PATROL=1
STATE_CHASE=2
STATE_DEAD=3

function tripolloLogic(pTripollo,state)
	print(state)
	if state==STATE_IDLE and pTripollo:getNumLives()>0 then
		state=STATE_PATROL
	elseif pTripollo:getNumLives()==0 then
		state=STATE_DEAD
	elseif state==STATE_PATROL then
		state=STATE_CHASE
	end
	return state
end