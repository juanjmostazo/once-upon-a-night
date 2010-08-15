<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
 
  <PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="500" fields="X;Y;Z;W"></PROPERTY>

  <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="30" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="8" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="6" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::position_correction" type="6" value="0 0 0" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::scale_correction" type="6" value="1 1 1" ></PROPERTY>

  <PROPERTY id="LogicComponent::scriptFilename" type="7" value="tripollo.lua" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::scriptFunction" type="7" value="tripolloLogic" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::patrolTrajectory" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::defaultState" type="2" value="3" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::healthPoints" type="2" value="3" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::numLives" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::lineOfSight" type="2" value="200" fields="X;Y;Z;W"></PROPERTY> ¡

  <!-- Trajectory Component -->
  <PROPERTY id="TrajectoryComponent::twodimensions" type="2" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="TrajectoryComponent::defaultspeed" type="2" value="0.3" fields="X;Y;Z;W"></PROPERTY> ¡


  <!-- Available attacks -->
  <PROPERTY id="AttackComponent::type" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::selectedAttack" type="7" value="peck" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#attackName" type="7" value="peck" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#animationName" type="7" value="attack01" fields="X;Y;Z;W">
  </PROPERTY>  
  <PROPERTY id="AttackComponent::attack0#damage" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#attackRange" type="2" value="10" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#cooldownDelay" type="6" value="1.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#area" type="6" value="0.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#powerCost" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <!-- -->
  <PROPERTY id="AttackComponent::attack1#attackName" type="7" value="claw" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#animationName" type="7" value="attack02" fields="X;Y;Z;W">
  </PROPERTY>  
  <PROPERTY id="AttackComponent::attack1#damage" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#attackRange" type="2" value="10" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#cooldownDelay" type="6" value="1.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#area" type="6" value="0.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#powerCost" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
 

  <!-- Animations -->
  <PROPERTY id="initialAnimation" type="7" value="idle01"></PROPERTY>
  
  <PROPERTY id="animation0d::name" type="7" value="die" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0d::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0d::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0d::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0d::transition0::blend_type" type="2" value="1"></PROPERTY>
  
  <PROPERTY id="animation1d::name" type="7" value="hit01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1d::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1d::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation1d::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1d::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1d::transition1::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation1d::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1d::transition1::blend_type" type="2" value="1"></PROPERTY>
  
  <PROPERTY id="animation2d::name" type="7" value="idle01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2d::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation2d::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2d::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2d::transition1::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation2d::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2d::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2d::transition2::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation2d::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2d::transition2::blend_type" type="2" value="1"></PROPERTY>  
  
  <PROPERTY id="animation3d::name" type="7" value="walk" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation3d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation3d::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation3d::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3d::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3d::transition1::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation3d::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3d::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3d::transition2::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation3d::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3d::transition2::blend_type" type="2" value="1"></PROPERTY>  
  
  <!-- Animations for the nightmare entity -->
    
  <PROPERTY id="animation0n::name" type="7" value="die" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0n::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0n::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0n::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0n::transition0::blend_type" type="2" value="1"></PROPERTY>
  
  <PROPERTY id="animation1n::name" type="7" value="hit01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1n::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1n::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation1n::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1n::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1n::transition1::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation1n::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1n::transition1::blend_type" type="2" value="1"></PROPERTY>
  
  <PROPERTY id="animation2n::name" type="7" value="idle01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2n::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation2n::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2n::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2n::transition1::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation2n::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2n::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2n::transition2::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation2n::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2n::transition2::blend_type" type="2" value="1"></PROPERTY>  
  
  <PROPERTY id="animation3n::name" type="7" value="walk" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation3n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation3n::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation3n::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3n::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3n::transition1::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation3n::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3n::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3n::transition2::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation3n::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3n::transition2::blend_type" type="2" value="1"></PROPERTY>  
  
  <!-- Sounds -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="tripollo_is_hit"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#1" type="7" value="tripollo_dies"></PROPERTY>
</CUSTOMPROPERTIES>