# org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay version 1

## Theory of Operation

See [Namespace Theory of Operation](theory-of-operation)  
This interface specifically controls the user interface of the device.  The 
Configuration Base Service language settings controls the Alljoyn bus default
language, and may also affect the device User Interface.  This allows a device 
to support one language on the Alljoyn interface and a different one on the 
actual device display.

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

#### DisplayLanguage

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | string                                                                |
| Access                | read-write                                                            |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

Currently displayed language on the user interface using IETF language tags as
specified by RFC 5646.  SupportedDisplayLanguages should be read prior to 
writing.

Errors raised writing this attribute:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState 
--- Value is not acceptable due to internal state.  Caller should try again at a 
later time.  This potentially could be raised if local user was interacting with 
the UI.

* org.alljoyn.Error.LanguageNotSupported --- Value is not supported.  Caller 
should read SupportedDisplayLanguages for acceptable values.

* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- remote control is 
disabled.   See the [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)


#### SupportedDisplayLanguages

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | string[]                                                              |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

List of allowable settings.  If only one item then the Display Language
cannot be changed.  The EmitsChangedSignal of this property should be updated to 
"const" once that feature is available in Core.


### Methods

No Methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors

The attribute writes in this interface use the AllJoyn error message handling 
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error 
message. The table below lists the possible errors raised by this interface.

| Error name                                                                  | Error message                                 |
|-----------------------------------------------------------------------------|-----------------------------------------------|
| org.alljoyn.Error.LanguageNotSupported                    | The language specified is not supported                           |
| org.alljoyn.SpartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled |


## References

* [Namespace Theory of Operation](theory-of-operation)

* The XML definition of the [LanguangeDisplay interface](LanguageDisplay-v1.xml)

* The [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

* The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
