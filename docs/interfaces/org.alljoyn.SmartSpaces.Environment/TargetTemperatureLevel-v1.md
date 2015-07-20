# org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel version 1

## Theory of Operation

This interface provides capability to get information about the temperature
level of an appliance or more in general of a resource of it (e.g. the water
temperature of a Clothes Washer).

It is used instead of **org.alljoyn.SmartSpaces.Environment.TargetTemperature**
when the related temperature feature takes values form a discrete set rather
than a continuous range; the values can be associated to descriptive labels
instead of physical quantities.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### MaxTemperatureLevel

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

Maximum value of temperature level.

#### TemperatureLevel

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Current value of temperature level. The valid values are in the range from 0
(the lowest one) to **MaxTemperatureLevel** (the highest one).

#### SelectableTemperatureLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It lists the values of temperature level which can be selected; it can be
different because of the appliance state (e.g. different selected operational
cycles can have a different list of selectable water temperature levels). It is
used to know in advance which are the values of **TemperatureLevel** property
that can be set by _consumer_ using the **SetTemperatureLevel** method.

If the array is empty the temperature level can be only monitored.

The elements of the array shall be in ascending and order not bigger than
**MaxTemperatureLevel**.

### Methods

#### SetTemperatureLevel (level)

Set the value of temperature level.
If the _consumer_ tries to set value which is not supported (i.e. it is not in
the list of **SelectableTemperatureLevels** property), then an error should
be returned.

Input arguments:

  * **level** --- byte --- the temperature level value to be set

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- if the level value is not one of the
    **SelectableTemperatureLevels** list
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    level value is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### GetTemperatureLevelInfo (languageTag) -> (info)

Get information about the temperature levels in string format.
It is used to communicate to _consumer_ the strings associated to the
temperature level supported values, so it can display them.

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **info** --- string[] --- the list of strings associated to the temperature
    levels, each element of the array refers to the level expressed by its
    index; the array can be:
      * empty: there are no string to communicate
      * list a string for each element from 0 to **MaxTemperatureLevel**
    examples of output are:
      1. "cold", "warm", "hot", "very hot"
      2.  "30 °C", "60 °C", "70 °C" ,"90 °C"

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                     |
| org.alljoyn.Error.LanguageNotSupported                        | Language specified is not supported               |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |

## Examples

The following sequence diagram shows an example of which can be the exchanged
messages between _producer_ and _consumer_ to select the temperature level from
remote, it refers to the water temperature of a Clothes Washer.

![Temperature Level Selection Example][TemperatureLevelSelectionExample]

[TemperatureLevelSelectionExample]: TemperatureLevelSelectionExample.png

**Figure 1:** Temperature level selection example

## References

  * The XML definition of the [TargetTemperatureLevel interface](TargetTemperatureLevel-v1.xml)
  * The XML definition of the [TargetTemperature interface](TargetTemperature-v1.xml)
