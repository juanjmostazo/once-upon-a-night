<?xml version="1.0" encoding="utf-8"?>
<!-- Resto de propiedades -->
<CUSTOMPROPERTIES>
   <PROPERTY id="LogicComponent::triggerScript" type="7" value="goal_trigger.lua"></PROPERTY>
   <PROPERTY id="LogicComponent::enterActionFunction" type="7" value="goalEnterFunction"></PROPERTY>
   <PROPERTY id="LogicComponent::enterConditionFunction" type="7" value="goalEnterCondition"></PROPERTY> <!-- ESTA PROPIEDAD PUEDE BORRARSE SI NO INTERESA COMPROBAR CONDICI�N ALGUNA-->
   <!--
   Para las funciones que se invocan al salir del trigger, deben indicarse los ids
   "LogicComponent::exitActionFunction", y "LogicComponent::exitConditionFunction".
    Aunque los atributos de la clase LogicComponentTrigger est�n encabezados por el mundo, en este caso el id es el mismo para sue�os y pesadillas,
    ya que se est�n recuperando del nodo asociado a un mundo concreto as� que no hay conflicto posible.
   -->
</CUSTOMPROPERTIES>
