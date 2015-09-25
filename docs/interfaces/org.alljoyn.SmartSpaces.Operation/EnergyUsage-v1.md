# org.alljoyn.SmartSpaces.Operation.EnergyUsage version 1

## Specification

|            |                                                          |
|------------|----------------------------------------------------------|
| Version    | 1                                                        |
| Annotation | org.alljoyn.Bus.Secure = true                            |

### Properties

#### Version

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | uint16                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

#### CurrentPower

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Holds the instantaneous power consumption of the device in Watts.
7fff ffff ffff ffff (NaN) indicates an unknown value.

#### CumulativeEnergy

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Holds the cumulative energy consumption of the device in kWh.
7fff ffff ffff ffff (NaN) indicates an unknown value.  ResetUsedEnergy resets
the value to 0.

### Methods

#### ResetEnergy ()

Resets the value of CumulativeEnergy to 0.

Errors raised by this method:
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Indicates that
    control request from a remote site is currently disabled.  See the
    RemoteControl property in the [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1) for
further information.


### Named Types

No Named Types are required by this interface.

### Interface Errors

The table below shows the possible raised by this inteface.

| Error name                                    | Error message         |
|-----------------------------------------------|-----------------------|
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled   | Control request from a remote site is currently disabled.       |

## References

  * [The XML definition of the EnergyUsage](EnergyUsage-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * [The definition of RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)
