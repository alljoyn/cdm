# org.alljoyn.SmartSpaces.Environment.TargetTemperature version 1

## Theory of Operation
This interface is for setting target temperature of the HAE devices such as air
conditioner, refrigerator, oven, etc. The temperature is expressed in degrees
celsius.
If a device needs to support multiple TargetTemperatures it shall implement each
on a separate bus object path and use well identified names for the paths to allow for
interoperability.
Because of the variety of devices and use cases that could support a
TargetTemperature the specific names will be documented by the parent device or
interface that requires a special naming convention.  That allows for additional
device types with their own naming convention.

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

The interface version.  The EmitsChangedSignal annotation of this property
should change to const once that feature is available in core.

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
If no target temperature is available this will read 7fff ffff ffff ffff (NaN).

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

Minimum value of target temperature, expressed in Celsius.  A minimum value is
required there is no special value for unavailable.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value of target temperature, expressed in Celsius.   A maximum value is
required there is no special value for unavailable.

#### StepValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Step value allowed for TargetTemperature setting, expressed in Celsius.
Zero indicates that their is no defined step, any value between MinValue and
MaxValue will be accepted.

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
* The [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)
* The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)


