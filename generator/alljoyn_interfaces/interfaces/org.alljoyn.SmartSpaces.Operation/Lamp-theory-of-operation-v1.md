## Lamp Theory of Operation version 1

This theory of operation explains the interaction of various interfaces to
assemble a lamp with varying functionality.


### Overview

The definition of a lamp is any type of single lighting device such as a light globe.
The Common Device Model (CDM) service framework defines a common set of standard interfaces that work
across multiple device types. This document illustrates how to combine a subset
of those interfaces to monitor and control different types of lighting functionality.  

#### Relationship to the Lighting Service Framework (LSF)
The LSF is a legacy framework for AllJoyn that is being phased out.  

The CDM aims to replace the LSF and thus redefines a number of interfaces specified by the LSF. The LSF interfaces are incompatible 
with guidelines established by the Interface Review Board. If the device isn't required to work with legacy LSF controllers, 
then the CDM interfaces should be preferred.  

It is possible for a device to implement both the CDM and LSF lighting interfaces. This will enable the device to work with both
legacy LSF controllers and CDM controllers simultaneously.  

Below is a table that specifies how the CDM interfaces map to the org.alljoyn.LSF.LampState interface.  

| org.alljoyn.SmartSpaces.Operation | org.alljoyn.LSF       | Mapping of values from LSF to CDM lighting properties                         |
|-----------------------------------|-----------------------|-------------------------------------------------------------------------------|
| Brightness.Brightness             | LampState.Brightness  | LampState.Brightness[0, MAX_UINT32] -> Brightness.Brightness[0.0, 1.0]        |
| Color.Hue                         | LampState.Hue         | LampState.Hue[0, MAX_UINT32] -> Color.Hue[0.0, 360.0]                         |
| Color.Saturation                  | LampState.Saturation  | LampState.Saturation[0, MAX_UINT32] -> Color.Saturation[0.0, 1.0]             |
| ColorTemperature.Temperature      | LampState.ColorTemp   | LampState.ColorTemp[0, MAX_UINT32] -> ColorTemperature.Temperature[MIN, MAX]* |
| OnOffStatus.IsOn                  | LampState.OnOff       | LampState.OnOff -> OnOffStatus.IsOn (as read only)                            |
| OnControl.SwitchOn()              | LampState.OnOff       | LampState.OnOff -> true                                                       |
| OffControl.SwitchOff()            | LampState.OnOff       | LampState.OnOff -> false                                                      |

() Signifies a method  
* MIN and MAX as specified by the org.allseen.SmartSpaces.ColorTemperature.MinTemperature and org.allseen.SmartSpaces.ColorTemperature.MaxTemperature properties.


### A Simple System

#### org.alljoyn.SmartSpaces.Operation.OnOffStatus

This interface provides the capability to monitor the on/off power status of
the lamp. The use of only this interface could coincide with the presence of a
physical switch that controls the lamp's power so only monitoring functionality is exposed.

#### OnOffStatus Combined with the OnControl and OffControl interfaces

The interfaces ***org.alljoyn.SmartSpaces.Operation.OnControl*** and
***org.alljoyn.SmartSpaces.Operation.OffControl*** provide functionality to fully
control the power operation of the lamp. A lamp with or without a physical switch
may want to provide this combination as a means to remotely turn lights on or off
or alter the power status driven by some other event.


### Some More Complex Systems

#### org.alljoyn.SmartSpaces.Operation.Brightness

Some lamps are made with the ability to have multiple brightness levels. This interface
exposes functionality that directly sets a lamp's brightness. A non colored but
dimmable lamp may want to use this interface.

#### org.alljoyn.SmartSpaces.Operation.Color

Some lamps are made with the ability to alter their color. This interface exposes
functionality to directly set both the hue and the saturation for the lamp. A use
case where only the Color interface is used is for a lamp that is acting as part
of a monitoring service. Depending on the state of what is being monitored, the
lamp might shift its hue from green to red or some other user defined color.

#### Combining Brightness and Color to create a complete HSV (hue, saturation and value) color model

The combination of both ***org.alljoyn.SmartSpaces.Operation.Color*** and
***org.alljoyn.SmartSpaces.Operation.Brightness*** provide the means to express
the color of the lamp using the HSV color model. This color model provides an intuitive 
representation of color in that the hue value represents the actual color and the saturation 
is amount of that color relative to the brightness. The documentation for ***org.alljoyn.SmartSpaces.Operation.Color***
provides a more in depth explanation of how the Color and Brightness interfaces combine to form the HSV model.

#### org.alljoyn.SmartSpaces.Operation.ColorTemperature

Some lamps provide the capability to tune their color temperature. This interface can be used independently
of ***org.alljoyn.SmartSpaces.Operation.Color*** to provide the ability to adjust the warmth of the white emitted by 
the device (see the documentation for [org.alljoyn.SmartSpaces.Operation.ColorTemperature](ColorTemperature-v1) for details).

#### Lamps that use both org.alljoyn.SmartSpaces.Operation.Color and org.alljoyn.SmartSpaces.Operation.ColorTemperature

When _ColorTemperature_ is composed along side the _Color_ interface, the recommended behavior is that these two
color models behave in a mutually exclusive manner. If the _Hue_ or _Saturation_ property is changed, _Color_ becomes the active color model
and the _Temperature_ property should be set to 0.0 (i.e., an invalid state). If the _Temperature_ property is adjusted, _ColorTemperature becomes
the active interface and the _Saturation_ property should be set to 0.0 so the _Color_ interface reports as colorless (i.e, as white).
  
By altering the property of the opposing color model, a signal is emitted that the property has been changed. This alerts all
clients to the invalidation of the previous color model.