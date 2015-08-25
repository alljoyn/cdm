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

interface version.

#### AirQualityType

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | byte                                                    |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

the type of air quality.
0 : CH2O (ug/m3)
1 : CO2 (ppm)
2 : CO (ppm)
3 : PM2.5 (ug/m3)
4 : PM10 (ug/m3)
5 : VOC (ug/m3)

#### CurrentValue

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | double                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The current value of concentration of air quality.

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

### Methods

No methods are exposed by this interface.

### Signals

No signals are exposed by this interface.

## References

  * the XML definition of the [CurrentAirQuality interface]
    (CurrentAirQuality-v1.xml)

