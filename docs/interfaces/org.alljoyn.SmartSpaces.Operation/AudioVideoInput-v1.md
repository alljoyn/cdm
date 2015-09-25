# org.alljoyn.SmartSpaces.Operation.AudioVideoInput version 1

## Theory of Operation
This interface provides capabilities to control and monitor audio video
input source of device such as TV or SetTopBox.

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

#### InputSourceId

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Activated input source id in the supported input source list. The value
corresponds to the input source id in InputSource.

Errors raised when setting this property:
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### SupportedInputSources

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | InputSource[]                                                  |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The list of supported input sources for the given device.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct InputSource

  * **id** --- uint16 --- The input source id.  It will be used as to set the
  device input source.
  * **sourceType** --- uint16 --- The enumeration below lists source type.
    * Tuner : 0
    * [Component](#Component) : 1
    * [Composite](#Composite) : 2
    * [S-Video](#S-Video) : 3
    * [RGB](#RGB) : 4 
    * [SDI](#SDI) : 5
    * [DVI](#DVI) : 6
    * [HDMI](#HDMI) : 7
    * [DisplayPort](#DisplayPort) : 8
    * [SCART](#SCART) : 9
    * External Storage : 10
    * Network : 11
    * [Analog Audio](#AnalogAudio) : 12
    * [Phono](#AnalogAudio) : 13
    * [S/PDIF](#S/PDIF) - Coaxial : 14
    * [S/PDIF](#S/PDIF) - Optical : 15
  * **detectedState** --- byte --- The enumeration below lists detected state.
    * Unknown : 0
    * Detected : 1
    * Not detected : 2
  * **portNumber** --- uint16 --- When the device has plural HDMI input port, it
    could be distinguished by port number.
    ex) HDMI2 : sourceType is 7, portNumber is 2.
  * **friendlyName** --- string --- The friendly name of input source is a UTF-8
    encoded string. The controller should display this field to the end-user.
    ex) "HDMI-2", "RGB-PC"

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
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
<a name="Component"/a>
  * **Component**[CEA-770.2-D] - Standard Definition TV Analog Component Video Interface
<a name="Composite"/a>
  * **Composite** - Composite Analog Video Signal – NTSC for Studio Applications
<a name="S-Video"/a>
  * **S-Video**[IEC 60933-5] - Audio, video and audiovisual systems - Interconnections and
    matching values. Part 5: Y/C connector for video systems - Electrical
    matching values and description of the connector
<a name="RGB"/a>
  * **RGB**[NTSC/PAL] - National Television Systems Committee/Phase Alternating Line
<a name="SDI"/a>
  * **SDI**[SMPTE 259M,292M,344M,372M,424M] - Serial Digital Interface
<a name="DVI"/a>
  * **DVI** - Digital Visual Interface, Revision 1.0
<a name="HDMI"/a>
  * **HDMI** - High-Definition Multimedia Interface Version 1.4b
<a name="DisplayPort"/a>
  * **DisplayPort** - VESA DisplayPort
<a name="SCART"/a>
  * **SCART**[IEC 60933-1] - Audio, video and audiovisual systems - Interconnections and
    matching values. Part 1: 21-pin connector for video systems - Application
    No. 1
<a name="AnalogAudio"/a>
  * **AnalogAudio**[IEC 60268] - Sound system equipment.
<a name="S/PDIF"/a>
  * **S/PDIF**[lEC 60958-1] - Digital audio Interface. Part 1: General
