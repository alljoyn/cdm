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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

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

The current relative level of water in the tank.
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

#### GetWaterLevelInfo (languageTag) -> (waterLevelInfo)

Get added info about the water levels in string format. It is 
used to communicate to controller the strings associated to the water 
level supported values so it can display them.

Input arguments:

  * **languageTag** --- string --- languageTag to be used in the output 
    strings using IETF language tags specified by RFC 5646.

Output arguments:

  * **waterLevelInfo** --- string[] --- the list of strings
    associated to the water levels, each element of the array refers
    to the level expressed by its index; the array can be:
    * empty: there are no strings to communicate
    * list a string for each element from 0 to **MaxLevel** 
      examples of output are: "Empty", "Low", "Mid", "High", "Full"

Errors raised by this method:

  * org.alljoyn.Error.LanguageNotSupported --- the language specified is not supported

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

|                          Error name                          |                     Error                     |
| ------------------------------------------------------------ | --------------------------------------------- |
| org.alljoyn.Error.LanguageNotSupported                       | The language specified is not supported       |

## References

  * The XML definition of the [WaterLevel interface](WaterLevel-v1.xml)
