<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
	<PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="1500" fields="X;Y;Z;W"></PROPERTY>
  
    <PROPERTY id="PhysicsComponentWeapon::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::radius" type="6" value="30" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::height" type="6" value="18" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::movementfactor" type="6" value="0.01" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::inflatespeed" type="6" value="55" fields="X;Y;Z;W"></PROPERTY>

  <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="10000" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="5" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="4" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::position_correction" type="6" value="0 -3 0" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::scale_correction" type="6" value="1 1 1" ></PROPERTY>

	<!-- Logic component attributes -->
	<PROPERTY id="LogicComponent::scriptFilename" type="7" value="bomb.lua"></PROPERTY>
	<PROPERTY id="LogicComponent::scriptFunction" type="7" value="bombLogic"></PROPERTY>
	<PROPERTY id="LogicComponent::defaultState" type="2" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::approachDistance" type="6" value="40"></PROPERTY>
	<PROPERTY id="LogicComponent::delay" type="6" value="0"></PROPERTY>

  <!-- Trajectory Component -->
  <PROPERTY id="TrajectoryComponent::twodimensions" type="2" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="TrajectoryComponent::defaultspeed" type="2" value="0.2" fields="X;Y;Z;W"></PROPERTY>

	<!-- TODO: add animations! -->
	  <!-- Animations -->
  <PROPERTY id="initialAnimation" type="7" value="bite_idle1_eani_Clip"></PROPERTY>
  <PROPERTY id="animation0::name" type="7" value="bite_idle1_eani_Clip"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation1::name" type="7" value="explote_eani_Clip" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation2::name" type="7" value="idle_eani_Clip" ></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation3::name" type="7" value="manual" ></PROPERTY>
  <PROPERTY id="animation3::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation4::name" type="7" value="walk1_Clip" ></PROPERTY>
  <PROPERTY id="animation4::loop" type="12" value="true" ></PROPERTY>

  <!-- Sounds -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="fart"></PROPERTY>

   
</CUSTOMPROPERTIES>