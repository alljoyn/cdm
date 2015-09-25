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
on/off status with different access credentials; following three cases are
contemplated:
  * the _consumer_ can monitor the on/off status of _producer_, but it can not
    control it
  * the _consumer_ can monitor the on/off status of _producer_ and it can
    control it, switching both on and   off
  * the _consumer_ can monitor the on/off status of _producer_ and it can switch
    it off but it can not switch it on (sometime this is required for safety
    issue)
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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It indicates whether on/off status can be switched on or not.

  * false --- the on/off status **can not** be switched on remotely
  * true --- the on/off status **can** be switched on remotely

#### SwitchOffIsSupported

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | boolean                                                  |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

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
  * The definition of the [Cycle Control interface](/org.alljoyn.SmartSpaces.Operation/CycleControl-v1)