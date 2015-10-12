# org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay version 1

## Theory of Operation

See [Namespace Theory of Operation](theory-of-operation)

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
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

The EmitsChangedSignal of this property should be updated to "const" once that 
feature is available in Core.

#### DisplayTimeFormat

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                  |
| Access                | read-write                                                            |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

0 = "12 hour" format
1 = "24 hour" format

Time format used on the device display.  SupportedDisplayTimeFormats should be
read prior to writing to this property.

Errors raised by writing to this attribute:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState 
--- Value is not acceptable due to internal state.  Caller should try again at a 
later time.  This potentially could be raised if local user was interacting with 
the UI.

* org.alljoyn.InvalidValue --- Value is not supported.  
Caller should read SupportedDisplyTemperatureUnits for acceptable values.

* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- 
Remote control is disabled.  See the [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

#### SupportedDisplayTimeFormats

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte[]                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

List of allowable settings.  If only one item in list then the 
SetDisplayTimeFormat method may not be changed. The EmitsChangedSignal of this 
property should be updated to "const" once that feature is available in Core.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors


The attribute writes in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error 
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                 |
|---------------------------------------------------------------|-----------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Value not supported                           |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | Value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control is disabled |



## References

* [Namespace Theory of Operation](theory-of-operation)

* The XML definition of the [TimeDisplay interface](TimeDisplay-v1.xml)

* The [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

* The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
