# org.alljoyn.SmartSpaces.Operation.BatteryPercentage version 1

## Theory of Operation

This interface provides capability to represent quantitative remaining
battery percentage.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### PercentageValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current remaining battery pecentage. The maximum value allowed for the
PercentageValue is 100.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [BatteryPercentage interface](BatteryPercentage-v1.xml)
