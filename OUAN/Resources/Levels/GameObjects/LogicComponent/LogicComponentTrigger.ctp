<?xml version="1.0" encoding="utf-8"?>
<!-- Resto de propiedades -->
<CUSTOMPROPERTIES>
   <PROPERTY id="LogicComponent::triggerScript" type="7" value="goal_trigger.lua"></PROPERTY>
   <PROPERTY id="LogicComponent::enterActionFunction" type="7" value="goalEnterFunction"></PROPERTY>
   <PROPERTY id="LogicComponent::enterConditionFunction" type="7" value="goalEnterCondition"></PROPERTY> <!-- ESTA PROPIEDAD PUEDE BORRARSE SI NO INTERESA COMPROBAR CONDICIÓN ALGUNA-->
   <!--
   Para las funciones que se invocan al salir del trigger, deben indicarse los ids
   "LogicComponent::exitActionFunction", y "LogicComponent::exitConditionFunction".
    Aunque los atributos de la clase LogicComponentTrigger están encabezados por el mundo, en este caso el id es el mismo para sueños y pesadillas,
    ya que se están recuperando del nodo asociado a un mundo concreto así que no hay conflicto posible.
   -->
</CUSTOMPROPERTIES>
