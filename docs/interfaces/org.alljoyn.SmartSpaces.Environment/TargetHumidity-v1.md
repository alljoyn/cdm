# org.alljoyn.SmartSpaces.Environment.TargetHumidity version 1

## Theory of Operation
This interface is for setting target humidity of the HAE devices such as
humidifier, dehumidifier, etc.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### TargetValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Target value for relative humidity. Relative humidity is the ratio of the
partial pressure of water vapor to the equilibrium vapor pressure of water at
the same temperature. If the controller tries to set a target value which is
out of range, then an error should be returned. In case that the TargetValue is
in range defined in MinValue and MaxValue, but it is not on the grid in terms of
StepValue, the controllee can set an appropriate value without returning an
error, or it can refuse to accept the TargetValue and return an appropriate
error. If StepValue = 0, it means there is no step value information available
for the controllee device. In this case, the controllee will go to an
appropriate value that can be accepted without returning an error.

#### MinValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Minimum value allowed for TargetValue. MinValue can’t be less than 0.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value allowed for TargetValue. MaxValue can’t be greater than 100.

#### StepValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Step value allowed for TargetValue(%) setting. The step of humidity increment or
decrement can be different for each device. The step can be 1%, 5%, and 10%, etc.
Starting from MinValue, valid target value will be represented. Difference
between MaxValue and MinValue should be a multiple of StepValue.

### Methods

#### SetTargetHumidity (humidity)

Set target value for relative humidity. Relative humidity is the ratio of the
partial pressure of water vapor to the equilibrium vapor pressure of water at
the same temperature. If the controller tries to set a target value which is out
of range, then an error should be returned. In case that the TargetValue is in
range defined in MinValue and MaxValue, but it is not on the grid in terms of
StepValue, the controllee can set an appropriate value without returning an
error, or it can refuse to accept the targetValue and return an appropriate
error. If StepValue = 0, it means there is no step value information available
for the controllee device. In this case, the controllee will go to an
appropriate value that can be accepted without returning an error.

Input arguments:

  * **humidity** --- byte --- Target humidity value.

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpace.NotAcceptableDueToInternalState --- Returned if
  value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpace.RemoteControlDisabled --- Returned if remote
  control is disabled.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.


| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

  * The XML definition of the [TargetHumidity interface](TargetHumidity-v1.xml)
