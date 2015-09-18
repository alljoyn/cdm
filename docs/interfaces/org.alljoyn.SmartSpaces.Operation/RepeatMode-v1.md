# org.alljoyn.SmartSpaces.Operation.RepeatMode version 1

## Theory of Operation

Interface that exposes On/Off control of device's Repeat mode. When the repeat
mode is on, the device repeats its operation. For example, when a robot cleaner 
works in a repeat mode, it will continue cleaning until its battery runs out.

## Specification

|            |                                                              |
|------------|--------------------------------------------------------------|
| Version    | 1                                                            |
| Annotation | org.alljoyn.Bus.Secure = true                                |

### Properties

#### Version

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | uint16                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Interface Version. The EmitsChangedSignal annotation can be modified to const 
once that feature is available.

#### RepeatMode

|            |                                                              |
|------------|--------------------------------------------------------------|
| Type       | boolean                                                      |
| Access     | read-write                                                   |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true      |

True if the device works in repeat mode.

Errors raised by the set method of this property:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- Indicates
that the given value was not acceptable due to internal state.
* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Indicates that
control from a remote site is currently disabled

### Methods

No methods defined for this interface.

### Signals

No signals defined for this interface.

### Interface Errors

The table below shows the possible errors raised by this interface.

| Error name                    | Error message                         |
|-------------------------------|---------------------------------------|
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled |Remote control disabled |

## References

  * The XML definition of the [RepeatMode](RepeatMode-v1.xml) interface.
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability](RemoteControllability-v1) interface.
