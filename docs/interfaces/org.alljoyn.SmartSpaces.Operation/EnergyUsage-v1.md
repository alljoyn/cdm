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



#### RepresentedPower

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Holds the instantaneous power consumption of the device in Watts. 
7fff ffff ffff ffff (NaN) indicates an unknown value.

#### UsedEnergy

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Holds the cumlative energy consumption of the device in kWh.  
7fff ffff ffff ffff (NaN) indicates an unknown value.  ResetUsedEnergy resets 
the value to 0.

### Methods

#### ResetUsedEnergy ()

Resets the value of UsedEnergy to 0.

Errors raised by this method:
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Indicates that
    control request from a remote site is currently disabled.  See the
    RemoteControl property in [the definition of common interface](/org.alljoyn.SmartSpaces/Common-v1)
    for further information.

### Named Types

No Named Types are required by this interface.

### Interface Errors

The table below shows the possible raised by this inteface.

| Error name                                    | Error message         |
|-----------------------------------------------|-----------------------|
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled   | Control request from a remote site is currently disabled.       |

## References

  * [The definition of common interface](/org.alljoyn.SmartSpaces/Common-v1)
  * [The XML definition of the EnergyUsage](EnergyUsage-v1.xml)
