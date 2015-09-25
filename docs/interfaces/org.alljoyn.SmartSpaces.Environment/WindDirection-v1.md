# org.alljoyn.SmartSpaces.Environment.WindDirection version 1

## Theory of Operation

WindDirection interface is for controlling wind direction of a device.
Horizontal/VerticalAutoMode supports to control wind direction automatically.

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

#### HorizontalDirection

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Horizontal wind direction of a device. 0 means the leftmost position.
HorizontalMax means the rightmost position. The device should adjust the value
to HorizontalMax value if a setpoint value is greater than HorizontalMax.
Step value for HorizontalDirection is always 1.
All directions are based on the user's view, where the user is at the
front of an object which contains this interface.

Errors raised when setting this property:

  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
    if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
    control is disabled.

#### HorizontalMax

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Maximum value allowed for a target horizontal wind direction. 0 means that
device doesn't support to set and represent horizontal wind direction.

#### HorizontalAutoMode

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

HorizontalAutoMode is for controlling horizontal wind direction of a device
automatically. If HorizontalAutoMode is enabled, a high level device of this
interface controls horizontal wind direction automatically and HorizontalWind
property of the interface should be changed according to changing wind direction.
If HorizontalAutoMode is disabled, horizontal wind direction will remain at an
appropriate fixed direction determined by the device. (At this time, the value
of HorizontalDirection can be a default value or the value when HorizontalAutoMode is
disabled. It depends on the device implementation.)

The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Off** --- Auto mode is disabled.
  * 0x01 --- **On** --- Auto mode is enabled.
  * 0xFF --- **Not supported** --- Auto mode is not supported by the specific
    appliance.

The controller shall not set 0xFF(not supported).
If the controller tries to set a value when the value is 0xFF,
org.alljoyn.Error.FeatureNotAvailable shall be returned.

Errors raised when setting this property:

  * org.alljoyn.Error.FeatureNotAvailable --- Returned if a controller tries to
  set this property when HorizontalAutoMode is not supported.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
    if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
    control is disabled.

#### VerticalDirection

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Vertical wind direction of a device. 0 means the lowest position. VerticalMax
means the highest position. The device should adjust the value
to VerticalMax value if a setpoint value is greater than VerticalMax.
Step value for VerticalDirection is always 1.

Errors raised when setting this property:

  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
    if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
    control is disabled.

#### VerticalMax

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | uint16                                                   |
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Maximum value allowed for a target vertical wind direction. 0 means that device
doesn't support to set and represent vertical wind direction.

#### VerticalAutoMode

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

VerticalAutoMode is for controlling vertical wind direction of a device
automatically. If VerticalAutoMode is enabled, a high level device of this
interface controls vertical wind direction automatically and VerticalDirection
property of the interface should be changed according to changing wind direction.
If VerticalAutoMode is disabled, vertical wind direction will remain at an
appropriate fixed direction determined by the device. (At this time, the value
of VerticalDirection can be a default value or the value when VerticalAutoMode is
disabled. It depends on the device implementation.)


The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Off** --- Auto mode is disabled.
  * 0x01 --- **On** --- Auto mode is enabled.
  * 0xFF --- **Not supported** --- Auto mode is not supported by the specific
    appliance.

The controller shall not set 0xFF(not supported).
If the controller tries to set a value when the value is 0xFF,
org.alljoyn.Error.FeatureNotAvailable shall be returned.

Errors raised when setting this property:

  * org.alljoyn.Error.FeatureNotAvailable --- Returned if a controller tries to
  set this property when VerticalAutoMode is not supported.
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
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

### References

  * The XML definition of the [WindDirection interface](WindDirection-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)
