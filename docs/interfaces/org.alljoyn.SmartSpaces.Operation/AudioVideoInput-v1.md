# org.alljoyn.SmartSpaces.Operation.AudioVideoInput version 1

## Theory of Operation
This interface provides capabilites to control and monitor audio video
input source of device such as TV or SetTopBox.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### InputSourceId

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Activated input source id in the supported input source list. The value
corresponds to the input source id in InputSource.

#### SupportedInputSources

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | InputSource[]                                                  |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The list of supported input sources for the given device.

### Methods

#### ChangeInputSource (inputSourceId)

Change the input source with InputSourceId.

Input arguments:
  * **inputSourceId** --- uint16 --- The value corresponds to the input source
  id in InputSource.

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct InputSource

  * **id** --- uint16 --- The input source id.  It will be used as to set the
  device input source.
  * **sourceType** --- uint16 --- The enumeration below lists source type.
    * Tuner : 0
    * Component : 1
    * Composite : 2
    * S-Video : 3
    * RGB : 4
    * DVI : 5
    * HDMI : 6
    * DisplayPort : 7
    * SCART : 8
    * External Storage : 9
    * Network : 10
  * **detectedState** --- byte --- The enumeration below lists detected state.
    * Detected : 0
    * Not detected : 1
    * Unknown : 2
  * **portNumber** --- uint16 --- When the device has plural HDMI input port, it
    could be distinguished by port number.
    ex) HDMI2 : sourceType is 6, portNumber is 2.
  * **representedName** --- string --- The represented name of input source is
    a UTF-8 encoded string. The controller should display this field to
    the end-user. ex) "HDMI-2", "RGB-PC"

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

  * The XML definition of the [AudioVideoInput interface](AudioVideoInput-v1.xml)
