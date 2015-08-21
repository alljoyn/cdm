# org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel version 1

## Theory of Operation

This information provides represented air quality level measured by an 
appliance.
Examples of appliances which may include this interface are air purifier and 
air quality monitor.

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

#### AirQualityType

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

The air quality type.

* **0** --- **PM2.5**
* **1** --- **PM10**
* **2** --- **CO**
* **3** --- **CO2**
* **4** --- **CH2O**
* **5** --- **VOC**
* **6** --- **Smoke**
* **7** --- **Odor**
* **8** --- **AirPollution**

#### CurrentLevel

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The qualitative representation of current relative air quality level.

0 ~ MaxLevel:

* **0** --- **the cleanest level**
* **MaxLevel** --- **the most impure level**

For example, a device that only has 2 states clean and dirty would have 
MaxLevel = 1, and represented levels {0, 1}.
If there were 6 levels of detectability then MaxLevel = 5, and
represented levels would be {0(cleanest), 1, 2, 3, 4, 5(dirtiest)}.

#### MaxLevel

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Maximum level allowed for represented air quality level.

### Methods

#### GetAirQualityLevelInfo (languageTag) -> (airQualityLevelInfo)

Get added info about the air quality levels in string format. It is used to 
communicate to controller the strings associated to the air quality level 
supported values so it can display them.

Input arguments:

  * **languageTag** --- string --- languageTag to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **airQualityLevelInfo** --- string[] --- the list of strings
    associated to the air quality levels, each element of the array refers
    to the level expressed by its index; the array can be:
    * empty: there are no strings to communicate
    * list a string for each element from 0 to **MaxLevel** 
    examples of output are: "Clean", "Mid", "Very Impure"

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

  * The XML definition of the [CurrentAirQualityLevel interface](CurrentAirQualityLevel-v1.xml)
