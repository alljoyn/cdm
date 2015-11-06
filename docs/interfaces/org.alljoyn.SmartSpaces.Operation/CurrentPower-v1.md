# org.alljoyn.SmartSpaces.Operation.CurrentPower version 1


## Theory of Operation
This interface allows a device to communicate its power consumption.  The rate
and precision of the updates are determined by the device, and governed by the
intended function of the device, its knowledge of significant changes and the
need to avoid side-channel attacks.

In order for the consumer to know what update rate is expected it should read
from the Precision and UpdateRate attributes to understand the amount of change 
required in the measured value before the property will update, and the maximum 
frequency at which updates can be expected.  Note that reading CurrentPower
between updates should not return a different value than the last changed
signal, as that would violate the
org.freedesktop.DBus.Property.EmitsChangedSignal = true contract.

The Precision and UpdateRate properties may change based on the state of the
device, either based on user settings, current mode, or the dynamic range of the
power consumption.  Also these are Precision properties, not accuracy
properties.  Accuracy should not be implied from them.

NOTE: “Energy usage can be used to implement side-channel attacks on security
sensitive hardware and software.  Manufacturers of devices implementing this
interface should be aware of this possibility.  Based on their implementation
specifics, these methods may leak information that may undermine the security of
the AllJoyn protocol.  Limiting the resolution of the measurement, or the rate
that the methods may be called may be sufficient protection.”

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

#### Precision

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The precision of the CurrentPower property.  i.e. the number of watts the
actual power consumption (the physical value which is measured) must change
before the CurrentPower property is updated.

#### UpdateMinTime

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | uint16                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The minimum time between updates in milliseconds.  Changes in the physical
measured value that occur faster, even if they exceed Precision property value
will not update the CurrentPower property.


### Methods

No Methods are implemented by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors

No Errors are implemente by this interface.

## References

  * The XML definition of the [CurrentPower interface](CurrentPower-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
