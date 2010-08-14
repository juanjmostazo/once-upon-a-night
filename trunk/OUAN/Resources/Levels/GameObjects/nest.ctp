<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
	<PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="1500" fields="X;Y;Z;W"></PROPERTY>
  
    <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="20" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="1.5" fields="X;Y;Z;W"></PROPERTY>
	<PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="8"></PROPERTY>	
	<PROPERTY id="PhysicsComponentCharacter::position_correction" type="6" value="0 40 0" ></PROPERTY>
	<PROPERTY id="PhysicsComponentCharacter::scale_correction" type="6" value="1.5 1.5 1.5" ></PROPERTY>
	<!-- Logic component properties  -->
	<PROPERTY id="LogicComponent::scriptFilename" type="7" value="nest.lua"></PROPERTY>
	<PROPERTY id="LogicComponent::scriptFunction" type="7" value="nestLogic"></PROPERTY>
	<PROPERTY id="LogicComponent::defaultState" type="2" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::approachDistance" type="6" value="50"></PROPERTY>
	<PROPERTY id="LogicComponent::delay" type="6" value="8"></PROPERTY>
	<!-- TODO: add animations! -->
	  <!-- Animations -->
	  <PROPERTY id="initialAnimation" type="7" value="idle"></PROPERTY>
	  
  <PROPERTY id="animation0::name" type="7" value="idle"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation1::name" type="7" value="shake" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation2::name" type="7" value="jump" ></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="false" ></PROPERTY>
   
</CUSTOMPROPERTIES>