# org.alljoyn.SmartSpaces.Devices.Humidifier version 1

## Theory of Operation

Humidifier is a home appliance used to increase humidity (moisture) in a single
room or an entire building. This humidifier interface provides capabilities to
control and monitor humidifier specific functions and resources. A controller
can recognize this device as a humidifier if object descriptions of the About
announcement include this interface

The followings are minimum required shared interfaces for humidifier.
  * **org.alljoyn.SmartSpaces.Operation.Control** --- for start/stop operation

Most humidifiers have capabilities to control and monitor target humidity or
moisture output rate. If humidifier has a capability to adjust qualitative
moisture output rate such as "Low", "Mid", "High", the MoistureOutput shared
interface can be used. If humidifier has setting of target humidity, the device
can use the TargetHumidity shared interface. Advanced humidifier can have both
of two capabilities.

In those cases following shared interfaces are implemented:

  * **org.alljoyn.SmartSpaces.Environment.TargetHumidity** --- for setting
  target humidity
  * **org.alljoyn.SmartSpaces.Environment.MoistureOutput** --- for setting
  rate of moisture output

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

No Properties are implemented by this interface.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No unique errors are associated with this interface.

## References

  * The XML definition of the [Humidifier interface](Humidifier-v1.xml)
  * The definition of the [Operation Control interface](/org.alljoyn.SmartSpaces.Operation/Control-v1)
  * The definition of the [TargetHumidity interface](/org.alljoyn.SmartSpaces.Environment/TargetHumidity-v1)
  * The definition of the [MoistureOutputinterface](/org.alljoyn.SmartSpaces.Environment/MoistureOutput-v1)
