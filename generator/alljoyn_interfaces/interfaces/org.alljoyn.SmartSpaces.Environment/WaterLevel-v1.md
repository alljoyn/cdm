# org.alljoyn.SmartSpaces.Environment.WaterLevel version 1

## Theory of Operation

This information provides level and supply source of water for an appliance.
Examples of appliances which may include this interface are air purifier, 
humidifier, and ice maker.

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

The interface version number.

#### SupplySource

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The supply source of water.

* **0** --- **Tank** --- water supplied via a tank
* **1** --- **Pipe** --- water supplied via a pipe
* **255** --- **Not Supported** --- no supply source information available

#### CurrentLevel

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current level of water in the tank.
If **SupplySource** = **Pipe** or **Not Supported**, then **Level** shall be always 
**0**, which means there is practically no information available about the 
current water level.

0 ~ MaxLevel:

* **0** --- **the smallest detectable quantity of water (possibly empty) **
* **MaxLevel** --- **the largest detectable quantity of water (possibly full) **

For example, a device that detects only whether there exists water or not 
would have MaxLevel = 1, and represented levels {0, 1}.
If there are 6 levels of detectability then MaxLevel = 5, and
the levels will be {0, 1, 2, 3, 4, 5}.

#### MaxLevel

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum level allowed for water level.
MaxLevel shall not change except when SupplySource is changed.
If **SupplySource** = **Pipe** or **Not Supported**, then **MaxLevel** shall be **0**.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [WaterLevel interface](WaterLevel-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
