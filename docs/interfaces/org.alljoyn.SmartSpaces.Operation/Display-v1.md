# org.alljoyn.SmartSpaces.Operation.Display version 1

## Theory of Operation

This Display interface provides capabilities to control and monitor Display
specific resources. Some other definitions which indicate the characteristic
of Display might be added in the future.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### PhysicalResolution

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | Resolution                                                     |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

This is actual resolution of display such like 1920 x 1080 for FHD and
3840 x 2160 for QFHD(4K).

A use case example of this property.
A smartphone(as a controller) can select a proper Display device to establish
Miracast or DLNA content playback if it knows the Display's physical resolution
in advance. If you have a 4K photo, it's better to push the content to 4K
Display device.

#### GraphicalResolution

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | Resolution                                                     |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

This is the active graphical plane resolution which is used for displaying
graphical user interface (GUI). When this graphical plane is drawn on the
actual display, the GUI would be expanded fully to match the physical display.

A use case example of this property.
In the case that a smartphone(as a controller) has a touch pad mouse app,
it can adjust speed of mouse pointer move if it knows the Display's graphical
plane resolution in advance.

For the devices that do not use different resolutions for physical and GUI
resolutions, physical resolution should be set in GraphicalResolution.


### Methods

No Methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct Resolution

 * **width** --- uint16 --- The width of display resolution.
 * **height** --- uint16 --- The height of display resolution.

### Interface Errors

No unique errors are associated with this interface.

## References

  * The XML definition of the [Dispaly interface](Display-v1.xml)
