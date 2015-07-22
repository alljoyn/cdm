# org.alljoyn.SmartSpaces.Devices.Television version 1

## Theory of Operation

Television(TV) is a home appliance used to show audio and visual contents
such as broadcasting program and network streaming. This TV interface provides
capabilities to control and monitor TV specific resources. A controller can
recognize this device as a TV if object descriptions of the About announcement
include this interface.

The followings are minimum required shared interfaces for TV.
  * **org.alljoyn.SmartSpaces.Operation.Control** --- for control of operation
  * **org.alljoyn.SmartSpaces.Operation.AudioVolume** --- for control of audio
  volume

The operation states that TV supports are:
  * **0** --- **Off**
  * **2** --- **Working**

The operation commands that TV supports are:
  * **0** --- **Off**
  * **1** --- **On**

A typical TV could have some other shared interfaces and the followings are
examples.
  * **org.alljoyn.SmartSpaces.Operation.TelevisionChannel** --- for control of
  channel selection
  * **org.alljoyn.SmartSpaces.Operation.AudioVideoInput** --- for control of
  external input selection
  * **org.alljoyn.SmartSpaces.Operation.VirtualKey** --- for control of TV by
  its remote
  * **org.alljoyn.SmartSpaces.Operation.Mouse** --- for control of TV by mouse
  device
  * **org.alljoyn.SmartSpaces.Operation.Display** --- for exposing display
  characteristics

## Specification
|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

No Properties are implemented by this interface.

### Methods

No Methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No unique errors are associated with this interface.

## References

  * The XML definition of the [Television interface](Television-v1.xml)
  * The definition of the [OperationalControl interface](/org.alljoyn.SmartSpaces.Operation/Control-v1)
  * The definition of the [AudioVolume interface](/org.alljoyn.SmartSpaces.Operation/AudioVolume-v1)
  * The definition of the [TelevisionChannel interface](/org.alljoyn.SmartSpaces.Operation/TelevisionChannel-v1)
  * The definition of the [AudioVideoInput interface](/org.alljoyn.SmartSpaces.Operation/AudioVideoInput-v1)
  * The definition of the [VirtualKey interface](/org.alljoyn.SmartSpaces.Operation/VirtualKey-v1)
  * The definition of the [Mouse interface](/org.alljoyn.SmartSpaces.Operation/Mouse-v1)
  * The definition of the [Display interface](/org.alljoyn.SmartSpaces.Operation/Display-v1)
