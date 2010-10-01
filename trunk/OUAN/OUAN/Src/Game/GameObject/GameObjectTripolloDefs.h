#ifndef GAMEOBJECTTRIPOLLODEFSH_H
#define GAMEOBJECTTRIPOLLODEFSH_H

namespace OUAN
{
	//State names
	const std::string TRIPOLLO_STATE_IDLE="TRIPOLLO_STATE_IDLE";
	const std::string TRIPOLLO_STATE_PATROL="TRIPOLLO_STATE_PATROL";
	const std::string TRIPOLLO_STATE_CHASE="TRIPOLLO_STATE_CHASE";
	const std::string TRIPOLLO_STATE_FIND="TRIPOLLO_STATE_FIND";
	const std::string TRIPOLLO_STATE_ATTACK="TRIPOLLO_STATE_ATTACK";
	const std::string TRIPOLLO_STATE_FLEE="TRIPOLLO_STATE_FLEE";
	const std::string TRIPOLLO_STATE_DEAD="TRIPOLLO_STATE_DEAD";
	const std::string TRIPOLLO_STATE_HIT="TRIPOLLO_STATE_HIT";
	const std::string TRIPOLLO_STATE_SURPRISE = "TRIPOLLO_STATE_SURPRISE";
	const std::string TRIPOLLO_STATE_FALSE_ALARM = "TRIPOLLO_STATE_FALSE_ALARM";
	const std::string TRIPOLLO_STATE_ALERT = "TRIPOLLO_STATE_ALERT";
	const std::string TRIPOLLO_STATE_TIRED = "TRIPOLLO_STATE_TIRED";
	const std::string TRIPOLLO_STATE_CALL_TO_ARMS = "TRIPOLLO_STATE_CALL_TO_ARMS";
	const std::string TRIPOLLO_STATE_TREMBLING = "TRIPOLLO_STATE_TREMBLING";
	const std::string TRIPOLLO_STATE_IDLE1 = "TRIPOLLO_STATE_IDLE1";
	const std::string TRIPOLLO_STATE_CALL_TO_CHASE = "TRIPOLLO_STATE_CALL_TO_CHASE";	
	const std::string TRIPOLLO_STATE_STATUE="TRIPOLLO_STATE_STATUE";

	//Animation names
	const std::string TRIPOLLO_ANIM_ALERT="alert";
	const std::string TRIPOLLO_ANIM_ATTACK_00="attack00";
	const std::string TRIPOLLO_ANIM_ATTACK_01="attack_01";
	const std::string TRIPOLLO_ANIM_CALL_TO_ARMS="call_to_arms";
	const std::string TRIPOLLO_ANIM_DIE="die";
	const std::string TRIPOLLO_ANIM_FALSE_ALARM="false_alarm";
	const std::string TRIPOLLO_ANIM_AFRAID="flee_afraid";
	const std::string TRIPOLLO_ANIM_HIT01="hit01";
	const std::string TRIPOLLO_ANIM_HIT02="hit02";
	const std::string TRIPOLLO_ANIM_IDLE="idle_00";	
	const std::string TRIPOLLO_ANIM_IDLE1="idle01";
	const std::string TRIPOLLO_ANIM_STATUE="rest";
	const std::string TRIPOLLO_ANIM_RUN="run";
	const std::string TRIPOLLO_ANIM_STUN="stun";
	const std::string TRIPOLLO_ANIM_SURPRISE="surprise";
	const std::string TRIPOLLO_ANIM_TIRED="tired";
	const std::string TRIPOLLO_ANIM_WALK="walk";
	const std::string TRIPOLLO_ANIM_WALK_FAST="walk_fast";

	const std::string TRIPOLLO_ANIM_NM_ALERT="alert";
	const std::string TRIPOLLO_ANIM_NM_ATTACK_00="attack00";
	const std::string TRIPOLLO_ANIM_NM_ATTACK_01="attack01";
	const std::string TRIPOLLO_ANIM_NM_DIE="die";
	const std::string TRIPOLLO_ANIM_NM_FALSE_ALARM="false_alarm";
	const std::string TRIPOLLO_ANIM_NM_AFRAID="flee_scared";
	const std::string TRIPOLLO_ANIM_NM_HIT01="hit01";
	const std::string TRIPOLLO_ANIM_NM_IDLE="idle00";	
	const std::string TRIPOLLO_ANIM_NM_IDLE1="idle01";
	const std::string TRIPOLLO_ANIM_NM_STATUE="rest";
	const std::string TRIPOLLO_ANIM_NM_RUN="run";
	const std::string TRIPOLLO_ANIM_NM_STUN="stunned";
	const std::string TRIPOLLO_ANIM_NM_SURPRISE="surprise";
	const std::string TRIPOLLO_ANIM_NM_TIRED="tired";
	const std::string TRIPOLLO_ANIM_NM_WALK="walk";
	const std::string TRIPOLLO_ANIM_NM_WALK_FAST="walk_fast";

	const std::string TRIPOLLO_ANIM_FNM_ALERT="alert_flying";
	const std::string TRIPOLLO_ANIM_FNM_DIVING_BEGIN="diving_begin";
	const std::string TRIPOLLO_ANIM_FNM_DIVING_BACK_TO_FLYING="diving_back_to_flying";
	const std::string TRIPOLLO_ANIM_FNM_DIVING_CLAW="diving_claw";
	const std::string TRIPOLLO_ANIM_FNM_DIE="fly_die";
	const std::string TRIPOLLO_ANIM_FNM_FALSE_ALARM="fly_false_alarm";
	const std::string TRIPOLLO_ANIM_FNM_HIT01="fly_hit";
	const std::string TRIPOLLO_ANIM_FNM_IDLE="flying_idle";	
	const std::string TRIPOLLO_ANIM_FNM_STATUE="rest_fly";
	const std::string TRIPOLLO_ANIM_FNM_RUN="flying_chase";
	const std::string TRIPOLLO_ANIM_FNM_SURPRISE="fly_surprise";
	const std::string TRIPOLLO_ANIM_FNM_TIRED="fly_tired";
	const std::string TRIPOLLO_ANIM_FNM_WALK="fly_loop";
	const std::string TRIPOLLO_ANIM_FNM_WALK_FAST="fly_search";

	//Should poses were used
	const std::string TRIPOLLO_ANIM_MANUAL="manual";

	//bones attach points
	const std::string HEAD_BONE_NAME="bone31";

	const std::string TRIPOLLO_SOUND_HIT="tripollo_hit";
	const std::string TRIPOLLO_SOUND_DIE="tripollo_die";
	const std::string TRIPOLLO_SOUND_EXPLODE="tripollo_explosion";
	const std::string TRIPOLLO_SOUND_SCRATCH="tripollo_scratch";
	const std::string TRIPOLLO_SOUND_WINGS="tripollo_wings";
	const std::string TRIPOLLO_SOUND_GRAZNIDO="tripollo_graznido";
	const std::string TRIPOLLO_SOUND_ATTACK="tripollo_attack";
	const std::string TRIPOLLO_SOUND_SURPRISE="tripollo_surprise";
	const std::string TRIPOLLO_SOUND_CALL_TO_ARMS="tripollo_call_to_arms";

	const std::string TRIPOLLO_ATTACK_PECK = "peck";
}

#endif