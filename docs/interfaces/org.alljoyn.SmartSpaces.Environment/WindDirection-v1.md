# org.alljoyn.SmartSpaces.Environment.WindDirection version 1

## Theory of Operation

WindDirection interface is for controlling wind direction of a device. AutoMode
supports to control wind direction automatically.

## Specification

|                       |                                                     |
|-----------------------|-----------------------------------------------------|
| Version               | 1                                                   |
| Annotation            | org.alljoyn.Bus.Secure = true                       |

### Properties

#### Version

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Interface version

#### DirectionType

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Type of wind direction.
0 : Horizontal
1 : Vertical

#### WindDirection

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Wind direction of a device. 0 means the leftmost/highest position. MaxDirection
means the rightmost/lowest position. An error code shall be returned if a
setpoint value is greater than MaxDirection. Step value for WindDirection is
always 1. All directions are based on the user's view, where the user is at the
front of an object which contains this interface.

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### MaxDirection

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

Maximum value allowed for a target wind direction. 0 means that device doesn't
support to set and represent the wind direction.

#### AutoMode

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

AutoMode is for controlling wind direction of a device automatically. If the
AutoMode is enabled, a high level device of this interface controls the wind
direction automatically and the WindDirection property of the interface should
be changed according to changing wind direction.
If the AutoMode is disabled, the wind direction will remain at an appropriate
fixed direction determined by the device. (At this time, the value of wind
direction can be a default value or the value when the AutoMode is disabled.
This operation of auto control direction depends on the device manufacturer.)

The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Off** --- Auto mode is disabled.
  * 0x01 --- **On** --- Auto mode is enabled.
  * 0xFF --- **Not supported** --- Auto mode is not supported by the specific
  appliance.

The controller shall not set 0xFF(not supported).
If the controller tries to set a value when the value is 0xFF,
org.alljoyn.Error.FeatureNotAvailable shall be returned.

Errors raised when setting this property:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if there is no selectable
  operational mode id.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling feature
(`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error message. The table
below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not supported                              |
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

### References

  * The XML definition of the [WindDirection interface](WindDirection-v1.xml)
