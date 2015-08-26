# org.alljoyn.SmartSpaces.Operation.BatteryStatus version 1

## Theory of Operation

This interface provides capability to represent remaining battery status.
The battery status would be displayed as quantitative remaining battery
percentage or qualitative remaining battery level.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### Version

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Interface version

#### BatteryValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current remaining battery value.
If the MaxBatteryValue is 100, the BatteryValue means remaining battery
percentage. And if the MaxBatteryValue is less than 100, this value means
qualitative remaining battery level.

#### MaxBatteryValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Maximum value allowed for the BatteryValue. This value is not allowed
more than 100.

### Methods

#### GetBatteryLevelsInfo (languageTag) -> (info)

Get additional information about the battery levels in string format.
The information strings associated with the battery level can be displayed
on the controller side. This method can be used when this interface represents
qualitative level of remaining battery. (When the MaxBatteryValue is less
than 100).

Input arguments:

  * **languageTag** --- string --- languageTag to be used in the output strings
  using IETF language tags specified by RFC 5646.

Output arguments:

  * **batteryLevelsInfo** --- string[] --- the list of strings
  associated with the battery levels, each element of the array refers
  to the level expressed by its index; the array can be:
    * empty: there are no string to communicate
    * list a string for each element from 0 to **MaxBatteryValue**
    examples of output are: "Low", "Med", "High"

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if the MaxBatteryValue
  is 100.
  * org.alljoyn.Error.LanguageNotSupported --- Returned if the language
  specified is not supported.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

|                          Error name             |                     Error                     |
|-------------------------------------------------|---------------------------------------------- |
| org.alljoyn.Error.FeatureNotAvailable           | Feature not supported                         |
| org.alljoyn.Error.LanguageNotSupported          | The language specified is not supported       |


## References

  * The XML definition of the [BatteryStatus interface](BatteryStatus-v1.xml)
