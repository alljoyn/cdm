# org.alljoyn.SmartSpaces.Operation.OnOffStatus version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e. a remote application) the
capability to monitor the on/off status of the _producer_ (i.e. the appliance).

Depending on the device type the on/off status can be power on/off status (for
non-cyclic operations devices like fridges, freezers, ...) or the main function
status (for cyclic operations devices like washers, ovens, ...). More detailed
definitions of appliance types are in the
**org.alljoyn.SmartSpaces.Operation.CycleControl** interface.

Depending on the _producer_ implementation, the _consumer_ can interact with its
on/off status with the following three cases.
  * the _consumer_ can monitor the on/off status of a _producer_, but it can not
    control it. As an example, some oven models might not allow remote on/off 
    since their usage requires **attended** operations (put in and out the food)
    and thus, the manufacturers can enable only monitoring on/off status.
  * the _consumer_ can monitor the on/off status of a _producer_ and it can
    control it, switching both on and off. In case AllJoyn connectivity module
    works even if its higher device is powered off, turning the device's power 
    on and off remotely might be enabled.
  * the _consumer_ can monitor the on/off status of a _producer_ and it can
    switch it off but it can not switch it on. Sometimes this is required for
    safety issue or it is impossible to turn on the device remotely since the
    AllJoyn connectivity module share the same power source the whole device.
    In the latter case, the **off** state couldn't be monitored.

This interface provide to the _consumer_ just the capability of monitor the
on/off status. The capability to control it (i.e. to stimulate its change from
remote) is implemented by the interfaces
**org.alljoyn.SmartSpaces.Operation.OffControl** and
**org.alljoyn.SmartSpaces.Operation.OnControl**.

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

The interface version.

#### OnOff

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | boolean                                                 |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the current on/off status of a device.

  * false --- **Off** --- turned off
  * true --- **On** --- turned on

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No error associated to this interface.

## References

  * The XML definition of the [OnOffStatus interface](OnOffStatus-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [CycleControl interface](CycleControl-v1)
  * The definition of the [OffControl interface](OffControl-v1)
  * The definition of the [OnControl interface](OnControl-v1)

