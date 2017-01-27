# org.alljoyn.SmartSpaces.Operation.RemoteControllability version 1

## Theory of Operation
This interface provides a capability to monitor a remote control
enabled/disabled status. Some home appliances provide an option to enable and
disable locally the remote controllability for the various reasons.
The followings are examples use cases.

* An end-user selects and starts the cooking process of an oven, then disables
  the remote control to prevent from other users from modifying its programmed
  operation.
* A mother sets a target temperature of Kimchi refrigerator and presses the
  kids lock button on the local control panel to prevent her little kids from
  changing the settings. Kimchi is a typical fermented Korean food.
* A family goes on vacation. They fear that their home devices might be remote
  controlled maliciously by somebody. So they disable the remote control
  operation of their home devices before their leaving.
* In the United States, UL requires that the consumer explicitly permit remote
  operation of the oven each time it is used. The permission expires whenever
  power is lost or the oven door is open. The **IsControllable** property
  can be used to track this permission.

This temporal disabling/enabling of remote control should be done locally
in front of the device and thus, it is not allowed to change remotely.

Remote monitoring should be always possible regardless of device's remote
control enabled/disabled status. The remote monitoring includes getting
properties and receiving signals. If a method call is about retrieving
information from the _producer_, then it should be allowed.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### Version

|                   |                                                         |
|-------------------|---------------------------------------------------------|
| Type              | uint16                                                  |
| Access            | read-only                                               |
| Annotation        | org.freedesktop.DBus.Property.EmitsChangedSignal = const|

The interface version.

#### IsControllable

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | boolean                                                        |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Status of remote controllability. The meaning of "Remote" covers both proximal
network and remote access from outside home. In other words, "Remote" means
everything outside of AllJoyn devices regardless of physical distance.
If **IsControllable** is true, the device is controllable by remote devices.
This value affects all interfaces of the bus object it belongs to and even its
children objects, if any.

Typically, this capability is expected to be used for an entire device (not for
sub-units) and it is recommended to implement this interface right under the
CDM root bus object.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

## References

  * The XML definition of the [RemoteControllability interface](RemoteControllability-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
