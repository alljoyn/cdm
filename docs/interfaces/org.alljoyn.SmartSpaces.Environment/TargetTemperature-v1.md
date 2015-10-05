# org.alljoyn.SmartSpaces.Environment.TargetTemperature version 1

## Theory of Operation
This interface is for setting target temperature of the HAE devices such as air
conditioner, refrigerator, oven, etc. The temperature is expressed in celsius.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### Version

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The interface version.The EmitsChangedSignal value of this property can be 
updated to "const" once that feature is available in Core.

#### SupportedSetPoints

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | SetPoint[]
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

List of supported set points. For each set point, a dictionary key, its allowed
minimum, maximum and step value for target temperature will be provided.

#### UpperActiveSetpoint
|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The dictionary key for a temperature that the device is attempting to keep the 
temperature below.  A traditional thermostat would call this a "COOL" setpoint.
This property is not intended to reflect any hysteresis.
A device like an Oven, or Thermostat in heat mode which can only actively
raise the temperature shall set the UpperActiveSetpoint to "".
This setpoint could also be "" if the cooling device is currently not
controlling using temperature.  For example an air-conditioner in a dehumidifier
mode.

Errors raised when setting this property:

* org.alljoyn.Error.InvalidValue --- Returned if value is not valid.  This
will be returned becuase the string is not a valid key, if setting to the same 
key as LowerActiveSetpoint.
* org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
if value is not acceptable due to internal state.
* org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
control is disabled. See the RemoteControllability property in the 
[RemoteControllability interface](RemoteControllability-v1) for further information.

#### LowerActiveSetpoint
|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The dictionary key for a temperature that the device is attempting to keep the 
temperature above.  A traditional thermostat would call this the "HEAT" setpoint.
This property is not intended to reflect any hysteresis.
A device that can only actively lower temperature, such as a refrigerator or 
air conditioner in cool mode should set this at "".
This setpoint could also be "" if the heating device is currently not 
controlling using temperature.  For example a portable heater on a fixed duty-
cycle or always on mode. 

Errors raised when setting this property:

* org.alljoyn.Error.InvalidValue --- Returned if value is not valid.  This
will be returned because the string is not a valid key, if setting to the same 
key as UpperActiveSetpoint.
* org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
if value is not acceptable due to internal state.
* org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
control is disabled. See the RemoteControllability property in the 
[RemoteControllability interface](RemoteControllability-v1) for further information.

### Methods

#### GetTargetTemperatures(keys) -> targetTemperatures

Used to get target temperature(s) for one or more set points.

Input arguments:

* **keys** --- string[] --- List of dictionary keys for each set point to get

Output arguments:

* **targetTemperatures**  ---TargetTemperature[] --- List of target temperatures

Errors raised by this method:
* org.alljoyn.Error.InvalidValue --- if there is(are) invalid key(s) in the input arguments.

#### SetTargetTemperatures(targetTemperatures)

Used to set target temperature(s) for one or more set points.

Input arguments:

* **targetTemperatures**  ---TargetTemperature[] --- List of target temperatures to set

If the controller tries to set a target value which is out of range, the value 
shall be then set to the limit of the range.  
If the controller tries to set a target value which doesn't match with the 
granularity of the current step, the device shall round TargetValue using a
device specific algorithm.

Errors raised by this method:
* org.alljoyn.Error.InvalidValue --- if there is(are) invalid key(s) in the input arguments.
* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
key or celcius value is not accepted by the _producer_
* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
control is disabled. See the RemoteControllability property in the 
[RemoteControllability interface](RemoteControllability-v1) for further information.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct SetPoint

* ** key ** -- string -- a dictionary key for each set point
* ** min ** -- double -- a minimum value allowed for each set point temperature, 
  expressed in Celsius. If there is no minimum value available, this shall 
  be set to 0xFFF0000000000000.
* ** max ** -- double -- a maximum value allowed for each set point temperature, 
  expressed in Celsius. If there is no maximum value available, this shall 
  be set to 0x7FF0000000000000.
* ** step ** -- double -- a step value allowed for each set point temperature, 
  expressed in Celsius. This shall be a non-negative value. If there is no step 
  value available, this shall be set to 0.

#### struct TargetTemperature

* ** key ** -- string -- a dictionary key for each set point
* ** temperature ** -- double -- a target temperature for each set point

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

* The XML definition of the [TargetTemperature interface](TargetTemperature-v1.xml)
* The [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)
* The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)


