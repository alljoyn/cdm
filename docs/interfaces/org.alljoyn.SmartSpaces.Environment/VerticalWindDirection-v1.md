# org.alljoyn.SmartSpaces.Environment.VerticalWindDirection version 1

## Theory of Operation

This interface is for controlling vertical wind direction of a
device. AutoMode supports to control vertical wind direction automatically.

## Specification

|                       |                                                     |
|-----------------------|-----------------------------------------------------|
| Version               | 1                                                   |
| Annotation            | org.alljoyn.Bus.Secure = true                       |

### Properties

#### WindDirection

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Wind direction of a device. 0 means the highest position. MaxDirextion means the
lowest position. An error code shall be returned if a setpoint value is greater
than MaxDirection. Step value for WindDirection is always 1.

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
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

AutoMode is for controlling vertical wind direction of a device
automatically. If the AutoMode is eanbled, a high level device of this interface
controls the vertiacl wind direction automatically and the WindDirection
property of the interface should be changed according to changing wind direction.
If the AutoMode is disabled, the wind direction will remain at an appropriate
fixed direction determined by the device. (At this time, the value of wind
direction can be a default value or the value when the AutoMode is disabled.
This operation of auto control direction depends on the device manufacturer.)

The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Off** --- Auto mode is disabled.
  * 0x01 --- **On** --- Auto mode is enabled.
  * 0xFF --- **Not supported** --- Auto mode is not supported by the specific
  appliance.

### Methods

#### SetWindDirection(windDirection)

Set the wind direction. If the controller tries to set a target value which
is out of range, then an appropriate error shall be returned.

Input arguments:

  * **windDirection** --- uint16 --- Target value of wind direction

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### EnableAutoMode(autoMode)

Enable/Disable control of vertical wind direction. If auto mode is disabled,
vertical wind direction will remain at an appropriate fixed direction determined
by the controllee device. If the Automode is 0xFF(not supported),
this method shall not be used. In this case, if contoller call this method,
org.alljoyn.Error.FeatureNotAvailable shall be returned.

Input arguments:

  * **autoMode** --- boolean --- Enable/Disable auto mode

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if there is no selectable
  operational mode id.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

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

## References

  * The XML definition of the [VerticalWindDirection interface](VerticalWindDirection-v1.xml)
