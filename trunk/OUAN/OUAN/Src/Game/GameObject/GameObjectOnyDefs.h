#ifndef GAMEOBJECTONYDEFSH_H
#define GAMEOBJECTONYDEFSH_H

namespace OUAN
{
	//Default state
	const int ONY_STATE_IDLE=0;
	const int ONY_STATE_IDLE1=1;
	const int ONY_STATE_NAP=2;
	const int ONY_STATE_NAP_END=20;
	const int ONY_STATE_WALK=3;
	const int ONY_STATE_RUN=4;
	const int ONY_STATE_JUMP=5;
	const int ONY_STATE_FALL=6;
	const int ONY_STATE_ATTACK=7;
	const int ONY_STATE_COMBO1=8;
	const int ONY_STATE_COMBO2=9;
	const int ONY_STATE_HIT=10;
	const int ONY_STATE_DIE=11;
	const int ONY_STATE_APPROACH_PORTAL=12;
	const int ONY_STATE_VICTORY=13;

	const double ONY_IDLE2_CHANCE=0.015;

	//Animation names
	const std::string ONY_ANIM_IDLE01="idle01";
	const std::string ONY_ANIM_IDLE02="idle02";
	const std::string ONY_ANIM_WALK="walk";
	const std::string ONY_ANIM_RUN="run";
	const std::string ONY_ANIM_JUMP="jump02_pre";
	const std::string ONY_ANIM_JUMP02_START="jump02_pre";
	const std::string ONY_ANIM_JUMP02_KEEP="jump02_loop";
	const std::string ONY_ANIM_JUMP02_END="jump02_post";
	const std::string ONY_ANIM_JUMP01_START="jump01_pre";
	const std::string ONY_ANIM_JUMP01_KEEP="jump01_loop";
	const std::string ONY_ANIM_JUMP01_END="jump01_post";
	const std::string ONY_ANIM_ATTACK01="attack01";
	const std::string ONY_ANIM_ATTACK02="attack02";
	const std::string ONY_ANIM_ATTACK03="attack03";
	const std::string ONY_ANIM_CROUCH_START="crouch_pre";
	const std::string ONY_ANIM_CROUCH_KEEP="crouch_loop";
	const std::string ONY_ANIM_CROUCH_END="crouch_post";
	const std::string ONY_ANIM_DIE="die";
	const std::string ONY_ANIM_DRAW_PILLOW="draw_pillow";
	const std::string ONY_ANIM_HIDE_PILLOW01="hide_pillow01";
	const std::string ONY_ANIM_HIDE_PILLOW02="hide_pillow02";
	const std::string ONY_ANIM_HIDE_PILLOW03="hide_pillow03";
	const std::string ONY_ANIM_FRIGHT="fright";
	const std::string ONY_ANIM_FALL_START="fall_pre";
	const std::string ONY_ANIM_FALL_KEEP="fall_loop";
	const std::string ONY_ANIM_FALL_END="fall_post";
	const std::string ONY_ANIM_HIT01="hit01";
	const std::string ONY_ANIM_NAP_START="nap_pre";
	const std::string ONY_ANIM_NAP_KEEP="nap_loop";
	const std::string ONY_ANIM_NAP_END="nap_post";
	const std::string ONY_ANIM_SHOOT_CENTER="shoot_center";
	const std::string ONY_ANIM_VICTORY="victory";
	const std::string ONY_ANIM_VICTORY_START="victory_pre";
	const std::string ONY_ANIM_VICTORY_LOOP="victory_loop";
	const std::string ONY_ANIM_TICKLING_START="tickling_pre";
	const std::string ONY_ANIM_TICKLING_LOOP="tickling_loop";
	const std::string ONY_ANIM_MANUAL="manual";

	//SOUND DEFINITIONS
	const std::string ONY_SOUND_DIE="any_dies";
	const std::string ONY_SOUND_STEP_GRASS_00="any_step_grass_00";
	const std::string ONY_SOUND_STEP_GRASS_01="any_step_grass_01";
	const std::string ONY_SOUND_STEP_WATER_00="any_step_water_00";
	const std::string ONY_SOUND_STEP_WATER_01="any_step_water_01";
	const std::string ONY_SOUND_STEP_HARD_SURFACE_00="any_step_hard_surface_00";
	const std::string ONY_SOUND_STEP_HARD_SURFACE_01="any_step_hard_surface_01";
	const std::string ONY_SOUND_STEP_WOOD_00="any_step_wood_00";
	const std::string ONY_SOUND_STEP_WOOD_01="any_step_wood_01";
	const std::string ONY_SOUND_SCARED="any_scared";
	const std::string ONY_SOUND_FALLS="any_falls";
	const std::string ONY_SOUND_LAUGHTS="any_laughts";
	const std::string ONY_SOUND_PILLOW_ATTACK_VOICE="any_pillow_attack";
	const std::string ONY_SOUND_PUSH="any_push";
	const std::string ONY_SOUND_INTERESTED="any_interested";
	const std::string ONY_SOUND_TRIUMPH_A="any_triumph_a";
	const std::string ONY_SOUND_TRIUMPH_B="any_triumph_b";
	const std::string ONY_SOUND_HIT_A="any_takes_hit_a";
	const std::string ONY_SOUND_HIT_B="any_takes_hit_b";
	const std::string ONY_SOUND_TRIUMPH_LAUGHT="any_triumph_laught";
	const std::string ONY_SOUND_JUMP="any_jump";
	const std::string ONY_SOUND_BURN="any_burn";
	const std::string ONY_SOUND_EXHAUSTED="any_exhausted";
	const std::string ONY_SOUND_SURPRISE_A="any_surprise_a";
	const std::string ONY_SOUND_SURPRISE_B="any_surprise_b";
	const std::string ONY_SOUND_VERY_SCARED="any_very_scared";
	const std::string ONY_SOUND_SPLASH_00="any_splash_00";
	const std::string ONY_SOUND_SPLASH_01="any_splash_01";
	const std::string ONY_SOUND_SPLASH_02="any_splash_02";
	const std::string ONY_SOUND_CRASH_00="any_crash_00";
	const std::string ONY_SOUND_CRASH_01="any_crash_01";
	const std::string ONY_SOUND_CRASH_02="any_crash_02";
	const std::string ONY_SOUND_SLIDE="any_slide";
	const std::string ONY_SOUND_JUMP_ONTO_WATER="any_jump_onto_water";
	const std::string ONY_SOUND_JUMP_ONTO_GRASS="any_jump_onto_grass";
	const std::string ONY_SOUND_JUMP_ONTO_HARD_SURFACE="any_jump_onto_hard_surface";
	const std::string ONY_SOUND_JUMP_ONTO_WOOD="any_jump_onto_wood";

	const std::string ONY_SOUND_PILLOW_ATTACK_START="pillow_attack_start";
	const std::string ONY_SOUND_PILLOW_ATTACK_END="pillow_attack_end";
	const std::string ONY_SOUND_FLASHLIGHT_ATTACK_START="flashlight_attack_start";
	const std::string ONY_SOUND_FLASHLIGHT_ATTACK_END="flashlight_attack_end";
	const std::string ONY_SOUND_FLASHLIGHT_OVERHEAT="flashlight_overheat";
}
#endif