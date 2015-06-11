# org.alljoyn.SmartSpaces.Operation.Control version 1

## Theory of Operation

This interface provides capability:
  * to get information about operational state of an appliance
  * to control appliance with a specific set of commands linked to appliance
    operational state.

Starting from following definitions:

  * the appliance **cycle** is a
    * user- or manufacture-preset sequence of operation
    * so that each operation of the sequence involves its starting and ending
      times or a duration
    * therefore the entire cycle sequence also involves its starting and ending
      times or a duration
  * the **cycle selection** is an
    * action of the user to customize cycles

the appliances can be organized in two categories:

  * **Cyclic Operations Devices**: devices that aim to accomplish cycles
    (e.g. washers, ovens, ...)
  * **Non-Cyclic Operations Devices**: devices that have no cycles (e.g.
    fridges, freezers, ...)

The list of possible operational state values for a generic appliance and their
meaning is the following:

  * **Off** --- the device makes no physical effect and waits for the on command
  * **Idle** --- cycle selection is unfinished, the device can not start to
    execute any operation because of no selected cycle or similar reasons; it
    also includes the case of the robot cleaner when it is being charged, but
    the battery level is not above threshold to start its cleaning operation
    (supported only by "Cyclic Operations Devices");
  * **Working** --- the device is executing its peculiar operation
  * **ReadyToStart** --- the cycle has been selected and the device is waiting
    the start to execute it (supported only by "Cyclic Operations Devices")
  * **DelayedStart** --- the execution of the cycle is being delayed until the
    specified time elapses (supported only by "Cyclic Operations Devices")
  * **Paused** --- the device is in pause, its operation is on hold (supported
    only by "Cyclic Operations Devices")
  * **EndOfCycle** --- the device has completed a cycle and waits for user
    acknowledge or time-out to move to the next state, typically
    **ReadyToStart** or **Idle**; the device can make some post-cycle operations
    in this state, e.g. buzzing, ... (supported only by "Cyclic Operations
    Devices")

The remote controller can monitor the value of the state and make evolve it by
sending the following operational commands:

  * **Off**
  * **On**
  * **Start** (supported only by "Cyclic Operations Devices")
  * **Stop** (supported only by "Cyclic Operations Devices")
  * **Pause** (supported only by "Cyclic Operations Devices")
  * **Resume** (supported only by "Cyclic Operations Devices")

The above list of operational states and commands cover the most general case.
A particular appliance implementation supports just sub-set of them.

All states transitions depending on the received commands are listed below: they
are described as generic cases, anyway the specific devices can refuse commands
for functional reason (e.g. for safety reason an device could not support the
switching on from remote ...):

  * transitions from **Off** state

    * only **On** command is accepted, resulting state depends on the device

  * transitions from **Idle** state

    * **Off** command makes a transition to the **Off** state
    * a **cycle selection** makes a transition to the **ReadyToStart** state:
      it can be accomplished in one of the following ways:
      * locally on the local UI of the device (at a first glance it can be not
        convenient selecting the cycle locally and then activate it remotely;
        anyway for these kind of devices a manual interaction is requested with
        the cycle selection, e.g. putting clothes or dishes in the washers,
        putting food in the oven ...)
      * remotely using a another interface; the remote procedures to select
        cycle remotely are defined in specific interfaces, because they involve
        the usage of parameters and options that are really peculiar to the
        device type
      when the device is in **Idle** state the controller can suggest or
      recommend the user to select the cycle (e.g. a dedicated message on a
      remote App) acting locally or remotely

  * transitions from **Working** state

    * **Off** command makes a transition to the **Off** state
    * **Stop** command on "Cyclic Operations Devices" stops the operation,
      resulting state depends on device
    * **Pause** command makes a transition to the **Paused** state

  * transitions from **ReadyToStart** state

    * **Off** command makes a transition to the **Off** state
    * **Start** command starts the selected operation, the resulting start can
      be **Working** or **DelayedStart** depending on device and selected cycle
      options

  * transitions from **DelayedStart** state

    * **Off** command makes an immediate transition to the **Off** state
    * **Stop** command cancels the delay, resulting state depends on device
    * **Pause** command pauses the delay counter, so it can be resumed later (it
      is a "Pause from Delay"), and makes a transition to the **Paused** state
      back

  * transitions from **Paused** state

    * **Off** command makes a transition to the **Off** state
    * **Stop** command removes pending operation, resulting state depends on
      device
    * **Resume** command restores the prior state, and makes a transition to the
      **Working** or **DelayedStart** state

  * transitions from **EndOfCycle** state

    * **Off** command makes a transition to the **Off** state
    * **Stop** command cancels post-cycle operations, resulting state depends on
      device
    * the device can exit from **EndOfCycle** by local interaction or
      autonomously (e.g. after a timeout); consider that for these kind of
      devices a manual interaction is requested at the end of the cycle (e.g.
      removing clothes from the washers or food from the oven)

The following figure summarizes the state transitions, anyway it is not
comprehensive of all the cases which can be covered by appliances.

![TransitionStateMachine][TransitionStateMachine]

[TransitionStateMachine]: OperationalControlTransitionStateMachine.png

**Figure 1:** Operational Control state chart

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### OperationalState

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the current operational state of an appliance.

The data type is an enumeration and its allowed value are listed below:

  * 0 --- **Off** --- see "Theory of Operation"
  * 1 --- **Idle** --- see "Theory of Operation"
  * 2 --- **Working** --- see "Theory of Operation"
  * 3 --- **RadyToStart** --- see "Theory of Operation"
  * 4 --- **DelayedStart** --- see "Theory of Operation"
  * 5 --- **Paused** --- see "Theory of Operation"
  * 6 --- **EndOfCycle** --- see "Theory of Operation"

#### SupportedOperationalStates

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte[]                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It indicates which are the supported operational states by the specific
appliance. A device may support just a subset of operational states, depending
on its type (e.g. a fridge does not support **Pause** state, ...) or on specific
implementation.

The data type are an enumeration and the allowed value are the same of
**OperationalState** property list.

#### SupportedOperationalCommands

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte[]                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It indicates which are the supported operational commands by the appliance. A
device may support just a subset of operational commands, depending on its type
(e.g. a fridge does not support **Pause** command, ...), on the current
appliance operational state or on specific implementation.

The data type is an enumeration and its allowed value are listed below:

  * 0 --- **Off** --- see "Theory of Operation"
  * 1 --- **On** --- see "Theory of Operation"
  * 2 --- **Start** --- see "Theory of Operation"
  * 3 --- **Stop** --- see "Theory of Operation"
  * 4 --- **Pause** --- see "Theory of Operation"
  * 5 --- **Resume** --- see "Theory of Operation"

### Methods

#### ExecuteOperationalCommand(command)

Execute an operational command. After getting the supported operational states
and the supported operational commands, a valid operational command should be
chosen out of the supported commands list. If a _producer_ device receives an
invalid operational command or can not execute a valid command due to its
internal operational state, then appropriate errors shall be returned.

Input arguments:

  * **command** --- byte --- operational command to be executed, the data type
    are an enumeration and the allowed values are the same of the
    **SupportedOperationalCommands** property list.

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- if the command value is not one of the
    **SupportedOperationalCommands** list
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command value is not accepted by the _producer_, because it is in a state
    which doesn't allow the resulting transition
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

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
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                       |

## Examples

### Example 1

The following sequence describes an example of an execution of a cycle and a
following **Stop** command from remote.

1. user powers on air conditioner appliance:
  * the appliance operation state moves from "Off" into "Working" state

2. the user stops the activity of the appliance:
  * the appliance receives the **Stop** command, accepts the command and moves
  to **Off** state

### Example 2

The following sequence describes an example of a refused operational command
from appliance.

1. appliance state executing a cycle:
  * the appliance operation state is **working**

2. the remote _consumer_ tries to start the appliance:
  * the appliance receives a **Start** command; it is refused because of its
  internal state (appliance is already working), The error reported is
  **org.alljoyn.Hae.Error.NotAcceptableDueToInternalState**

### Example 3

The following example describe the typical implementation of a
**Non-Cyclic Operations Devices**:

* the **SupportedOperationalStates** are { **Off**, **Working** }

* the **SupportedOperationalStates** are { **Off**, **On** }

so the appliance can just toggle from **Off** to **Working** and vice versa.

## References

  * The XML definition of the [Control interface](Control-v1.xml)

