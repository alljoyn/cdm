# org.alljoyn.SmartSpaces.Environment.CurrentTemperature version 1

## Theory of Operation
This interface provides capability to represent current temperature.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### CurrentValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | Temperature                                                    |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The represented value of current temperature, expressed in Celsius.
See fixed-point representation for more information in Temperature struct
definition.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct Temperature

Temperature struct express a fixed-point number.

  * **significand** --- int16 --- significand of temperature value
  * **exponent** --- int16 --- exponent of temperature value

Temperatures representing properties (e.g. TargetValue, MinValue and MaxValue)
are defined using a struct where:
  * first element is the significand;
  * second element is the exponent and base is 10.The actual temperature value
  can be represented by significand (10^exponent)
  * Refer to http://en.wikipedia.org/wiki/Significand

> Example:
> the value 10.2 can be represented as 102 in a fixed-point data type with
> scaling factor of 1/10, which is given by the exponent equal to -1 and
> base is 10.
> (102, -1) = 102 \* 10^(-1) = 10.2, (32442, -3) = 32442 \* 10^(-3) = 32.442
> If the device does not limit minimum temperature, the MinValue is represented
> as (0x8000, 0x7FFF).If the device does not limit maximum temperature, the
> MaxValue is represented as (0x7FFF, 0x7FFF).

**Note**: this representation gives some flexibility to manage different levels
of approximation; e.g. "10.0°C" can be represented as (1, 1), (10, 0), (100, -1)...
It is strongly suggested to use the minimum approximation which fits with the
application requirements; e.g. if the device manage temperatures with a "0.1°C"
accuracy, the exponent has to be set to "-1" (it can not be higher for
information loss, but it has no sense to set it lower because it adds complexity
in the calculation without having any advantage).It is also suggested to keep
fixed exponent in any specific application and not change at run-time.

## References

  * The XML definition of the [CurrentTemperature interface](CurrentTemperature-v1.xml)
