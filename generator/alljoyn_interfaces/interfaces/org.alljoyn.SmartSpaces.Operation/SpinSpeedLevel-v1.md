# org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel version 1

## Theory of Operation

This interface provides the capability to set the level of spin speed in Clothes
Washers or Clothes Washer-Dryers.
The values are usually associated to descriptive labels or physical quantities
(usually expressed in RPM).

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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const       |

The interface version.

#### MaxLevel

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const |

Maximum value of spin speed level.

#### TargetLevel

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-write                                              |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Target value of spin speed level. The valid values are in the range from 0 (the
lowest one) to **MaxLevel** (the highest one).

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- if the level value is not one of the
    **SelectableLevels** list
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    level value is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### SelectableLevels

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte[]                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The values of spin speed level which can be selected; it can be different
because of the appliance state (e.g., different selected operational cycles can
have a different list of selectable spin speed levels). It is used to know in
advance which are the values of the **TargetLevel** property that can be set
by a _consumer_.

If the array is empty the spin speed level can be only monitored.

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

  * The XML definition of the [SpinSpeedLevel interface](SpinSpeedLevel-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
