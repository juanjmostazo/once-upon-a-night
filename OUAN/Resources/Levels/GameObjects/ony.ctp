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
  
  <PROPERTY id="PhysicsComponentCharacterOny::mass" type="6" value="0" ></PROPERTY>
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
  
    <!-- TRANSITION VARS 
  <PROPERTY id="animation0::name" type="7" value="die" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="false" fields="X;Y;Z;W"></PROPERTY>
  <PROPERTY id="animation0::transition0::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0::transition0::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0::transition0::blend_type" type="2" value="1"></PROPERTY>
  -->
  
  <PROPERTY id="initialAnimation" type="7" value="idle01"></PROPERTY>

  <PROPERTY id="animation0::name" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation0::timescale" type="6" value="1.0"></PROPERTY> <!-- BY DEFAULT -->
  <PROPERTY id="animation0::transition0::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation0::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation0::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation0::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation0::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation0::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition3::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation0::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation0::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation0::transition4::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation0::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation0::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation0::transition5::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation0::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation0::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation0::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation0::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation0::transition7::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation0::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation0::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation0::transition8::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation0::transition8::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation0::transition8::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation0::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation0::transition9::duration" type="6" value="0.4"></PROPERTY>
  <PROPERTY id="animation0::transition9::blend_type" type="2" value="1"></PROPERTY> 
  
  
  <PROPERTY id="animation1::name" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation1::transition0::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation1::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation1::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation1::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation1::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition3::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation1::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation1::transition4::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation1::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation1::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation1::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation1::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation1::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation1::transition7::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation1::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation1::transition8::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation1::transition8::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation1::transition8::blend_type" type="2" value="1"></PROPERTY> 
          <PROPERTY id="animation1::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation1::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation1::transition9::blend_type" type="2" value="1"></PROPERTY> 
  
  
  <PROPERTY id="animation2::name" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="false"></PROPERTY>
    <PROPERTY id="animation2::transition0::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation2::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation2::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation2::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation2::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition3::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation2::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation2::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation2::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation2::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation2::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation2::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation2::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation2::transition7::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation2::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation2::transition8::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation2::transition8::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation2::transition8::blend_type" type="2" value="1"></PROPERTY> 
        <PROPERTY id="animation2::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation2::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation2::transition9::blend_type" type="2" value="1"></PROPERTY>    
  
  
  <PROPERTY id="animation3::name" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation3::loop" type="12" value="false"></PROPERTY>
    <PROPERTY id="animation3::transition0::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation3::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation3::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation3::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation3::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation3::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation3::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation3::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation3::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation3::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation3::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation3::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation3::transition7::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation3::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation3::transition8::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation3::transition8::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation3::transition8::blend_type" type="2" value="1"></PROPERTY> 
        <PROPERTY id="animation3::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation3::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation3::transition9::blend_type" type="2" value="1"></PROPERTY>   
  
  
  
  <PROPERTY id="animation4::name" type="7" value="crouch_loop"></PROPERTY>
  <PROPERTY id="animation4::loop" type="12" value="true"></PROPERTY>
  
  
  <PROPERTY id="animation5::name" type="7" value="crouch_post"></PROPERTY>
  <PROPERTY id="animation5::loop" type="12" value="false"></PROPERTY>  
  
  
  <PROPERTY id="animation6::name" type="7" value="crouch_pre"></PROPERTY>
  <PROPERTY id="animation6::loop" type="12" value="false"></PROPERTY>  
  
  
  <PROPERTY id="animation7::name" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation7::loop" type="12" value="false"></PROPERTY>  
  
  
  <PROPERTY id="animation8::name" type="7" value="draw_pillow"></PROPERTY>
  <PROPERTY id="animation8::loop" type="12" value="false"></PROPERTY>  
  
  
  <PROPERTY id="animation9::name" type="7" value="face_afraid"></PROPERTY>
  <PROPERTY id="animation9::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation10::name" type="7" value="face_close"></PROPERTY>
  <PROPERTY id="animation10::loop" type="12" value="false"></PROPERTY>    
  <PROPERTY id="animation11::name" type="7" value="face_happy01"></PROPERTY>
  <PROPERTY id="animation11::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation12::name" type="7" value="face_happy02"></PROPERTY>
  <PROPERTY id="animation12::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation13::name" type="7" value="face_neutral"></PROPERTY>
  <PROPERTY id="animation13::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation14::name" type="7" value="face_panic"></PROPERTY>
  <PROPERTY id="animation14::loop" type="12" value="false"></PROPERTY>    
  <PROPERTY id="animation15::name" type="7" value="face_sad"></PROPERTY>
  <PROPERTY id="animation15::loop" type="12" value="false"></PROPERTY>    
  <PROPERTY id="animation16::name" type="7" value="face_scream"></PROPERTY>
  <PROPERTY id="animation16::loop" type="12" value="false"></PROPERTY>    
  <PROPERTY id="animation17::name" type="7" value="face_speak01"></PROPERTY>
  <PROPERTY id="animation17::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation18::name" type="7" value="face_speak02"></PROPERTY>
  <PROPERTY id="animation18::loop" type="12" value="false"></PROPERTY>  
  
  
  <PROPERTY id="animation19::name" type="7" value="fall_loop"></PROPERTY>
  <PROPERTY id="animation19::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation20::name" type="7" value="fall_post"></PROPERTY>
  <PROPERTY id="animation20::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation21::name" type="7" value="fall_pre"></PROPERTY>
  <PROPERTY id="animation21::loop" type="12" value="false"></PROPERTY>    
  <PROPERTY id="animation22::name" type="7" value="fright"></PROPERTY>
  <PROPERTY id="animation22::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation23::name" type="7" value="hide_pillow01"></PROPERTY>
  <PROPERTY id="animation23::loop" type="12" value="false"></PROPERTY>    
  <PROPERTY id="animation24::name" type="7" value="hide_pillow02"></PROPERTY>
  <PROPERTY id="animation24::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation25::name" type="7" value="hide_pillow03"></PROPERTY>
  <PROPERTY id="animation25::loop" type="12" value="false"></PROPERTY>
  
  <PROPERTY id="animation26::name" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation26::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation26::transition0::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation26::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation26::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation26::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation26::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation26::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation26::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation26::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation26::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation26::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation26::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation26::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation26::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation26::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation26::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation26::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation26::transition7::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation26::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation26::transition8::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation26::transition8::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation26::transition8::blend_type" type="2" value="1"></PROPERTY>
      <PROPERTY id="animation26::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation26::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation26::transition9::blend_type" type="2" value="1"></PROPERTY>   
  
  
  
  <PROPERTY id="animation27::name" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation27::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation27::transition0::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation27::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation27::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation27::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation27::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation27::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation27::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation27::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation27::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation27::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation27::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation27::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation27::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation27::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation27::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation27::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation27::transition7::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation27::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation27::transition8::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation27::transition8::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation27::transition8::blend_type" type="2" value="1"></PROPERTY>
      <PROPERTY id="animation27::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation27::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation27::transition9::blend_type" type="2" value="1"></PROPERTY> 
  
  
  <PROPERTY id="animation28::name" type="7" value="jump01_loop"></PROPERTY>
  <PROPERTY id="animation28::loop" type="12" value="true"></PROPERTY>  
  <PROPERTY id="animation29::name" type="7" value="jump01_post"></PROPERTY>
  <PROPERTY id="animation29::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation30::name" type="7" value="jump01_pre"></PROPERTY>
  <PROPERTY id="animation30::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation31::name" type="7" value="jump02_loop"></PROPERTY>
  <PROPERTY id="animation31::loop" type="12" value="true"></PROPERTY>  
  <PROPERTY id="animation32::name" type="7" value="jump02_post"></PROPERTY>
  <PROPERTY id="animation32::loop" type="12" value="false"></PROPERTY>
  
  <PROPERTY id="animation33::name" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation33::loop" type="12" value="false"></PROPERTY>
  <PROPERTY id="animation33::transition0::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation33::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation33::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation33::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation33::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation33::transition2::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation33::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation33::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation33::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation33::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation33::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation33::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation33::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation33::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation33::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation33::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation33::transition7::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation33::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation33::transition8::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation33::transition8::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition8::blend_type" type="2" value="1"></PROPERTY> 
    <PROPERTY id="animation33::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation33::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation33::transition9::blend_type" type="2" value="1"></PROPERTY> 
  
  
  
  <PROPERTY id="animation34::name" type="7" value="look_back"></PROPERTY>
  <PROPERTY id="animation34::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation35::name" type="7" value="look_down"></PROPERTY>
  <PROPERTY id="animation35::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation36::name" type="7" value="look_left"></PROPERTY>
  <PROPERTY id="animation36::loop" type="12" value="false"></PROPERTY>  
  <PROPERTY id="animation37::name" type="7" value="look_right"></PROPERTY>
  <PROPERTY id="animation37::loop" type="12" value="false"></PROPERTY>   
  <PROPERTY id="animation38::name" type="7" value="look_up"></PROPERTY>
  <PROPERTY id="animation38::loop" type="12" value="false"></PROPERTY>   
  <PROPERTY id="animation39::name" type="7" value="manual"></PROPERTY>
  <PROPERTY id="animation39::loop" type="12" value="true"></PROPERTY>   
  <PROPERTY id="animation40::name" type="7" value="nap_loop"></PROPERTY>
  <PROPERTY id="animation40::loop" type="12" value="true"></PROPERTY>   
  <PROPERTY id="animation41::name" type="7" value="nap_post"></PROPERTY>
  <PROPERTY id="animation41::loop" type="12" value="false"></PROPERTY>   
  <PROPERTY id="animation42::name" type="7" value="nap_pre"></PROPERTY>
  <PROPERTY id="animation42::loop" type="12" value="false"></PROPERTY>     
  
  
  <PROPERTY id="animation43::name" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation43::loop" type="12" value="true"></PROPERTY>
   <PROPERTY id="animation43::transition0::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation43::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation43::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation43::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation43::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation43::transition2::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation43::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation43::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation43::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation43::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition3::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation43::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation43::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition4::blend_type" type="2" value="1"></PROPERTY>    
  <PROPERTY id="animation43::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation43::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation43::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation43::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation43::transition7::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation43::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition7::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation43::transition8::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation43::transition8::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition8::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation43::transition9::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation43::transition9::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation43::transition9::blend_type" type="2" value="1"></PROPERTY> 
  
  <PROPERTY id="animation44::name" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation44::loop" type="12" value="true"></PROPERTY>
   <PROPERTY id="animation44::transition0::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation44::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation44::transition1::target" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation44::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation44::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation44::transition2::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation44::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation44::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation44::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation44::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition3::blend_type" type="2" value="0"></PROPERTY>  
  <PROPERTY id="animation44::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation44::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition4::blend_type" type="2" value="0"></PROPERTY>    
  <PROPERTY id="animation44::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation44::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation44::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation44::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation44::transition7::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation44::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition7::blend_type" type="2" value="0"></PROPERTY>  
  <PROPERTY id="animation44::transition8::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation44::transition8::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation44::transition8::blend_type" type="2" value="1"></PROPERTY>
	<PROPERTY id="animation44::transition9::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation44::transition9::duration" type="6" value="0.4"></PROPERTY>
  <PROPERTY id="animation44::transition9::blend_type" type="2" value="1"></PROPERTY>  
  
  
  <PROPERTY id="animation45::name" type="7" value="tickling_loop"></PROPERTY>
  <PROPERTY id="animation45::loop" type="12" value="true"></PROPERTY>     
  <PROPERTY id="animation46::name" type="7" value="tickling_pre"></PROPERTY>
  <PROPERTY id="animation46::loop" type="12" value="false"></PROPERTY>   
  <PROPERTY id="animation47::name" type="7" value="victory"></PROPERTY>
  <PROPERTY id="animation47::loop" type="12" value="false"></PROPERTY>       
  <PROPERTY id="animation48::name" type="7" value="victory_loop"></PROPERTY>
  <PROPERTY id="animation48::loop" type="12" value="true"></PROPERTY>   
  <PROPERTY id="animation49::name" type="7" value="victory_pre"></PROPERTY>
  <PROPERTY id="animation49::loop" type="12" value="false"></PROPERTY>  
  
  
  <PROPERTY id="animation50::name" type="7" value="walk"></PROPERTY>
  <PROPERTY id="animation50::loop" type="12" value="true"></PROPERTY> 
  <PROPERTY id="animation50::transition0::target" type="7" value="hit01"></PROPERTY>
  <PROPERTY id="animation50::transition0::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition0::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation50::transition1::target" type="7" value="shoot_center"></PROPERTY>
  <PROPERTY id="animation50::transition1::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation50::transition1::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation50::transition2::target" type="7" value="jump02_pre"></PROPERTY>
  <PROPERTY id="animation50::transition2::duration" type="6" value="0.2"></PROPERTY>
  <PROPERTY id="animation50::transition2::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation50::transition3::target" type="7" value="attack02"></PROPERTY>
  <PROPERTY id="animation50::transition3::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition3::blend_type" type="2" value="0"></PROPERTY>  
  <PROPERTY id="animation50::transition4::target" type="7" value="attack01"></PROPERTY>
  <PROPERTY id="animation50::transition4::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition4::blend_type" type="2" value="0"></PROPERTY>    
  <PROPERTY id="animation50::transition5::target" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation50::transition5::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition5::blend_type" type="2" value="1"></PROPERTY>
  <PROPERTY id="animation50::transition6::target" type="7" value="die"></PROPERTY>
  <PROPERTY id="animation50::transition6::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition6::blend_type" type="2" value="1"></PROPERTY>  
  <PROPERTY id="animation50::transition7::target" type="7" value="attack03"></PROPERTY>
  <PROPERTY id="animation50::transition7::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition7::blend_type" type="2" value="0"></PROPERTY>  
  <PROPERTY id="animation50::transition8::target" type="7" value="idle02"></PROPERTY>
  <PROPERTY id="animation50::transition8::duration" type="6" value="0.1"></PROPERTY>
  <PROPERTY id="animation50::transition8::blend_type" type="2" value="1"></PROPERTY>
	<PROPERTY id="animation50::transition9::target" type="7" value="run"></PROPERTY>
  <PROPERTY id="animation50::transition9::duration" type="6" value="0.4"></PROPERTY>
  <PROPERTY id="animation50::transition9::blend_type" type="2" value="1"></PROPERTY> 

  <!-- Audio component -->
  <PROPERTY id="AudioComponent::soundID#0" type="7" value="any_triumph_laught"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#1" type="7" value="any_dies"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#2" type="7" value="any_step_grass_00"></PROPERTY>
  <PROPERTY id="AudioComponent::soundID#3" type="7" value="any_step_grass_01"></PROPERTY>  
  <PROPERTY id="AudioComponent::soundID#4" type="7" value="any_step_water_00"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#5" type="7" value="any_step_water_01"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#6" type="7" value="any_step_hard_surface_00"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#7" type="7" value="any_step_hard_surface_01"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#8" type="7" value="any_step_wood_00"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#9" type="7" value="any_step_wood_01"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#10" type="7" value="any_scared"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#11" type="7" value="any_falls"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#12" type="7" value="any_laughts"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#13" type="7" value="any_pillow_attack"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#14" type="7" value="any_push"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#15" type="7" value="any_interested"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#16" type="7" value="any_triumph_a"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#17" type="7" value="any_triumph_b"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#18" type="7" value="any_takes_hit_a"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#19" type="7" value="any_takes_hit_b"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#20" type="7" value="any_jump"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#21" type="7" value="any_burn"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#22" type="7" value="any_exhausted"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#23" type="7" value="any_surprise_a"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#24" type="7" value="any_surprise_b"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#25" type="7" value="any_very_scared"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#26" type="7" value="any_splash_00"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#27" type="7" value="any_splash_01"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#28" type="7" value="any_splash_02"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#29" type="7" value="any_crash_00"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#30" type="7" value="any_crash_01"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#31" type="7" value="any_crash_02"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#32" type="7" value="any_slide"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#33" type="7" value="any_jump_onto_water"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#34" type="7" value="any_jump_onto_grass"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#35" type="7" value="any_jump_onto_hard_surface"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#36" type="7" value="any_jump_onto_wood"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#37" type="7" value="pillow_attack_start"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#38" type="7" value="pillow_attack_end"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#39" type="7" value="flashlight_attack_start"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#40" type="7" value="flashlight_attack_end"></PROPERTY>   
  <PROPERTY id="AudioComponent::soundID#41" type="7" value="flashlight_overheat"></PROPERTY>   



</CUSTOMPROPERTIES>