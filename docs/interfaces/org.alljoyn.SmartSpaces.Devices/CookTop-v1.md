# org.alljoyn.SmartSpaces.Devices.CookTop version 1

## Theory of Operation

The CookTop is a home appliance with a flat framework used to place pots to be
heated, so the food inside is cooked.
This interface provides capabilities to interact with specific functions and
resources of CookTops. It is applicable to different types of CookTops:
Gas based, Electrical, Induction ...

There are no minimum required shared interfaces for these appliances.

Following interfaces can be supported when a specific CookTop implements extra
features:

  * **org.alljoyn.SmartSpaces.Operation.Control** --- for monitoring and
  controlling the appliance operation time
  * **org.alljoyn.SmartSpaces.Operation.Timer** --- for monitoring and
    controlling the appliance operation time
  * **org.alljoyn.SmartSpaces.Operation.Alerts** --- for communicating alerts
  * **org.alljoyn.SmartSpaces.RepresentedTemperature** --- for monitoring the
    temperature

This interface can be used:
  * stand alone, to describe one or more heating zones that can be controlled
    (if **org.alljoyn.SmartSpaces.Operation.Control** is supported) together.
  * as sub-unit of a complex device; e.g. a CookTop with different heating zones
    which can be controlled separately.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

### NumberOfHeatingZones

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It indicates the total number of heating zones of the CookTop.
The zones can be activated dynamically if the CookTop implement pot recognition.
The value is 1 for CookTop with just a fixed zone.

### MaxHeatingLevels

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte[]                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It indicates the max levels for each the heating zone.

### HeatingLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the list of current heating levels of the different zones of the
CookTop.
For each element the value range is from 0 (indication that the zone is not
heating) to the value of related element of **MaxHeatingLevels**.

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No error associated to this interface.

## Examples

No example associated to this interface.

## References

  * The XML definition of the [CookTop interface](CookTop-v1.xml)
  * The definition of the [Alerts interface](/org.alljoyn.SmartSpaces.Operation/Alerts-v1)
  * The definition of the [Control interface](org.alljoyn.SmartSpaces/Operation/Control-v1)
  * The definition of the [Timer interface](org.alljoyn.SmartSpaces.Operation/Timer-v1)
