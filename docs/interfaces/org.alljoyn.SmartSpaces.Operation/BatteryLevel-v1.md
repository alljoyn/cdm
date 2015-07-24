# org.alljoyn.SmartSpaces.Operation.BatteryLevel version 1

## Theory of Operation

This interface provides capability to represent qualitative remaining
battery level. Remaining battery can be displayed by qualitative level like
"Low, Med, High".

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### BatteryLevel

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current remaining battery level.
The scope of value is 0 to MaxBatteryLevel.

#### MaxBatteryLevel

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Maximum value allowed for represented battery level.

### Methods

#### GetBatteryLevelsInfo (languageTag) -> (info)

Get additional information about the battery levels in string format.
The information strings associated with the battery level can be displayed
on the controller side.

Input arguments:

  * **languageTag** --- string --- languageTag to be used in the output strings
  using IETF language tags specified by RFC 5646.

Output arguments:

  * **batteryLevelsInfo** --- string[] --- the list of strings
  associated with the battery levels, each element of the array refers
  to the level expressed by its index; the array can be:
    * empty: there are no string to communicate
    * list a string for each element from 0 to **MaxBatteryLevel**
    examples of output are: "Low", "Med", "High"

Errors raised by this method:

  * org.alljoyn.Error.LanguageNotSupported --- The language
  specified is not supported

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

|                          Error name             |                     Error                     |
|-------------------------------------------------|---------------------------------------------- |
| org.alljoyn.Error.LanguageNotSupported          | The language specified is not supported       |

## References

* The XML definition of the [BatteryLevel interface](BatteryLevel-v1.xml)

