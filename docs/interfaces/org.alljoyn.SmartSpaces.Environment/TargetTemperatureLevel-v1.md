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

#### MaxLevel

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

Maximum value allowed for target temperature level setting.

#### TargetLevel

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-write                                              |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Target set-point value of temperature level. The valid values are in the range
from 0 (the lowest one) to **MaxLevel** (the highest one).
If the _consumer_ tries to set value which is not supported (i.e. it is not in
the list of **SelectableTemperatureLevels** property), then an error shall
be returned.

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- if the level value is not one of the
    **SelectableTemperatureLevels** list
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    level value is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### SelectableTemperatureLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It lists the values of temperature level which can be selected; it can be
different because of the appliance state (e.g. different selected operational
cycles can have a different list of selectable water temperature levels). It is
used to know in advance which are the values of **TargetLevel** property
that can be set by _consumer_.

If the array is empty the target temperature level can be only monitored.

The elements of the array shall be in ascending order and not bigger than
**MaxLevel**.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                     |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |

## References

  * The XML definition of the [TargetTemperatureLevel interface](TargetTemperatureLevel-v1.xml)
  * The XML definition of the [TargetTemperature interface](TargetTemperature-v1.xml)
