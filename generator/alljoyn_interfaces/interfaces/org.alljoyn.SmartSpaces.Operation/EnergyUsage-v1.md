# org.alljoyn.SmartSpaces.Operation.EnergyUsage version 1

## Theory of Operation

This interface allows a device to communicate its energy consumption. The rate 
and precision of the updates are determined by the device, and governed by the
intended function of the device, its knowledge of significant changes and the
need to avoid side-channel attacks.

In order for the consumer to know what update rate is expected it should read
from the Precision and UpdateMinTime properties to understand the amount of
change required in the measured value before the property will update, and the
maximum time at which updates can be expected. Note that reading
CumulativeEnergy between updates should not return a different value than the
last changed signal, as that would violate the **EmitsChangedSignal = true**
contract. It means that if the physical value changes often, that there's no way
to retrieve the actual current value.

The Precision and UpdateMinTime properties may change based on the state of the
device, either based on user settings, current mode, or the dynamic range of the
power consumption. Also these are Precision properties, not accuracy properties.
Accuracy should not be implied from them.

NOTE: Energy usage can be used to implement side-channel attacks on security
sensitive hardware and software. Manufacturers of devices implementing this
interface should be aware of this possibility. Based on their implementation
specifics, these methods may leak information that may undermine the security of
the AllJoyn protocol. Limiting the resolution of the measurement, or the rate
that the methods may be called may be sufficient protection.

## Specification

|            |                                                          |
|------------|----------------------------------------------------------|
| Version    | 1                                                        |
| Annotation | org.alljoyn.Bus.Secure = true                            |

### Properties

#### Version

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | uint16                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const |

Interface version.

#### CumulativeEnergy

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Holds the cumulative energy consumption of the device in kWh.
ResetCumulativeEnergy resets the value to 0.

#### Precision

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The precision of the CumulativeEnergy property.; i.e., the number of kWh the
actual energy consumption (the physical value which is measured)must change
before CumulativeEnergy property is updated.

#### UpdateMinTime

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | uint16                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The minimum time between updates in milliseconds. Changes in the physical
measured value that occur faster, even if they exceed Precision property value
will not update the CumulativeEnergy property.

### Methods

#### ResetCumulativeEnergy ()

Resets the value of CumulativeEnergy to 0.

Errors raised by this method:
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Indicates that
    control request from a remote site is currently disabled. See the 
    RemoteControl property in the [RemoteControllability interface](RemoteControllability-v1)
    for further information.

### Named Types

No Named Types are required by this interface.

### Interface Errors

The table below shows the possible raised by this inteface.

|                      Error name                     |                       Error message                       |
|-----------------------------------------------------|-----------------------------------------------------------|
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled | Control request from a remote site is currently disabled. |

## References

  * The XML definition of the [EnergyUsage interface](EnergyUsage-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
