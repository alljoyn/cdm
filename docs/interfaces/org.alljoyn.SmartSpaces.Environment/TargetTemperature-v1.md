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

The interface version.

#### TargetValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Target temperature, expressed in Celsius.

If the controller tries to set a target value which is out of range, then
the controllee should adjust the value to min/max value. If the controller
tries to set a target value which doesn't match with the granularity of
the current step, the device should set an appropriate value that can be
accepted.

Errors raised when setting this property:

  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### MinValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Minimum value of target temperature, expressed in Celsius.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value of target temperature, expressed in Celsius.


#### StepValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Step value allowed for TargetTemperature setting, expressed in Celsius.
~~It shall be a positive value.~~

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

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
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

