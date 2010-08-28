<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>

  <PROPERTY id="RenderComponentQuadHalo::quadMaterial" type="7" value="quad_halo" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::haloRadio" type="6" value="9" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::totalQuads" type="6" value="256" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::quadSize" type="6" value="0.2" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::speedScale" type="6" value="0.1" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::offsetX" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::offsetY" type="6" value="7" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::offsetZ" type="6" value="0" ></PROPERTY>
  
  <PROPERTY id="PhysicsComponentCharacterOny::mass" type="6" value="66" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacterOny::radius" type="6" value="4" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacterOny::height" type="6" value="14" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacterOny::position_correction" type="6" value="0 -12 0" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacterOny::scale_correction" type="6" value="1.5 1.5 1.5" ></PROPERTY>
  
  <PROPERTY id="LogicComponent::scriptFilename" type="7" value="" ></PROPERTY>
  <PROPERTY id="LogicComponent::defaultState" type="2" value="-1" ></PROPERTY>
  <PROPERTY id="LogicComponent::healthPoints" type="2" value="3" ></PROPERTY>
  <PROPERTY id="LogicComponent::numLives" type="2" value="3" ></PROPERTY>
  <PROPERTY id="LogicComponent::lineOfSight" type="2" value="-1" ></PROPERTY>
  
  <PROPERTY id="CollectableItem0::type" type="7" value="diamond"></PROPERTY>
  <PROPERTY id="CollectableItem0::newLifeAmount" type="2" value="50"></PROPERTY>
  
  <PROPERTY id="WeaponComponent::weapon0" type="7" value="flashlight#1"></PROPERTY>
  <PROPERTY id="WeaponComponent::weapon1" type="7" value="pillow#0"></PROPERTY>
  
  <PROPERTY id="RunParticles::min" type="6" value="2.0"></PROPERTY>
  <PROPERTY id="RunParticles::max" type="6" value="5.0"></PROPERTY>
  
  <PROPERTY id="RenderComponentMessageBox::basePanelName" type="7" value="OUAN/TextBubble"></PROPERTY>
  <PROPERTY id="RenderComponentMessageBox::charPanelName" type="7" value=""></PROPERTY>
  <PROPERTY id="RenderComponentMessageBox::duration" type="6" value="0.5" ></PROPERTY>
  <PROPERTY id="RenderComponentMessageBox::message" type="7" value="" ></PROPERTY>
  <PROPERTY id="RenderComponentMessageBox::visible" type="12" value="false" ></PROPERTY>
  
  <PROPERTY id="TrajectoryComponent::twodimensions" type="2" value="true" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="TrajectoryComponent::defaultspeed" type="2" value="0.3" fields="X;Y;Z;W"></PROPERTY>
  
  <!-- Animations -->
  <PROPERTY id="initialAnimation" type="7" value="idle01"></PROPERTY>

  <PROPERTY id="animation0::name" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation0::timescale" type="6" value="1.0"></PROPERTY> <!-- BY DEFAULT -->
  <PROPERTY id="animation0::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation0::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation0::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition2::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation0::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation0::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation0::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation0::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition6::target" type="7" value="stab_pillow"></PROPERTY>
  <PROPERTY id="animation0::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition6::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition7::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation0::transition7::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation0::transition7::blend_type" type="2" value="1"></PROPERTY>
  
  
  <PROPERTY id="animation1::name" type="7" value="idle02" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation1::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation1::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation1::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation1::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation1::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation1::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation1::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition6::target" type="7" value="stab_pillow"></PROPERTY>
  <PROPERTY id="animation1::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition6::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition7::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation1::transition7::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation1::transition7::blend_type" type="2" value="1"></PROPERTY>
  
  
  <PROPERTY id="animation2::name" type="7" value="walk" ></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation2::timescale" type="6" value="1.5" ></PROPERTY>
  <PROPERTY id="animation2::transition0::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation2::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation2::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation2::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation2::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation2::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation2::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition6::target" type="7" value="stab_pillow"></PROPERTY>
  <PROPERTY id="animation2::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition6::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition7::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation2::transition7::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation2::transition7::blend_type" type="2" value="1"></PROPERTY>
  
  <PROPERTY id="animation3::name" type="7" value="run" ></PROPERTY>
  <PROPERTY id="animation3::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation3::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation3::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition1::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation3::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation3::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation3::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation3::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation3::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition6::target" type="7" value="stab_pillow"></PROPERTY>
  <PROPERTY id="animation3::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition6::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition7::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation3::transition7::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation3::transition7::blend_type" type="2" value="1"></PROPERTY>
  
  
  <PROPERTY id="animation4::name" type="7" value="jump_init" ></PROPERTY>
  <PROPERTY id="animation4::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation4::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation4::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation4::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation4::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition3::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation4::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation4::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation4::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition6::target" type="7" value="stab_pillow"></PROPERTY>
  <PROPERTY id="animation4::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition6::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation4::transition7::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation4::transition7::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation4::transition7::blend_type" type="2" value="1"></PROPERTY>
  
  <PROPERTY id="animation5::name" type="7" value="hit1" ></PROPERTY>
  <PROPERTY id="animation5::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation5::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation5::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation5::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation5::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation5::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5::transition4::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation5::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5::transition5::target" type="7" value="stab_pillow"></PROPERTY>
  <PROPERTY id="animation5::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation5::transition6::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation5::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation5::transition6::blend_type" type="2" value="1"></PROPERTY>  
  
  <PROPERTY id="animation6::name" type="7" value="die02" ></PROPERTY>
  <PROPERTY id="animation6::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation6::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation6::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation6::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation6::transition1::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation6::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation6::transition1::blend_type" type="2" value="1"></PROPERTY>  
  
  <PROPERTY id="animation7::name" type="7" value="shoot_center" ></PROPERTY>
  <PROPERTY id="animation7::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation7::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation7::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation7::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation7::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation7::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation7::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation7::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation7::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation7::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation7::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation7::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation7::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition5::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation7::transition6::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation7::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation7::transition6::blend_type" type="2" value="1"></PROPERTY>  
  
  <PROPERTY id="animation8::name" type="7" value="stab_pillow" ></PROPERTY>  
  <PROPERTY id="animation8::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation8::timescale" type="6" value="0.8" ></PROPERTY>
  <PROPERTY id="animation8::transition0::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation8::transition0::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation8::transition1::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation8::transition1::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition1::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation8::transition2::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation8::transition2::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation8::transition3::target" type="7" value="jump_init"></PROPERTY>
  <PROPERTY id="animation8::transition3::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition3::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation8::transition4::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation8::transition4::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition4::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation8::transition5::target" type="7" value="die01"></PROPERTY>
  <PROPERTY id="animation8::transition5::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition5::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation8::transition6::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation8::transition6::duration" type="6" value="0.5"></PROPERTY>
  <PROPERTY id="animation8::transition6::blend_type" type="2" value="1"></PROPERTY>  

  
  <!-- Audio component -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="any_takes_hit"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#1" type="7" value="any_dies"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#2" type="7" value="any_step_grass_00"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#3" type="7" value="any_step_grass_01"></PROPERTY>  
  <PROPERTY id="AudioComponent::soundID#4" type="7" value="any_triumph"></PROPERTY>   
  
</CUSTOMPROPERTIES>