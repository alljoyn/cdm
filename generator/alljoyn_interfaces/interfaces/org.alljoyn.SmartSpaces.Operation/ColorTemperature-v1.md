# org.alljoyn.SmartSpaces.Operation.ColorTemperature version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e., a remote application) the
capability to directly set the color temperature in kelvins (K) of the _producer_ (i.e., the appliance).

This interface is intended to be implemented by devices that emit light, e.g., lamps, screens, etc.


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

#### Temperature

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | double                                                                |
| Access                | readwrite                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |
| Annotation            | org.alljoyn.Bus.Type.Min = 0.0                                        |
| Annotation            | org.alljoyn.Bus.Type.Units = K                                        |

Holds the current color temperature in kelvins (K).

The following diagram demonstrates how the temperature value relates to color.  
![1000K=Candle, 3000K=Warm White, 5000K=Cool White][ColorTemp]
[ColorTemp]: ColorTemperature.png

The range defined by the properties _MinTemperature_ and _MaxTemperature_ is the valid range
for the _Temperature_ property but a value of 0.0 is reserved to represent an invalid state (e.g., when a different color model is active).

#### MinTemperature

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | double                                                                |
| Access                | read                                                                  |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = const              |
| Annotation            | org.alljoyn.Bus.Type.Min = 0.0                                        |
| Annotation            | org.alljoyn.Bus.Type.Units = K                                        |

A read only property that defines the lowest supported color temperature.

#### MaxTemperature

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | double                                                                |
| Access                | read                                                                  |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = const              |
| Annotation            | org.alljoyn.Bus.Type.Min = 0.0                                        |
| Annotation            | org.alljoyn.Bus.Type.Units = K                                        |

A read only property that defines the highest supported color temperature.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No errors associated to this interface.

## References

  * The [ColorTemperature interface](ColorTemperature-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v2)
