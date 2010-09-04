<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
	<PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="1500" fields="X;Y;Z;W"></PROPERTY>
  
    <PROPERTY id="PhysicsComponentWeapon::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::radius" type="6" value="30" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::height" type="6" value="18" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::movementfactor" type="6" value="0.01" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentWeapon::inflatespeed" type="6" value="55" fields="X;Y;Z;W"></PROPERTY>

    <PROPERTY id="PhysicsComponentSimpleBox::mass" type="6" value="100000" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentSimpleBox::length" type="9" value="8 8 8" fields="X;Y;Z;W"></PROPERTY>

	<!-- Logic component attributes -->
	<PROPERTY id="LogicComponent::scriptFilename" type="7" value="bomb.lua"></PROPERTY>
	<PROPERTY id="LogicComponent::scriptFunction" type="7" value="bombLogic"></PROPERTY>
	<PROPERTY id="LogicComponent::defaultState" type="2" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::approachDistance" type="6" value="40"></PROPERTY>
	<PROPERTY id="LogicComponent::delay" type="6" value="0"></PROPERTY>

	<!-- TODO: add animations! -->
	  <!-- Animations -->
  <PROPERTY id="animation0::name" type="7" value="manual"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation1::name" type="7" value="shake" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation2::name" type="7" value="jump" ></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="false" ></PROPERTY>
   
</CUSTOMPROPERTIES>