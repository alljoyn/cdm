# org.alljoyn.SmartSpaces.Environment.CurrentTemperature version 1

## Theory of Operation
This interface provides capability to represent current temperature.

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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const       |

The interface version.

#### CurrentValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |
| Annotation | org.alljoyn.Bus.Type.Units = degrees Celsius                   |

The current temperature in degrees Celsius.

#### Precision

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |
| Annotation | org.alljoyn.Bus.Type.Units = degrees Celsius                   |

The precision of the CurrentValue property. I.e., the number of degrees Celsius the
actual current temperature (the physical value which is measured) must change
before the CurrentValue property is updated.

#### UpdateMinTime

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | uint16                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |
| Annotation | org.alljoyn.Bus.Type.Units = milliseconds                |

The minimum time between updates in milliseconds.  Changes in the physical
measured value that occur faster, even if they exceed Precision property value
will not update the CurrentValue property.


### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [CurrentTemperature interface](CurrentTemperature-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
