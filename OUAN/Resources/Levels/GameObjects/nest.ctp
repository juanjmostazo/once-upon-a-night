<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>

   <PROPERTY id="CustomAttribute::maxRenderRadium" type="6" value="500" fields="X;Y;Z;W"></PROPERTY>

	<PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="1500" fields="X;Y;Z;W"></PROPERTY>
  
	<!-- Physics component properties  -->
    <PROPERTY id="PhysicsComponentSimpleBox::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
    <PROPERTY id="PhysicsComponentSimpleBox::length" type="9" value="15 8 15" fields="X;Y;Z;W"></PROPERTY>

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

  <!-- Sounds -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="nest_break"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#1" type="7" value="nest_tripollo"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#2" type="7" value="nest_nothing"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#3" type="7" value="nest_toc_toc"></PROPERTY>
   
</CUSTOMPROPERTIES>