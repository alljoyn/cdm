# org.alljoyn.SmartSpaces.Operation.OffControl version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e. a remote application) the
capability to control the on/off status of the _producer_ (i.e. the appliance)
in the case of **switching off** operation.

This interface depends on the **org.alljoyn.SmartSpaces.Operation.OnOffStatus** in the
sense that: any device that implements
**org.alljoyn.SmartSpaces.Operation.OffControl** has to implement also
**org.alljoyn.SmartSpaces.Operation.OnOffStatus**.

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

### Methods

#### SwitchOff()

Switch the _producer_ off.

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

  * The XML definition of the [OffControl interface](OffControl-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
  * The definition of the [OnOffStatus interface](OnOffStatus-v1)
