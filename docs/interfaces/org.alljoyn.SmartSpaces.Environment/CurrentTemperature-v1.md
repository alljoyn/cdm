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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The interface version.

#### CurrentValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | double                                                    |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current temperature in degrees Celsius.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [CurrentTemperature interface](CurrentTemperature-v1.xml)
