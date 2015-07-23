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

#### WindStrength

|                  |                                                          |
|------------------|----------------------------------------------------------|
| Type             | byte                                                     |
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Wind Strength of a device. 1 means the lowest setting of continuous fan
operation. MaxStrength means the highest setting of continuous fan operation.
Step value is always 1.

Special reserved values listed below:
  * 0x00 --- **Off** --- Fan operation is turned off.

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
| Access           | read-only                                                |
| Annotation       | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

AutoMode is for automatic control of wind strength. If the AutoMode is enabled,
a high level device of this interface controls the wind strength automatically
and the WindStrength property shall be changed according to changing wind
strength. If the AutoMode is disabled, the wind strength will remain at an
appropriate fixed strength determined by the device. (The fixed value of wind
strength can be a default value or the value when the AutoMode is disabled. This
operation of auto control wind strength depends on the device manufacturer.)

The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Off** --- Auto mode is disabled.
  * 0x01 --- **On** --- Auto mode is enabled.
  * 0xFF --- **Not supported** --- Auto mode is not supported by the specific
  appliance.

### Methods

#### SetWindStrength(windStrength)

Set the wind strength. The controller shall not set 0x00(Off) to turn off the
fan operation. Turning on/off shall be operated by the OperationalControl
interface. Only highlevel device of this interface can set 0x00 internally when
the fan operation is turned off. If the controller tries to set 0x00,
org.alljoyn.Error.InvalidValue error shall be returned.

Input arguments:

  * **windStrength** --- byte --- Target value of wind strength

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### GetWindStrengthInfo (languageTag) -> (info)

Get added information about the wind strength which are supported by
the appliance. It is used to communicate to controller the names and
descriptions of rates supported by the appliance, so they can be available by
the remote controller.

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
  using IETF language tags specified by RFC 5646.

Output arguments:

  * **info** --- string[] --- the list of wind strength
     * empty: there are no string to communicate
     * list a string for each element from 0 to **MaxWindStrength**
     examples of output are: "low", "med", "high"

Errors raised by this method:

  * org.alljoyn.Error.LanguageNotSupported --- The language specified is not
    supported.

#### EnableAutoMode(autoMode)

Enable/Disable auto control of wind strength. If auto mode is disabled, wind
strength will remain at an appropriate fixed strength determined by the
controllee device. If the Automode is 0xFF(not supported), this method shall
not be used. In this case, if contoller call this method,
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

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not supported                              |
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.Error.LanguageNotSupported                        | The language specified is not supported            |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

  * The XML definition of the [WindStrength interface](WindStrength-v1.xml)
