# org.alljoyn.SmartSpaces.Devices.AirPurifier version 1

## Theory of Operation

Air purlifier is a home appliance used to purify air in a single room or 
an entire building. 

The followings are minimum required shared interfaces for an air purifier.

  * **org.alljoyn.SmartSpaces.Operation.OperationControl** --- for start/stop operation

The followings are examples of shared interfaces expected to be commonly 
used for an air purifier.

If there are a plurality of air quality types measurable by an air 
purifier, then a plurality of bus objects with air quality level 
interfaces with different air quality types are expected as direct 
children of the bus object with this (air purifier device) interface.

  * **org.alljoyn.SmartSpaces.Environment.CurrentAirQuarityLevel**
  * **org.alljoyn.SmartSpaces.Environment.CurrentCo2Concentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentCoConcentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentPm2_5Concentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentPm10Concentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentCh2oConcentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentVocConcentration**
  * **org.alljoyn.SmartSpaces.Environment.WindStrength**
  * **org.alljoyn.SmartSpaces.Operation.FilterStatus**
 
The following is an example of a shared interface expected to be 
commonly used for an air purifier with a water tank.

  * **org.alljoyn.SmartSpaces.Environment.WaterLevel**

The following is an example of a shared interface expected to be 
commonly used for an air purifier with humidifying capability.

  * **org.alljoyn.SmartSpaces.Environment.MoistureOutput**

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### TurboMode

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Turbo on/off status.
When turbo mode is on, the effect of purifying air increases.

  * **0** --- **Off**
  * **1** --- **On**
  * **255** --- **Not Available or Unknown**

### Methods

#### EnableTurboMode (turboMode)

Enable turbo mode. 
If the device cannot enable/disable turbo mode due to its internal state, 
then an appropriate error shall be returned.

Input arguments:

  * **turboMode** --- boolean --- true: enable, false: disable

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- Value not supported
  * org.alljoyn.Error.FeatureNotAvailable --- Feature (Turbo mode) not available by the device
  * org.alljoyn.SmartSpaces.Error.RemoteContolDisabled --- Remote control disabled
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- The value is not acceptable due to internal state

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling feature
(`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error message. The table
below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                     |
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not available                             |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The Value is not acceptable due to internal state |

## References

  * The XML definition of the [AirPurifier interface](AirPurifier-v1.xml)
