# org.alljoyn.SmartSpaces.Common version 1

## Theory of Operation
This interface is a common AllJoyn interface for all HAE devices. Per About
announcement, there shall be one and only one common interface for HAE service
framework and the bus object where the common interface reside is the root HAE
bus object.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### CountryOfProduction

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Country of production

#### Location

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Location information of a device. There is no constraint about location
information. For example, classification of rooms ("Dining room",
"Bedroom", "Restroom", etc.) or coordinate of GPS data can be a value
of location information.

#### CorporateBrand

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Corporate level brand name. For example, AEG for Electrolux and Sanyo for
Panasonic, etc.

#### ProductBrand

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Product level brand name. Walkman and Bravia for Sony, Viera for Panasonic.

#### RemoteControl

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | boolean                                                        |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The meaning of "Remote" covers both proximal network and remote access from
outside home. In other words, "Remote" means everything outside of AllJoyn
devices regardless of physical distance. If RemoteControl is true, the device is
controllable by remote devices. This value affects all interfaces of the device.
If RemoteControl is false, the device cannot be controlled by any device
interfaces or shared interfaces.

### Methods

#### SetLocation (location)

Set location information of a device.

Input arguments:

  * **location** --- string --- location information of a device to set

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [Common interface](Common-v1.xml)
