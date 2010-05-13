<?xml version="1.0" encoding="utf-8"?>
<CUSTOMPROPERTIES>

  <PROPERTY id="RenderComponentQuadHalo::quadMaterial" type="7" value="quad_halo" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::haloRadio" type="6" value="20" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::totalQuads" type="6" value="256" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::quadSize" type="6" value="0.25" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::speedScale" type="6" value="0.1" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::offsetX" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::offsetY" type="6" value="15" ></PROPERTY>
  <PROPERTY id="RenderComponentQuadHalo::offsetZ" type="6" value="0" ></PROPERTY>
	
  <PROPERTY id="RenderComponentFractalVolume::texture3D" type="7" value="texture3D_32" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::juliaGlobalReal" type="6" value="0.4" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::juliaGlobalImag" type="6" value="0.5" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::juliaGlobalTheta" type="6" value="0.1" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::vScale" type="6" value="2.5" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::vCut" type="6" value="29.0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::vSlices" type="6" value="16" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::vSize" type="6" value="250" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::offsetX" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::offsetY" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::offsetZ" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::rotationDegreesInitialX" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::rotationDegreesInitialY" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::rotationDegreesInitialZ" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::rotationDegreesPerSecondX" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::rotationDegreesPerSecondY" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::rotationDegreesPerSecondZ" type="6" value="0" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::colorR" type="6" value="-1" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::colorG" type="6" value="-1" ></PROPERTY>
  <PROPERTY id="RenderComponentFractalVolume::colorB" type="6" value="-1" ></PROPERTY>
	
  <PROPERTY id="PhysicsComponentCharacter::mass" type="6" value="66" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::radius" type="6" value="4" ></PROPERTY>
  <PROPERTY id="PhysicsComponentCharacter::height" type="6" value="14" ></PROPERTY>
  
  <PROPERTY id="LogicComponent::scriptFilename" type="7" value="" ></PROPERTY>
  <PROPERTY id="LogicComponent::defaultState" type="2" value="-1" ></PROPERTY>
  <PROPERTY id="LogicComponent::healthPoints" type="2" value="3" ></PROPERTY>
  <PROPERTY id="LogicComponent::numLives" type="2" value="3" ></PROPERTY>
  <PROPERTY id="LogicComponent::lineOfSight" type="2" value="-1" ></PROPERTY>
  
  <PROPERTY id="WeaponComponent::weapon0" type="7" value="flashlight#1"></PROPERTY>
  <PROPERTY id="WeaponComponent::weapon1" type="7" value="pillow#0"></PROPERTY>
  
  <!-- Animations -->
  <PROPERTY id="animation0::name" type="7" value="idle01"></PROPERTY>
  <PROPERTY id="animation0::loop" type="12" value="true"></PROPERTY>
  <PROPERTY id="animation1::name" type="7" value="idle02" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation2::name" type="7" value="walk" ></PROPERTY>
  <PROPERTY id="animation2::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation3::name" type="7" value="run" ></PROPERTY>
  <PROPERTY id="animation3::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation4::name" type="7" value="jump" ></PROPERTY>
  <PROPERTY id="animation4::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation5::name" type="7" value="get_pillow" ></PROPERTY>
  <PROPERTY id="animation5::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation6::name" type="7" value="stab_right_pillow" ></PROPERTY>
  <PROPERTY id="animation6::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation7::name" type="7" value="stab_left_pillow" ></PROPERTY>  
  <PROPERTY id="animation7::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation8::name" type="7" value="leave_pillow" ></PROPERTY>
  <PROPERTY id="animation8::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation9::name" type="7" value="special_pillow_attack" ></PROPERTY>
  <PROPERTY id="animation9::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation10::name" type="7" value="get_flash" ></PROPERTY>
  <PROPERTY id="animation10::loop" type="12" value="false" ></PROPERTY>    
  <PROPERTY id="animation11::name" type="7" value="shoot_special" ></PROPERTY>
  <PROPERTY id="animation11::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation12::name" type="7" value="alert" ></PROPERTY>
  <PROPERTY id="animation12::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation13::name" type="7" value="hit01" ></PROPERTY>
  <PROPERTY id="animation13::loop" type="12" value="false" ></PROPERTY>    
  <PROPERTY id="animation14::name" type="7" value="hit02" ></PROPERTY>
  <PROPERTY id="animation14::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation15::name" type="7" value="die01" ></PROPERTY>
  <PROPERTY id="animation15::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation16::name" type="7" value="die02" ></PROPERTY>
  <PROPERTY id="animation16::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation17::name" type="7" value="tired" ></PROPERTY>
  <PROPERTY id="animation17::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation18::name" type="7" value="handle" ></PROPERTY>
  <PROPERTY id="animation18::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation19::name" type="7" value="open_door" ></PROPERTY>
  <PROPERTY id="animation19::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation20::name" type="7" value="get_piece" ></PROPERTY>
  <PROPERTY id="animation20::loop" type="12" value="false" ></PROPERTY>  
  <PROPERTY id="animation21::name" type="7" value="get_item" ></PROPERTY>
  <PROPERTY id="animation21::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation22::name" type="7" value="afraid" ></PROPERTY>
  <PROPERTY id="animation22::loop" type="12" value="true" ></PROPERTY>  
  <PROPERTY id="animation23::name" type="7" value="change_world" ></PROPERTY>
  <PROPERTY id="animation23::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation24::name" type="7" value="tickling" ></PROPERTY>
  <PROPERTY id="animation24::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation25::name" type="7" value="speak" ></PROPERTY>
  <PROPERTY id="animation25::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation26::name" type="7" value="falling" ></PROPERTY>
  <PROPERTY id="animation26::loop" type="12" value="true" ></PROPERTY>
  <PROPERTY id="animation27::name" type="7" value="shoot_up" ></PROPERTY>
  <PROPERTY id="animation27::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation28::name" type="7" value="shoot_center" ></PROPERTY>
  <PROPERTY id="animation28::loop" type="12" value="false" ></PROPERTY>
  <PROPERTY id="animation29::name" type="7" value="shoot_down" ></PROPERTY>
  <PROPERTY id="animation29::loop" type="12" value="false" ></PROPERTY> 
  <!--<PROPERTY id="animation1::name" type="7" value="idle03" ></PROPERTY>
  <PROPERTY id="animation1::loop" type="12" value="true" ></PROPERTY>-->
  
</CUSTOMPROPERTIES>