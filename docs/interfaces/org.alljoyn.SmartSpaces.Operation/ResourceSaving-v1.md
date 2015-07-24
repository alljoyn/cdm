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

#### ResourceSavingMode

|            |                                                              |
|------------|--------------------------------------------------------------|
| Type       | boolean                                                      |
| Access     | read-only                                                    |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true      |

Indicates the running mode of device from the aspect of resource saving.  It
holds TRUE if the device runs in the resource saving mode, FALSE otherwise.

### Methods

#### EnableResourceSaving (resourceSavingMode)

Enables or disables the resource saving mode.

Input arguments:

  * **resourceSavingMode** --- boolean --- Set TRUE to enable or FALSE to
    disable.

Errors raised by this method:

  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- Indicates
    that the given value was not acceptable due to internal state.
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Indicates that
    control
    from a remote site is currently disabled.  See the RemoteControl property
    in [the definition of common interface](/org.alljoyn.SmartSpaces/Common-v1) for
    further information.

### Interface Errors

The table below shows the possible errors raised by this interface.

| Error name                    | Error message                         |
|-------------------------------|---------------------------------------|
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | Given value was not acceptable due to internal state. |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled | Control from a remote site is currently disabled. |

## References

  * [The definition of common interface](/org.alljoyn.SmartSpaces/Common-v1)
  * [The XML definition of ResourceSaving](ResourceSaving-v1.xml)
