<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
	<PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="100" fields="X;Y;Z;W"></PROPERTY>		
        <PROPERTY id="PhysicsComponentSimpleBox::mass" type="6" value="0" fields="X;Y;Z;W"></PROPERTY>
        <PROPERTY id="PhysicsComponentSimpleBox::length" type="9" value="5 10 5" fields="X;Y;Z;W"></PROPERTY>

	<!-- Logic component properties  -->
	<PROPERTY id="LogicComponent::scriptFilename" type="7" value="signpost.lua"></PROPERTY>
	<PROPERTY id="LogicComponent::scriptFunction" type="7" value="signpostLogic"></PROPERTY>
	<PROPERTY id="LogicComponent::defaultState" type="2" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::approachDistance" type="6" value="0"></PROPERTY>
	<PROPERTY id="LogicComponent::delay" type="6" value="0"></PROPERTY>
	
	<!-- TODO: Animations! -->
	<PROPERTY id="initialAnimation" type="7" value="idle"></PROPERTY>
	
	<PROPERTY id="animation0d::name" type="7" value="idle"></PROPERTY>
	<PROPERTY id="animation0d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
	
	
	<PROPERTY id="animation1d::name" type="7" value="hit"></PROPERTY>
	<PROPERTY id="animation1d::loop" type="12" value="false"></PROPERTY>	

	
	<PROPERTY id="RenderComponentMessageBox::basePanelName" type="7" value="OUAN/SignpostMessage"></PROPERTY>
	<PROPERTY id="RenderComponentMessageBox::charPanelName" type="7" value="" ></PROPERTY>  

</CUSTOMPROPERTIES>