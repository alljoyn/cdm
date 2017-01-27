# org.alljoyn.SmartSpaces.Operation.Color version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e., a remote application) the
capability to directly set the color, through hue and saturation values, of the
_producer_ (i.e., the appliance).

This interface is intended to be implemented by a device that supports color with
a fixed brightness, e.g., a lamp that can change color without being dimmed.
It can also be combined with the **org.alljoyn.SmartSpaces.Operation.Brightness**
interface to achieve the full HSV (Hue, Saturation, and Value) color model.


## Specification

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Version               | 1                                                                     |
| Annotation            | org.alljoyn.Bus.Secure = true                                         |


### Properties

#### Version

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | uint16                                                                |
| Access                | read                                                                  |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = const              |

The interface version.

#### Hue

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | double                                                                |
| Access                | readwrite                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |
| Annotation            | org.alljoyn.Bus.Type.Min = 0.0                                        |
| Annotation            | org.alljoyn.Bus.Type.Max = 360.0                                      |

Contains the current hue of the device.

The following diagram demonstrates how hue values should be represented.  
![0.0=Red, 180.0=Cyan, 360.0=Red][ColorWheel]
[ColorWheel]: HueColorWheel.png

 * Note: A hue value of 0.0 and 360.0 are equivalent.

#### Saturation

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | double                                                                |
| Access                | readwrite                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |
| Annotation            | org.alljoyn.Bus.Type.Min = 0.0                                        |
| Annotation            | org.alljoyn.Bus.Type.Max = 1.0                                        |

Contains the current saturation of the device.

Without **org.alljoyn.SmartSpaces.Operation.Brightness**:

 * The minimum value of 0.0 indicates zero color. The _producer_ will have to decide
   how this is represented as the brightness value is undefined.

 * The maximum value of 1.0 indicates pure color as specified by the hue value.
   The _producer_ will have to decide how this is represented as the brightness
   value is undefined.

When combined with **org.alljoyn.SmartSpaces.Operation.Brightness**:

 * The minimum value of 0.0 is combined with the brightness value to create a range
   from black to white.  
   i.e.  
    * A saturation of 0.0 and brightness of 0.0 is black.  
    * A saturation of 0.0 and brightness of 1.0 is white.  

 * The maximum value of 1.0 is combined with the brightness value to create a range
   of black to the pure color specified by the hue.  
   i.e.  
    * A saturation of 1.0 and brightness of 0.0 is black.  
    * A saturation of 1.0 and brightness of 1.0 is the color specified by the hue.  

#### Devices that use a different internal color model

For devices that internally represent color using a different model (e.g., RGB, CIE XYZ, etc), the exposed interface to AllJoyn
should be HSV as specified by above.

#### Devices supporting a subset of colors

For devices that only support a subset of colors, i.e., a 256 fixed color palette, the _Hue_ and _Saturation_
property values should snap to the closest supported color.

Changing the _Hue_ property might mean the _Saturation_ property needs to be adjusted to match the nearest
supported color and vice versa.

### Methods

No methods are exposed by this interface.

### Signals

No signals are exposed by this interface.

### Interface Errors

No error associated to this interface.

## References

  * The [Color interface](Color-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v2)
  * The description of the [Brightness interface](Brightness-v1)
