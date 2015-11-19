# org.alljoyn.SmartSpaces.Environment.CurrentAirQuality version 1

## Specification
|                   |                                   |
|-------------------|-----------------------------------|
| Version           | 1                                 |
| Annotation        | org.alljoyn.Bus.Secure = true     |

### Properties

#### Version

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | uint16                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Interface version.

#### AirQualityType

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | byte                                                    |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The type of air quality.

* **0** -- **CH2O (ug/m3)**
* **1** -- **CO2 (ppm)**
* **2** -- **CO (ppm)**
* **3** -- **PM2.5 (ug/m3)**
* **4** -- **PM10 (ug/m3)**
* **5** -- **VOC (ug/m3)**

#### CurrentValue

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | double                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The current air quality in the unit indicated by AirQualityType.

#### MaxValue

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | double                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The maximum value allowed for CurrentValue.
If there is no maximum value available, the MaxValue shall
be set to 0x7FF0 0000 0000 0000.

#### MinValue

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | double                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The minimum value allowed for CurrentValue.
If there is no minimum value available, the MinValue shall
be set to 0x0.

#### Precision

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | double                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The precision of the CurrentValue property. i.e. the number of ug/m3 or ppm the
actual current temperature (the physical value which is measured)must change
before the CurrentValue property is updated.

#### UpdateMinTime

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | uint16                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The minimum time between updates in milliseconds.  Changes in the physical
measured value that occur faster, even if they exceed Precision property value
will not update the CurrentValue property.

### Methods

No methods are exposed by this interface.

### Signals

No signals are exposed by this interface.

## References

  * the XML definition of the [CurrentAirQuality interface](CurrentAirQuality-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)

