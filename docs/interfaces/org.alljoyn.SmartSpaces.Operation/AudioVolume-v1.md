# org.alljoyn.SmartSpaces.Operation.AudioVolume version 1

## Theory of Operation
This interface provides capabilities to control and monitor volume.

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

Interface version

#### Volume

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Speaker volume index of the device. Minimum volume is always 0 and volume value
is incremented by 1. If the controller tries to set a target value which is out
of range, then the controllee should return an appropriate error.

**Example**: AV receiver has volume range from -80.0 to +10.0 in 0.5 dB
increments. In this case, Minimum volume and maximum volume could be 0 and 180
and those values correspond to -80.0 dB and +10.0 dB. Incremental value, which
is 1, of **Volume** corresponds to 0.5dB. 

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### MaxVolume

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value allowed for Volume.

#### Mute

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | boolean                                                        |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Volume mute state. True indicates that volume is not muted, false
indicates volume is muted. When **Mute** property is set to true, the value
of **Volume** property might be changed to 0 depending on implementation. Also,
when **Mute** property is set to false, the value of **Volume** property might
be changed to previous value depending on implementation.

Errors raised when setting this property:

  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

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

#### Signals

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

  * The XML definition of the [AudioVolume interface](AudioVolume-v1.xml)
