#  org.alljoyn.SmartSpaces.Environment.CurrentCo2Concentration version 1

## Specification

|              |                                      |
|--------------|--------------------------------------|
| Version      | 1                                    |
| Annotation   | org.alljoyn.Bus.Secure = true        |

### Properties

#### CurrentValue

|              |                                                          |
|--------------|----------------------------------------------------------|
| Type         | Concentration                                            |
| Access       | read-only                                                |
| Annotation   | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The current value of relative concentration of CO2.
Relative concentration of CO2 is the ratio of CO2 to the monitored mixture of
gases.
The value is expressed in ppm( Parts Per Million ).

### Methods

No methods are exposed by this interface.

### Signals

No signals are exposed by this interface.

###Named Types

#### struct Concentration

Concentration struct express a fixed-point number.
  * **significand**  ---uint16--- significand of CO2 concentration value.
  * **exponent**  ---int16--- exponent of CO2 concentration value.

CO2 concentration representing property(CurrentValue)
is defined using a struct where:
  * first element is the significand.
  * second element is the exponent and base is 10.The actual CO2 concentration
    value can be represented by significand(10^exponent).

## References

  * the XML definition of the [CurrentCo2Concentration interface]
    (CurrentCo2Concentration-v1.xml)

