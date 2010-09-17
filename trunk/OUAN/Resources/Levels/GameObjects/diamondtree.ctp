<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
	<PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="1500" fields="X;Y;Z;W"></PROPERTY>		
        <PROPERTY id="PhysicsComponentSimpleBox::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
        <PROPERTY id="PhysicsComponentSimpleBox::length" type="9" value="15 80 15" fields="X;Y;Z;W"></PROPERTY>
	<!--
	<PROPERTY id="PhysicsComponentSimpleBox::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentSimpleBox::length" type="9" value="15 80 15" fields="X;Y;Z;W"></PROPERTY>
	<PROPERTY id="PhysicsComponentVolumeBox::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentVolumeBox::length" type="9" value="30 80 30" fields="X;Y;Z;W"></PROPERTY>
	-->
	<!-- Logic component properties  -->
	<PROPERTY id="LogicComponent::scriptFilename" type="7" value="diamond_tree.lua"></PROPERTY>
	<PROPERTY id="LogicComponent::scriptFunction" type="7" value="diamondTreeLogic"></PROPERTY>
	<PROPERTY id="LogicComponent::defaultState" type="2" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::approachDistance" type="6" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::delay" type="6" value="30"></PROPERTY>
	
	<!-- TODO: Animations! -->
	<PROPERTY id="initialAnimation" type="7" value="static_pose"></PROPERTY>
	<PROPERTY id="animation0::name" type="7" value="static_pose"></PROPERTY>
	<PROPERTY id="animation0::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  
	<PROPERTY id="animation1::name" type="7" value="hit"></PROPERTY>
	<PROPERTY id="animation1::loop" type="12" value="false"></PROPERTY>
	
  <!-- Sounds -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="tree"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#1" type="7" value="diamond"></PROPERTY>
	</CUSTOMPROPERTIES>