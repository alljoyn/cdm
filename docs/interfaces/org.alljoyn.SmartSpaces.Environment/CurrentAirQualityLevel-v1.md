# org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel version 1

## Theory of Operation

This information provides represented air quality level measured by a 
device.
Examples of devices which may include this interface are air purifier and 
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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The measured air quality type.

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

The qualitative representation of current air quality level.

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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum level allowed for represented air quality level.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [CurrentAirQualityLevel interface](CurrentAirQualityLevel-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
