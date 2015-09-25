# org.alljoyn.SmartSpaces.Environment.TargetHumidity version 1

## Theory of Operation
This interface provides a capability to set a target humidity.
This interface also provides capability to set a target level of moisture or
humidity of an appliance or more in general of a resource of it (e.g. the
clothes moisture of a Clothes Dryer).

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
controllee should adjust the value to min/max value. When the **TargetValue** is
in range defined in **MinValue** and **MaxValue**, but it is not on the grid
in terms of **StepValue**, the controllee should set an appropriate value
that can be accepted. In the case of qualitative representation of target
humidity level, an error shall be returned if the value is not one of the
**SelectableHumidityLevels** list.

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
If this value is same with **MaxValue**, **TargetValue** represents the
set-point value of qualitative level of target humidity.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Maximum value allowed for **TargetValue**. **MaxValue** can’t be greater than
100. If this value is same with **MinValue**, **TargetValue** represents the
set-point value of qualitative level of target humidity.

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
If this interface is for setting the qualitative level of target humidity (when
the **MaxValue** is same with **MinValue**), this value shall be set to 1.

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
The elements of the array shall be in ascending order and not bigger
than **MaxValue**.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.


| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

  * The XML definition of the [TargetHumidity interface](TargetHumidity-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)

