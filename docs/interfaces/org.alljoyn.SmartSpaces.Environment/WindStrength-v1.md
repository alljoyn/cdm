# org.alljoyn.SmartSpaces.Environment.WindStrength version 1

## Theory of Operation

WindStrength interface is for controlling wind strength of a device. The
AutoMode supports to control wind strength automatically.

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

The Interface version

#### WindStrength

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Wind Strength of a device. 1 means the lowest setting of continuous fan
operation. MaxStrength means the highest setting of continuous fan operation.
Step value is always 1.

Special reserved values listed below:
  * 0x00 --- **Off** --- Fan operation is turned off.

The controller shall not set 0x00(Off) to turn off the fan operation. Turning
on/off shall be operated by the OnOff interface. Only highlevel
device of this interface can set 0x00 internally when the fan operation is
turned off. If the controller tries to set 0x00, org.alljoyn.Error.InvalidValue
error shall be returned.

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### MaxStrength

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

Maximum strength allowed for target wind strength.

#### AutoMode

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-write                                               |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

AutoMode is for automatic control of wind strength. If the AutoMode is enabled,
a high level device of this interface controls the wind strength automatically
and the WindStrength property shall be changed according to changing wind
strength. If the AutoMode is disabled, the wind strength will remain at an
appropriate fixed strength determined by the device. (The fixed value of wind
strength can be a default value or the value when the AutoMode is disabled.
It depends on the device implementation.)

The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Off** --- Auto mode is disabled.
  * 0x01 --- **On** --- Auto mode is enabled.
  * 0xFF --- **Not supported** --- Auto mode is not supported by the specific
  appliance.

The controller shall not set 0xFF(not supported).
If the controller tries to set a value when the value is 0xFF,
org.alljoyn.Error.FeatureNotAvailable shall be returned.

Errors raised when setting this property:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if a controller tries to
  set this property when the AutoMode is not supported.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not supported                              |
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

  * The XML definition of the [WindStrength interface](WindStrength-v1.xml)
