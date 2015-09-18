# org.alljoyn.SmartSpaces.Operation.HeatingZone version 1

## Theory of Operation

This interface provides information about the status of heating zones of a
Cook-Top. It is designed in order to describe the case of Cook-Top which zones
can be activated dynamically (e.g. the device implement pot recognition).
Anyway the interface covers also the typical case of the Cook-Top consisting
of multiple fixed heating zones and/or dynamically activated heating zones.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### NumberOfHeatingZones

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the total number of heating zones of the Cook-Top.
The zones can be activated dynamically if the CookTop implement pot recognition.

### MaxHeatingLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the max levels for each heating zone.
The array size should be equal to **NumberOfHeatingZones**.

### HeatingLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the list of current heating levels of the different zones of the
Cook-Top.
For each element the value range is from 0 (indication that the zone is not
heating) to the value of related element of **MaxHeatingLevels**.
The array size should be equal to **NumberOfHeatingZones**.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors

No unique errors are associated with this interface.

## References

  * The XML definition of the [HeatingZone interface](HeatingZone-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)

