# org.alljoyn.SmartSpaces.Operation.LockControl version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e., a remote application) the
capability to engage the locking mechanism on the _producer_ (i.e., the appliance).

This interface depends on the **org.alljoyn.SmartSpaces.Operation.LockedStatus** interface
in the sense that: any device that implements **org.alljoyn.SmartSpaces.Operation.LockControl** 
has to implement the **org.alljoyn.SmartSpaces.Operation.LockedStatus** interface.

This interface can also be composed with the **org.alljoyn.SmartSpaces.Operation.RemoteControllability**
interface. **RemoteControllability** provides the capability to enable or disable
the **LockControl** interface.


## Specification

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Version               | 1                                                                     |
| Annotation            | org.alljoyn.Bus.Secure = true                                         |


### Properties

#### Version

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | uint16                                                                |
| Access                | read                                                                  |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = const              |

The interface version


### Methods

#### Lock()

Engage the locking mechanism on the _producer_.

Errors raised by this method:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
  command value is not accepted by the _producer_, because it is in a state
  which doesn't allow the resulting transition
* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
  control is disabled


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

  * The [LockControl interface](LockControl-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v2)
  * The description of the [RemoteControllability interface](RemoteControllability-v1)
  * The description of the [LockedStatus interface](LockedStatus-v1)
