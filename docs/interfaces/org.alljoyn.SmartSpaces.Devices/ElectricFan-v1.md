# org.alljoyn.SmartSpaces.Devices.ElectricFan version 1

## Theory of Operation

Electric Fan is a home appliance that creates air flow.  This interface is an
abstract type so that it covers any type of Electric Fans related air flow
such as floor fans and ceiling fans.

The minimum required shared interface for Electric Fan is as follows:
  * **org.alljoyn.SmartSpaces.Operation.Control** --- for control

The operation states that Electric Fan supports are:
  * **0** --- **Off**
  * **2** --- **Working**

The operation commands that Electric Fan supports are:
  * **0** --- **Off**
  * **1** --- **On**

Some of Electric Fans have the capability of changing the strength or the
direction of the wind that they create.  For example, the user is able to
change the strength of the wind by operating physical buttons, and the
direction of the wind by rotating the head of the fan.

For those who want to control the strength or direction of the wind that an
Electric Fan creates, the following shared interfaces may be implemented:
  * **org.alljoyn.SmartSpaces.Environment.WindStrength**
  * **org.alljoyn.SmartSpaces.Environment.HorizontalWindDirection**
  * **org.alljoyn.SmartSpaces.Environment.VerticalWindDirection**

Some of Electric Fans involve a kind of intelligence to control the strength
and the direction of the wind by itself.

## Specification

|               |                                                       |
|---------------|-------------------------------------------------------|
| Version       | 1                                                     |
| Annotation    | org.alljoyn.Bus.Secure = true                         |

## References

  * [The XML definition of ElectricFan](ElectricFan-v1.xml)
  * [The definition of OperationalControl](/org.alljoyn.SmartSpaces.Operation/Control-v1)
  * [The definition of WindStrength](/org.alljoyn.SmartSpaces.Environment/WindStrength-v1)
  * [The definition of HorizontalWindDirection](/org.alljoyn.SmartSpaces.Environment/HorizontalWindDirection-v1)
  * [The definition of VerticalWindDirection](/org.alljoyn.SmartSpaces.Environment/VerticalWindDirection-v1)
