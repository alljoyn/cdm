# org.alljoyn.SmartSpaces.Operation.PlugInUnits version 1

## Theory of Operation

This interface is designed to be used in combo devices which have some sub-units
that can be plugged in and out or disabled/enabled on the fly.
When a sub-unit is not plugged in the related bus object, it shouldn't be used
by the _consumer_ because the related interfaces are not working, so the
_consumer_ itself has to be aware of it.
This interface gives information about which are the sub-units that can be hot
plugged in and out and which are the related status of them.

In principle this feature could be managed without implementing this interface,
but by just updating the bus objects structure: i.e. creating a new bus object
when a sub-unit is plugged in and deleting when it is plugged out. Anyway the
implementation of this interface lets the _consumer_ get in real time the
sub-unit status by emitting related properties change signals.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### Version

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | uint16                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Interface version.
The EmitsChangedSignal of this property should be modified to const once that
feature is available.

#### PlugInUnits

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | PlugInInfo[]                                            |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The lists of all the possible hot pluggable devices and their associated status
which indicates which are plugged in and which are not.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Named Types

#### struct PlugInInfo

The **PlugInInfo** is used to describe the characteristics and the status
of a plug-in unit. Its elements are:

  * **objectPath** --- object_path --- object path of the unit
  * **deviceId** --- uint32 --- device type id of the unit as defined in the HAE
    service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * **status** --- boolean --- current status of the unit
    * **false** --- not active, not present or not inserted
    * **true** --- active, present or inserted

### Interface Errors

No unique errors are associated with this interface.

## Examples

A typical example of usage of this interface is an oven device with a plug in
meat probe.
The bus objects of the units are:
  * /appliance  --- for the root
  * /appliance/oven --- for the oven cavity
  * /appliance/oven/probe -- for the meat probe

The **PlugInUnits** interfaces should be implemented in the **/appliance/oven**
object path and with an element in its list which describes the meat probe as a
**FoodProbe** device.

## References

  * The XML definition of the [PlugInUnits interface](PlugInUnits-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)

