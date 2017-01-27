# org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel version 1

## Theory of Operation

This information provides represented air quality level measured by a 
device.
Examples of devices which may include this interface are air purifier and 
air quality monitor.
If the sensor is capable of detecting CHO2/CO2/CO/PM2.5/PM/VOC in ppm or 
ug/m3, it is recommended to use the CurrentAirQuality interface rather 
than CurrentAirQualityLevel.

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

#### ContaminantType

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The measured contaminant type.

* **0** --- **CH2O**
* **1** --- **CO2**
* **2** --- **CO**
* **3** --- **PM2.5**
* **4** --- **PM10**
* **5** --- **VOC**
* **253** --- **Smoke**
* **254** --- **Odor**
* **255** --- **AirPollution**

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
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
