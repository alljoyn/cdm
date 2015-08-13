# org.alljoyn.SmartSpaces.Environment.TargetHumidity version 1

## Theory of Operation
This interface is for setting target humidity of the HAE devices such as
humidifier, dehumidifier, etc.
This interface also provides capability to get information about the moisture or
humidity level of an appliance or more in general of a resource of it (e.g. the
clothes moisture a Clothes Dryer). When the related humidity feature takes
values from a discrete set rather than a continuous range, the values can be
associated to descriptive labels instead of physical quantities.

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

The interface version.

#### TargetValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Target set-point value of relative humidity. Releative humidity is the ratio
of the partial pressure of water vapor to the equilibrium vapor pressure of
water at the same temperature. When **MinValue** is the same as **MaxValue**,
then this value represents the target relative humidity as a qualitative level.
Otherwise, this value represents the target relative humidity as a quantitative
value, expressed in percentage.
In the case of quantitative representation of target humidity value, if the
controller tries to set a relative humidity which is out of range, then
an error shall be returned. When the **TargetValue** is in range defined in
**MinValue** and **MaxValue**, but it is not on the grid in terms of
**StepValue**, the controllee can set an appropriate value without returning
an error, or it can refuse to accept the **TargetValue** and return an
appropriate error. But if **StepValue** = 0, it means there is no step value
information available for the controllee device. In this case, the controllee
will go to an appropriate value that can be accepted without returning an error.
In the case of qualitative representation of target humidity level, an error
shall be returned if the value is not one of the **SelectableHumidityLevels**
list.

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
    if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
    control is disabled.

#### MinValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Minimum value allowed for **TargetValue**. **MinValue** can’t be less than 0.
If this value is same with **MaxValue**, **TargetValue** means qualitative level
of current humidity.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value allowed for **TargetValue**. **MaxValue** can’t be greater than
100.
If this value is same with **MinValue**, **TargetValue** means qualitative level
of current humidity.

#### StepValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Step value allowed for **TargetValue** (relative humidity, expressed in
percentage) setting. The step of humidity increment or decrement can be
different for each device. The step can be 1%, 5%, and 10%, etc. Starting from
**MinValue**, valid target value will be represented. Difference between
**MaxValue** and **MinValue** shall be a multiple of **StepValue**.
If this interface is for qualitative level of current humidity (When the
**MaxValue** is same with **MinValue**), this value shall be set to 1.

#### SelectableHumidityLevels

|            |                                                                |
| ---------- | -------------------------------------------------------------- |
| Type       | byte[]                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It lists the values of humidity level which can be selected when this interface
represents the target humidity as a qualitative level (When the **MaxValue**
is same with **MinValue**); it can be different because of the appliance state
(e.g. different selected operational cycles can have a different list of
selectable humidity levels). It is used to let _consumer_ know in advance
which are the values of **TargetValue** property that can be set by _consumer_.

If the array is empty, the humidity level can be only monitored.

The elements of the array shall be in ascending and order not bigger than
**MaxValue**.

### Methods

#### GetHumidityLevelInfo (languageTag) -> (info)

Get information about the humidity levels in string format.
It is used to communicate to _consumer_ the strings associated to the humidity
level supported values, so it can display them. This method can be used when
this interface represents the target humidity as a qualitative level (When the
**MaxValue** is same with **MinValue**).

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **info** --- string[] --- the list of strings associated to the humidity
    levels, each element of the array refers to the level expressed by its index;
    the array can be:
      * empty: there are no string to communicate
      * list a string for each element from 0 to **MaxValue**
    examples of output are:
      1. "wet", "damp", "dry"

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- The feature is not supported.
  * org.alljoyn.Error.LanguageNotSupported --- The language specified is not
    supported.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.


| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.Error.FeatureNotAvailable                         | Feature is not supported                           |
| org.alljoyn.Error.LanguageNotSupported                        | Language specified is not supported                |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

  * The XML definition of the [TargetHumidity interface](TargetHumidity-v1.xml)
