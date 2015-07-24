# org.alljoyn.SmartSpaces.Operation.AudioVolume version 1

## Theory of Operation
This interface provides capabilites to control and monitor volume.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

#### Properties

#### Volume

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Speaker volume index of the device. Minimum volume is always 0.

#### StepValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Step value of volume control.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value allowed for Volume.

#### Muted

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The state of volume muted. If mute value is changed, changing value of volume
property depends on device implementation.

The property data type is an enumeration and its allowed value are listed below:
  * 0x00 --- **Not muted** --- Volume is not muted
  * 0x01 --- **Muted** --- Volume is muted
  * 0xFF --- **Not supported** --- Volume mute is not supported by the specific
appliance.

### Methods

#### UpVolume ()

Up volume to the next available value.

Input arguments: None.

Output arguments: None.

Errors raised by this method:
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### DownVolume ()

Down volume to the next available value.

Input arguments: None.

Output arguments: None.

Errors raised by this method:
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### ChangeVolume (volume)

Change the volume. If the controller tries to set a target value which is out of
range, then an appropriate error should be returned. In case that the Volume is
in range defined by MaxValue, but it is not on the grid in terms of StepValue,
the controllee can set an appropriate value without returning an error, or it
can refuse the target value and return an appropriate error. If StepValue = 0,
it means there is no step value information available for the controllee device.
In this case, the controllee will go to an appropriate value that can be
accepted without returning an error.

Input arguments:

  * **volume** --- byte --- target volume value

Output arguments: None.

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

##### EnableMute(mute)

Enable/Disable volume mute of device.

Input arguments:
  * **mute** --- boolean --- Enable/Disable volume mute

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if there is no selectable
  operational mode id.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### Signals

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

  * The XML definition of the [AudioVolume interface](AudioVolume-v1.xml)
