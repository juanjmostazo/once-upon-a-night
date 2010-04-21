<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
  <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="30" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="8" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="6" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::scriptFilename" type="7" value="tripollo.lua" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::scriptFunction" type="7" value="tripolloLogic" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::patrolTrajectory" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::defaultState" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::healthPoints" type="2" value="3" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::numLives" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::lineOfSight" type="2" value="150" fields="X;Y;Z;W"></PROPERTY>  
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
  <PROPERTY id="animation0d::name" type="7" value="alert" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0d::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1d::name" type="7" value="attack01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2d::name" type="7" value="attack02" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation3d::name" type="7" value="die" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation3d::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation4d::name" type="7" value="hit01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation4d::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation5d::name" type="7" value="idle01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation5d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation6d::name" type="7" value="idle02" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation6d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation7d::name" type="7" value="idle03" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation7d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation8d::name" type="7" value="run" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation8d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation9d::name" type="7" value="walk" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation9d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation10d::name" type="7" value="walk02" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation10d::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
    
  <!-- Animations for the nightmare entity -->
  <PROPERTY id="animation0n::name" type="7" value="alert" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0n::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1n::name" type="7" value="attack01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation1n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2n::name" type="7" value="attack02" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation2n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation3n::name" type="7" value="die" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation3n::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation4n::name" type="7" value="hit01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation4n::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation5n::name" type="7" value="idle01" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation5n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation6n::name" type="7" value="idle02" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation6n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation7n::name" type="7" value="idle03" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation7n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation8n::name" type="7" value="run" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation8n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation9n::name" type="7" value="walk" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation9n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
  <PROPERTY id="animation10n::name" type="7" value="walk02" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation10n::loop" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>  
</CUSTOMPROPERTIES>