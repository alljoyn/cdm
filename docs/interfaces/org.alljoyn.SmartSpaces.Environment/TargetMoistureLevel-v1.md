
# org.alljoyn.SmartSpaces.Environment.TargetMoistureLevel version 1

## Theory of Operation

This interface provides capability to get information about the moisture or
humidity level of an appliance or more in general of a resource of it (e.g. the
clothes moisture a Clothes Dryer).

It is used instead of **org.alljoyn.SmartSpaces.Environment.TargetHumidity**
when the related humidity feature takes values form a discrete set rather
than a continuous range; the values can be associated to descriptive labels
instead of physical quantities.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### MaxMoistureLevel

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

Maximum value of moisture level.

#### MoistureLevel

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Current value of moisture level. The valid values are in the range from 0
(the lowest one) to **MaxMoistureLevel** (the highest one).

#### SelectableMoistureLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It lists the values of moisture level which can be selected; it can be
different because of the appliance state (e.g. different selected operational
cycles can have a different list of selectable moisture levels). It is used to
know in advance which are the values of **MoistureLevel** property that can be
set by _consumer_ using the **SetMoistureLevel** method.

If the array is empty the moisture level can be only monitored.

The elements of the array shall be in ascending and order not bigger than
**MaxMoistureLevel**.

### Methods

#### SetMoistureLevel (level)

Set the value of moisture level.
If the _consumer_ tries to set value which is not supported (i.e. it is not in
the list of **SelectableMoistureLevels** property), then an error should be
returned.

Input arguments:

  * **level** --- byte --- the moisture level value to be set

Errors raised by this method:

  * org.alljoyn.Error.InvalidValue --- if the level value is not one of the
    **SelectableMoistureLevels** list
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    level value is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### GetMoistureLevelInfo (languageTag) -> (info)

Get information about the moisture levels in string format.
It is used to communicate to _consumer_ the strings associated to the moisture
level supported values, so it can display them.

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **info** --- string[] --- the list of strings associated to the moisture
    levels, each element of the array refers to the level expressed by its
    index; the array can be:
      * empty: there are no string to communicate
      * list a string for each element from 0 to **MaxMoistureLevel**
    examples of output are:
      1. "wet", "damp", "dry"

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
messages between _producer_ and _consumer_ to select the moisture level from
remote, it refers to the clothe moisture of a Clothes Dryer.

![Moisture Level Selection Example][MoistureLevelSelectionExample]

[MoistureLevelSelectionExample]: MoistureLevelSelectionExample.png

## References

  * The XML definition of the [TargetMoistureLevel interface](TargetMoistureLevel-v1.xml)
  * The XML definition of the [TargetHumidity interface](TargetHumidity-v1.xml)
