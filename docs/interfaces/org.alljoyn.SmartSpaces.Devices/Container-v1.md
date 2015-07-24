# org.alljoyn.SmartSpaces.Devices.Container version 1

## Theory of Operation

Container interface is for comprising of two or more devices as same level under
the root bus object. Container interface can be a container having two or more
other device interfaces. For example, complex refrigerator consists of
refrigerator, freezer and ice maker can be represented as a container device
which has Refrigerator, Freezer and IceMaker device interfaces.
Use of the container device interface for just one sub-unit shall be prohibited.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

No properties are implemented by this interface.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [Container interface](Container-v1.xml)
