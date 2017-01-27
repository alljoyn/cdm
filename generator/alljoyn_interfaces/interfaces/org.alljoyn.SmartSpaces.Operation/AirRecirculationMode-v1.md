# org.alljoyn.SmartSpaces.Operation.AirRecirculationMode version 1

## Theory of Operation

The interface is used to control if air is recirculating or being refreshed in a 
ventilation product.  The recirc/refresh could be on inlet, like a window air-
conditioner, or on exhaust like a cooking hood.


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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const|

The interface version.  

### IsRecirculating

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | boolean                                                  |
| Access     | read-write                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Indicates if the air flow inlet/extraction is in a recirculating mode(true) or 
is drawing/exhausting to outside(false).

Errors raised by setting this property:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- Returned
if value is not acceptable due to internal state.  example: Device must be
stopped to make change and is currently running.
* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- Returned if 
remote control is disabled. See the RemoteControllability property in the 
[RemoteControllability interface](RemoteControllability-v1) for further information.


### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling feature
(`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error message.
The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control is disabled                         |

## Examples

No example associated to this interface.

## References

* The XML definition of the [AirRecirculationMode interface](AirRecirculationMode-v1.xml)
* The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
* The [RemoteControllability interface](RemoteControllability-v1)


