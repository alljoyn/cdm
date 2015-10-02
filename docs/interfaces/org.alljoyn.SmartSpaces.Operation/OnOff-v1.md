# org.alljoyn.SmartSpaces.Operation.OnOff version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e. a remote application) the
capability to monitor and control the on/off status of the _producer_ (i.e. the
appliance).
Depending on the device type the on/off status can be power on/off status (for
non-cyclic operations devices like fridges, freezers, ...) or the main function
status (for cyclic operations devices like washers, ovens, ...). More detailed
definitions of appliance types are in the
**org.alljoyn.SmartSpaces.Operation.CycleControl** interface.

Depending on the _producer_ implementation, the _consumer_ can interact with its
on/off status with the following three cases.
  * the _consumer_ can monitor the on/off status of _producer_, but it can not
    control it. As an example, some oven models might not allow remote on/off 
    since their usage requires **attended** operations (put in and out the food)
    and thus, the manufacturers can enable only monitoring on/off status.
  * the _consumer_ can monitor the on/off status of _producer_ and it can
    control it, switching both on and off. In case AllJoyn connectivity module
    works even if its higher device is powered off, turning the device's power 
    on and off remotely might be enabled.
  * the _consumer_ can monitor the on/off status of _producer_ and it can switch
    it off but it can not switch it on. Sometimes this is required for safety
    issue or it is impossible to turn the device on remote since the AllJoyn
    connectivity module share the same power source with its higer device.
    In the latter case, the **off** state couldn't be monitored.
This interface provide the capability to the _consumer_ to know in advance which
are the allowed operations without the need to attempt them and check errors.


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
| Access     | read-write                                              |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the current on/off status of a device.

  * false --- **Off** --- turned off
  * true --- **On** --- turned on

Errors raised when setting this property:

  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command value is not accepted by the _producer_, because it is in a state
    which doesn't allow the resulting transition
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### SwitchOnIsSupported

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | boolean                                                  |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

It indicates whether on/off status can be switched on or not.

  * false --- the on/off status **can not** be switched on remotely
  * true --- the on/off status **can** be switched on remotely

#### SwitchOffIsSupported

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | boolean                                                  |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

It indicates whether on/off status can be switched off or not.

  * false --- the on/off status **can not** be switched off remotely
  * true --- the on/off status **can** be switched off remotely

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |

## References

  * The XML definition of the [OnOff interfce](OnOff-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
  * The definition of the [Cycle Control interface](CycleControl-v1)
