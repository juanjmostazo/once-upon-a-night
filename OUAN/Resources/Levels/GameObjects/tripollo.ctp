<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>
    <PROPERTY id="CustomAttribute::maxRenderRadium" type="6" value="900" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="CustomAttribute::maxUpdateRadium" type="6" value="500" fields="X;Y;Z;W"></PROPERTY>

  <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="30" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="8" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="6" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::position_correction" type="6" value="0 -3 0" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::scale_correction" type="6" value="1 1 1" ></PROPERTY>

  <PROPERTY id="LogicComponent::scriptFilename" type="7" value="tripollo.lua" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::scriptFunction" type="7" value="tripolloLogic" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::patrolTrajectory" type="12" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::defaultState" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::healthPoints" type="2" value="3" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::numLives" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="LogicComponent::lineOfSight" type="2" value="200" fields="X;Y;Z;W"></PROPERTY> ¡

  <!-- Trajectory Component -->
  <PROPERTY id="TrajectoryComponent::twodimensions" type="2" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="TrajectoryComponent::defaultspeed" type="2" value="0.3" fields="X;Y;Z;W"></PROPERTY>

  <!-- Available attacks -->
  <PROPERTY id="AttackComponent::type" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::selectedAttack" type="7" value="peck" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#attackName" type="7" value="peck" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#animationName" type="7" value="attack01" fields="X;Y;Z;W">
  </PROPERTY>  
  <PROPERTY id="AttackComponent::attack0#damage" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#attackRange" type="2" value="17" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#cooldownDelay" type="6" value="1.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#area" type="6" value="0.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack0#powerCost" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
  <!-- -->
  <PROPERTY id="AttackComponent::attack1#attackName" type="7" value="claw" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#animationName" type="7" value="attack02" fields="X;Y;Z;W">
  </PROPERTY>  
  <PROPERTY id="AttackComponent::attack1#damage" type="2" value="1" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#attackRange" type="2" value="17" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#cooldownDelay" type="6" value="1.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#area" type="6" value="0.0" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="AttackComponent::attack1#powerCost" type="2" value="0" fields="X;Y;Z;W"></PROPERTY>
 

  <!-- Animations -->
  <PROPERTY id="initialAnimation" type="7" value="idle_00"></PROPERTY>
  
  <PROPERTY id="animation0d::name" type="7" value="die" ></PROPERTY>  
  <PROPERTY id="animation0d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation1d::name" type="7" value="hit01" ></PROPERTY>
  <PROPERTY id="animation1d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation2d::name" type="7" value="hit02"></PROPERTY>  
  <PROPERTY id="animation2d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation3d::name" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation3d::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation4d::name" type="7" value="walk_fast"></PROPERTY>
  <PROPERTY id="animation4d::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation5d::name" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation5d::loop" type="7" value="true"></PROPERTY>
  <PROPERTY id="animation5d::transition0::target" type="7" value="attack00"></PROPERTY>
  <PROPERTY id="animation5d::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5d::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5d::transition1::target" type="7" value="attack_01"></PROPERTY>
  <PROPERTY id="animation5d::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5d::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation6d::name" type="7" value="alert"></PROPERTY>
  <PROPERTY id="animation6d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation7d::name" type="7" value="attack00"></PROPERTY>
  <PROPERTY id="animation7d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation8d::name" type="7" value="attack_01"></PROPERTY>
  <PROPERTY id="animation8d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation9d::name" type="7" value="call_to_arms"></PROPERTY>
  <PROPERTY id="animation9d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation10d::name" type="7" value="false_alarm"></PROPERTY>
  <PROPERTY id="animation10d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation11d::name" type="7" value="flee_afraid"></PROPERTY>
  <PROPERTY id="animation11d::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation12d::name" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation12d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation13d::name" type="7" value="rest"></PROPERTY>
  <PROPERTY id="animation13d::loop" type="12" value="true"></PROPERTY>  
  <PROPERTY id="animation14d::name" type="7" value="stun"></PROPERTY>
  <PROPERTY id="animation14d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation15d::name" type="7" value="surprise"></PROPERTY>
  <PROPERTY id="animation15d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation16d::name" type="7" value="tired"></PROPERTY>
  <PROPERTY id="animation16d::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation17d::name" type="7" value="manual"></PROPERTY>
  <PROPERTY id="animation17d::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation18d::name" type="7" value="idle_00"></PROPERTY>
  <PROPERTY id="animation18d::loop" type="12" value="true"></PROPERTY>
  
  <!-- Animations for the nightmare entity -->
  <PROPERTY id="animation0n::name" type="7" value="die" ></PROPERTY>  
  <PROPERTY id="animation0n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation1n::name" type="7" value="hit01" ></PROPERTY>
  <PROPERTY id="animation1n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation2n::name" type="7" value="hit02"></PROPERTY>  
  <PROPERTY id="animation2n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation3n::name" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation3n::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation4n::name" type="7" value="walk_fast"></PROPERTY>
  <PROPERTY id="animation4n::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation5n::name" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation5n::loop" type="7" value="true"></PROPERTY>
  <PROPERTY id="animation5n::transition0::target" type="7" value="attack00"></PROPERTY>
  <PROPERTY id="animation5n::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5n::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5n::transition1::target" type="7" value="attack_01"></PROPERTY>
  <PROPERTY id="animation5n::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5n::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation6n::name" type="7" value="alert"></PROPERTY>
  <PROPERTY id="animation6n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation7n::name" type="7" value="attack00"></PROPERTY>
  <PROPERTY id="animation7n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation8n::name" type="7" value="attack_01"></PROPERTY>
  <PROPERTY id="animation8n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation9n::name" type="7" value="call_to_arms"></PROPERTY>
  <PROPERTY id="animation9n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation10n::name" type="7" value="false_alarm"></PROPERTY>
  <PROPERTY id="animation10n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation11n::name" type="7" value="flee_afraid"></PROPERTY>
  <PROPERTY id="animation11n::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation12n::name" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation12n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation13n::name" type="7" value="rest"></PROPERTY>
  <PROPERTY id="animation13n::loop" type="12" value="true"></PROPERTY>  
  <PROPERTY id="animation14n::name" type="7" value="stun"></PROPERTY>
  <PROPERTY id="animation14n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation15n::name" type="7" value="surprise"></PROPERTY>
  <PROPERTY id="animation15n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation16n::name" type="7" value="tired"></PROPERTY>
  <PROPERTY id="animation16n::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation17n::name" type="7" value="manual"></PROPERTY>
  <PROPERTY id="animation17n::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation18n::name" type="7" value="idle_00"></PROPERTY>
  <PROPERTY id="animation18n::loop" type="12" value="true"></PROPERTY>
  
  
  <!-- TRANSITION VARS 
  <PROPERTY id="animation0n::name" type="7" value="die" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0n::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0n::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0n::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0n::transition0::blend_type" type="2" value="1"></PROPERTY>
  
  -->
  
  
  <!-- Sounds -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="tripollo_wings"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#1" type="7" value="tripollo_scratch"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#2" type="7" value="tripollo_explosion"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#3" type="7" value="tripollo_graznido"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#4" type="7" value="tripollo_attack"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#5" type="7" value="tripollo_hit"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#6" type="7" value="tripollo_surprise"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#6" type="7" value="tripollo_die"></PROPERTY>

</CUSTOMPROPERTIES>