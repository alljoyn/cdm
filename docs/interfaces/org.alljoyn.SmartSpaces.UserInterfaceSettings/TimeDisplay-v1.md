# org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay version 1

## Theory of Operation

See [Namespace Theory of Operation](UserInterfaceSettingsTheoryOfOperation)

## Specification

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Version               | 1                                                                     |
| Annotation            | org.alljoyn.Bus.Secure = true                                         |

### Properties

#### DisplayTimeFormat

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                  |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

0 = "12 hour" format
1 = "24 hour" format

#### SupportedDisplayTimeFormatSettings

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte[]                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = false              |

List of allowable settings.  If only one item in list then the 
SetDisplayTimeFormat method may not be changed.

### Methods

#### SetDisplayTimeFormat(displayTimeFormat)

User by remote device to attempt to set the displayed time format on the 
device.  SupportedDisplayTimeFormatSettings should be read first.

Input arguments:

* **displayTimeFormat** --- byte --- Desired format for displaying time in the 
device UI.


Errors raised by this method:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState 
--- Value is not acceptable due to internal state.  Caller should try again at a 
later time.  This potentially could be raised if local user was interacting with 
the UI.

* org.alljoyn.InvalidValue --- Value is not supported.  
Caller should read SupportedDisplyTemperatureUnitSettings for acceptable values.

* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- 
Remote control is disabled.  See the SmartSpaces [Common Interface.](../org.alljoyn.SmartSpaces/Common-v1)

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors


The method calls in this interface use the AllJoyn error message handling feature
(`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error message. The table
below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                 |
|---------------------------------------------------------------|-----------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Value not supported                           |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | Value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control is disabled |



## References

* [Namespace Theory of Operation](UserInterfaceSettingsTheoryOfOperation)

* The XML definition of the [TimeDisplay interface](TimeDisplay-v1.xml)

* The SmartSpaces [Common Interface.](../org.alljoyn.SmartSpaces/Common-v1)
