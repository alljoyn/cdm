# org.alljoyn.SmartSpaces.Operation.ResourceSaving version 1

## Theory of Operation

Resource Saving is one of the operation modes of an appliance, in which the
appliance consumes less energy or resources than that in another, usually with
some restrictions in its performance and/or functions.  The examples of
resources are electricity, water and gas.

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


#### ResourceSavingMode

|            |                                                              |
|------------|--------------------------------------------------------------|
| Type       | boolean                                                      |
| Access     | read-write                                                   |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true      |

Indicates the running mode of device from the aspect of resource saving.  It
holds TRUE if the device runs in the resource saving mode, FALSE otherwise.

Errors raised by the set method of this property:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- Indicates
that the given value was not acceptable due to internal state.
* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Indicates that
control from a remote site is currently disabled.  See the RemoteControl 
property in [the definition of common interface](/org.alljoyn.SmartSpaces/Common-v1) for
further information.

### Methods

No methods defined for this interface.

### Interface Errors

The table below shows the possible errors raised by this interface.

| Error name                    | Error message                         |
|-------------------------------|---------------------------------------|
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | Given value was not acceptable due to internal state. |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled | Control from a remote site is currently disabled. |

## References

  * [The XML definition of ResourceSaving](ResourceSaving-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
