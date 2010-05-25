function goalEnterFunction(pOny)
	playMusic("SUCCESS")
	playSoundFromGameObject(pOny:getName(),"any_triumph")
	victory()
return
end

function goalEnterCondition(pOny)
	log ("CHECK CONDITION!!")
	return false
end