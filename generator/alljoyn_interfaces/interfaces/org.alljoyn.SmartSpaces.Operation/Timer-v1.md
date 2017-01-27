# org.alljoyn.SmartSpaces.Operation.Timer version 1

## Theory of Operation

This interface provides capability to monitor and control the times when the
appliance executes its operations (i.e. when it starts, when it ends ...).

The appliance executes some operations in order to carry some tasks; in general
these operations have some of the following features:

  * they have a start time
  * they have a end time
  * they can be set to start after a delay
  * they can provide info about the amount of time before the end of operation
  * they can provide info about the operation duration

So it is useful to describe the appliance behavior in term of times and
counters which represent the above features. Note that a specific appliance can
support just a subset of them.
The time information described are related the the operational state of the
appliance is related, so this interface is linked to
**org.alljoyn.SmartSpaces.Operation.Control** interface

The above interfaces provide a set of properties and methods, which let the
 _producer_ (i.e. the appliance) to be monitored and controlled by a _consumer_
(usually it is a remote application).

Most of properties of this interface gives time information related to the
above features; all these times are described in relation to an
**App Defined Epoch**, because it is too restrictive assuming that every
appliance, which supports the interface, can handle time with an absolute
reference (e.g. UTC).
Moreover all these time properties are represented as signed data type for the
following reasons:

  * the same data type is used for each of these properties
  * some negative values are reserved for some special meanings (e.g.
    **Unknown**)
  * since these times are relative, future evolution of the interface can use
    the negative values to express periods in the past: e.g. "10" means "in 10
    seconds", "0" means "now", "-10" means "10 seconds ago", ...

At the moment negative values are used just for special cases, not to represent
the past.


## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### Version

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const       |

The interface version.

#### ReferenceTimer

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | int32                                                    |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It is a Timer (e.g. a time-based propriety, App Defined Epoch, Progressive)
expressed in seconds.
It indicates a time counter to be used as reference for the other time-based
properties of this interface.

Usually it is the time since the last event of power on of the _producer_ (or
more in detail the boot of its connectivity node); anyway the **ReferenceTimer**
reset to 0 action can be triggered by other events which depends on the specific
behaviors of the appliances and so are out of the scope of this specification.

There could be also the extreme case where the **ReferenceTimer** is always 0
because it is reset every seconds; in this case also the values of the other
properties of this interface are updated every seconds.

If no reset events occur its value is increasing of one value each second.

The fact that the **EmitsChangedSignal** is false means that the
**org.freedesktop.DBus.Properties.PropertiesChanged** signal is not guaranteed
to be emitted if the property changes; anyway in the particular case of
**ReferenceTimer** this signal shall be emitted when the value differs from the
expected up-counting evolution in order to synchronize _consumer_ and
_producer_.

So the property change signal shall emitted at least in the following cases:

  * as soon as possible when **ReferenceTimer** is reset to 0
  * if the _producer_ time counter component has known accuracy, the signal
    should be emitted periodically depending on it; e.g. if _producer_ uses an
    internal clock with 0.5% accuracy it should be emit at least once every 200
    seconds.

When this signal is emitted other properties of this interface can change value.

#### TargetTimeToStart

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | int32                                                   |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It is a TimeSpan (e.g. a time-based propriety, App Defined Epoch, Fixed)
expressed in seconds.
It indicates the time when the appliance is expected to start its operation,
starting counting from the last **ReferenceTimer** event.

The special values 0x80000000 (i.e. the lowest representable value with int32)
is used to indicate:
  * no setting of the related feature has been applied to the appliance, i.e.
    an operation with a delay start has not been set

The special values 0x80000001 is used to indicate:
  * it is not supported by the specific appliance

The most typical use case of this property is this:
  * the _producer_ is set to start an operation after some delay time
  * **TargetTimeToStart** give the information about this delay time
  * the operation starts when **ReferenceTimer** is equal to
    **TargetTimeToStart**

#### TargetTimeToStop

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | int32                                                   |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It is a TimeSpan (e.g. a time-based propriety, App Defined Epoch, Fixed)
expressed in seconds.
It indicates the time when the appliance is expected to stop its operation,
starting counting from the last **ReferenceTimer** event.

The special values 0x80000000 (i.e. the lowest representable value with int32)
is used to indicate:

  * no setting of the related feature has been applied to the appliance, i.e.
    an operation with an expected stop time is not executed or has not been set
    (in some cases operations can run indefinitely and stop just by user
    intervention)

The special values 0x80000001 is used to indicate:
  * it is not supported by the specific appliance

The most typical use case of this property is this:
  * the _producer_ is executing an operation or is waiting to start with a known
    delay time
  * **TargetTimeToStop** give the information about the expected time of
    operation end
  * it could be that operation doesn't stops when **ReferenceTimer** is equal to
    **TargetTimeToStop**, because it is just the expected time not the real one

In case of an operation which is set with a delay time and has an expected stop
time **TargetTimeToStart** must be less than **TargetTimeToStart**

#### EstimatedTimeToEnd

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | int32                                                    |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It is a Timer (e.g. a time-based propriety, App Defined Epoch, Progressive)
expressed in seconds.
It indicates the time to the ends of appliance operations.

It is calculated at runtime by device itself during the execution of its
operation; at the begin of operation it should be equal to the difference
between **TargetTimeToStop** and **TargetTimeToStart** (if both are available),
but then it is recalculated and may differentiate from that one because of
environmental conditions (e.g. in a Washing Machine the real duration depends on
water temperature, load ... so the duration showed at selection is just a
forecast).

When there are no recalculations its value is decreasing of one step each
second; when it reaches zero it keeps this value until the end of the operation.

The fact that the **EmitsChangedSignal** is false means that the
**org.freedesktop.DBus.Properties.PropertiesChanged** signal is not guaranteed
to be emitted if the property changes; anyway in the particular case of
**EstimatedTimeToEnd** this signal shall be emitted when the value differs from
the expected down-counting evolution in order to synchronize _consumer_ and
_producer_.

So the property change signal shall emitted at least every time the appliance
recalculate the time to end following the change of the boundary conditions.

The special values 0x80000000 (i.e. the lowest representable value with int32)
is used to indicate:
  * no setting of the related feature has been applied to the appliance, i.e.
    the operation is not executed or its expected time to end is not known

The special values 0x80000001 is used to indicate:
  * it is not supported by the specific appliance


#### RunningTime

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | int32                                                    |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It is a Timer (e.g. a time-based propriety, App Defined Epoch, Progressive)
expressed in seconds.
It indicates the time of the current operation.

Usually its value is increasing of one value each second
It starts counting from 0 when the operation starts and stops counting when the
operation ends.
The up-counting can be hanged and resume again later in some case related to the
_producer_ behavior; e.g. in some appliance the **RunningTime** is not
increasing when the operation is paused.

The fact that the **EmitsChangedSignal** is false means that the
**org.freedesktop.DBus.Properties.PropertiesChanged** signal is not guaranteed
to be emitted if the property changes; anyway in the particular case of
**RunningTime** this signal shall be emitted when the value differs from the
expected up-counting evolution in order to synchronize _consumer_ and
_producer_.

The special values 0x80000000 (i.e. the lowest representable value with int32)
is used to indicate:
  * no setting of the related feature has been applied to the appliance, i.e.
    the operation is not executed.

The special values 0x80000001 is used to indicate:
  * it is not supported by the specific appliance

#### TargetDuration

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | int32                                                   |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It is a TimeSpan (e.g. a time-based propriety, App Defined Epoch, Fixed)
expressed in seconds.
It indicates a time, representing the target duration of the operation as per
user selection.

Before the start of the operation, it is equal to the difference between
TargetTimeToStop and TargetTimeToStart.

The special values 0x80000000 (i.e. the lowest representable value with int32)
is used to indicate:
  * no setting of the related feature has been applied to the appliance, i.e.
    an operation with an expected stop time is not executed or has not been set

The special values is used to indicate:
  * it is not supported by the specific appliance

### Methods

#### SetTargetTimeToStart (targetTimeToStart)

Set the **TargetTimeToStart** property to a new value.
It is called when the _consumer_ wants that the operation, which has been
selected in the _producer_, starts at a defined time.
If a _producer_ device can not execute the setting or doesn't support the remote
control of the start time appropriate errors shall be returned.
Since this method change times related to _producer_ operation, when it is
called other properties of this interface can change value.

Input arguments:

  * **targetTimeToStart** --- int32 --- time to be set

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- if the appliance doesn't support the
    remote control of the start time
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command value is not accepted by the _producer_, because it is in a state
    which doesn't allow the setting
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### SetTargetTimeToStop (targetTimeToStop)

Set the **TargetTimeToStop** property to a new value.
It is called when the _consumer_ wants that the operation, which has been
selected in the _producer_, stops at a defined time.
If a _producer_ device can not execute the setting or doesn't support the remote
control of the stop time appropriate errors shall be returned.
Since this method change times related to _producer_ operation, when it is
called other properties of this interface can change value.

Input arguments:

  * **targetTimeToStop** --- int32 --- time to be set

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- if the appliance doesn't support the
    remote control of the stop time
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command value is not accepted by the _producer_, because it is in a state
    which doesn't allow the setting
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message.
The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                     |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |

## Examples

The following figure shows in a time chart how the properties evolve in the
following case:
  * the operation is selected after 300 seconds from the reset of
    **ReferenceTimer**
  * it starts after 900 seconds from the reset of **ReferenceTimer**
  * it is foreseen to stop after 2700 seconds from the reset of
    **ReferenceTimer**
  * it stops really after 3000 seconds from the reset of **ReferenceTimer**

![OperationalTimerGraphExample][OperationalTimerGraphExample]

[OperationalTimerGraphExample]: OperationalTimerGraphExample.png

**Figure 1:** Operational Timer chart example

## References

  * The XML definition of the [Timer interface](Timer-v1.xml)
  * The definition of the [Control interface](Control-v1)
