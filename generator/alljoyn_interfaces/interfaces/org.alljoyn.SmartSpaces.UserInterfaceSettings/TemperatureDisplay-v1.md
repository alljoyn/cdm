# org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay version 1

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
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = const              |

#### DisplayTemperatureUnit

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                  |
| Access                | read-write                                                            |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

0 = Celsius
1 = Fahrenheit
2 = Kelvin

Unit for Temperatures displayed on the device UI.  
SupportedDisplayTemperatureUnitSettings should be read prior to writing.

Errors raised by writing to this attribute:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState 
--- Value is not acceptable due to internal state.  Caller should try again at a 
later time.  This potentially could be raised if local user was interacting with 
the UI.

* org.alljoyn.Error.InvalidValue --- Value is not supported.  
Caller should read SupportedDisplayTemperatureUnits for acceptable values.

* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- 
Remote control is disabled.  See the [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

#### SupportedDisplayTemperatureUnits

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte[]                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = const              |

List of allowable settings.  If only one item then the Display Temperature Unit
cannot be changed.

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
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control is disabled                    |


## References

* [Namespace Theory of Operation](theory-of-operation)

* The XML definition of the [TemperatureDisplay interface](TemperatureDisplay-v1.xml)

* The [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

* The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)

