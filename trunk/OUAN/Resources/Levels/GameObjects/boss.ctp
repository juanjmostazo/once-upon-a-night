<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>

  <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="20" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="25" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="18" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::position_correction" type="6" value="0 0 0" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::scale_correction" type="6" value="1 1 1" ></PROPERTY>

  <PROPERTY id="LogicComponent::scriptFilename" type="7" value="boss.lua" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::scriptFunction" type="7" value="bossLogic" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::patrolTrajectory" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::defaultState" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::healthPoints" type="2" value="3" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::numLives" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::lineOfSight" type="2" value="150" fields="X;Y;Z;W"></PROPERTY> 

  <PROPERTY id="PhysicsComponentWeapon::mass" type="6" value="100" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentWeapon::radius" type="6" value="3" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentWeapon::height" type="6" value="6" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentWeapon::movementfactor" type="6" value="0.01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentWeapon::inflatespeed" type="6" value="8" fields="X;Y;Z;W"></PROPERTY>

  <!-- Trajectory Component -->
  <PROPERTY id="TrajectoryComponent::twodimensions" type="2" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="TrajectoryComponent::defaultspeed" type="2" value="0.4" fields="X;Y;Z;W"></PROPERTY>

	<!-- TODO: add animations! -->
	  <!-- Animations -->
  <PROPERTY id="initialAnimation" type="7" value="alert"></PROPERTY>
  <PROPERTY id="animation0::name" type="7" value="alert"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation1::name" type="7" value="attack00" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation2::name" type="7" value="die" ></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation3::name" type="7" value="flashlight_hit" ></PROPERTY>
  <PROPERTY id="animation3::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation4::name" type="7" value="leave" ></PROPERTY>
  <PROPERTY id="animation4::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation5::name" type="7" value="manual" ></PROPERTY>
  <PROPERTY id="animation5::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation6::name" type="7" value="pillow_hit" ></PROPERTY>
  <PROPERTY id="animation6::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation7::name" type="7" value="rest" ></PROPERTY>
  <PROPERTY id="animation7::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation8::name" type="7" value="run" ></PROPERTY>
  <PROPERTY id="animation8::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation9::name" type="7" value="run_pissed_off" ></PROPERTY>
  <PROPERTY id="animation9::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation10::name" type="7" value="sp_attack" ></PROPERTY>
  <PROPERTY id="animation10::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation11::name" type="7" value="stunned" ></PROPERTY>
  <PROPERTY id="animation11::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation12::name" type="7" value="tired" ></PROPERTY>
  <PROPERTY id="animation12::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation13::name" type="7" value="trot" ></PROPERTY>
  <PROPERTY id="animation13::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation14::name" type="7" value="war_cry" ></PROPERTY>
  <PROPERTY id="animation14::loop" type="12" value="false" ></PROPERTY>
</CUSTOMPROPERTIES>