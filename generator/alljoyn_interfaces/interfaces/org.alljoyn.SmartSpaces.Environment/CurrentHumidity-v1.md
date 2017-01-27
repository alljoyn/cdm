# org.alljoyn.SmartSpaces.Environment.CurrentHumidity version 1

## Theory of Operation
This interface provides capability to represent current
relative humidity.

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
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current value of relative humidity. Relative humidity is the ratio of 
the partial pressure of water vapor to the equilibrium vapor pressure of 
water at the same temperature. If **MaxValue** is equal to 100, it represents
the current humidity value as a quantitative percentage (0~100%). Otherwise, it
represents the current humidity value as a qualitative level (0~MaxValue).
0 represents the lowest level of humidity, and MaxValue represents the highest 
level of humidity.


#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value allowed for represented relative humidity. This value can't be 
above 100. If the current relative humidity is represented by a quantitative
percentage ratio, then this value shall be set to 100.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [CurrentHumidity interface](CurrentHumidity-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
