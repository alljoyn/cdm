# org.alljoyn.SmartSpaces.Devices.RobotCleaner version 1

## Theory of Operation

Robot cleaner is an autonomous robotic vacuum cleaner that has intelligent
programming and a limited vacuum cleaning system. This robot cleaner interface
provides capabilities to control and monitor robot cleaner specific functions
and resources. A controller can recognize this device as a robot cleaner if
object descriptions of the About announcement include this interface.

The followings are minimum required shared interfaces for robot cleaner.
  * **org.alljoyn.SmartSpaces.Operation.Control** --- for control of operation

For example, A relationship betweeen operational state of the OperatoinalControl
interface and behavior of robot cleaner can express below:

  * **Idle** --- The robot cleaner is being charged, but the battery level is
  not above threshold to start its cleaning option.
  * **ReadyToStart** --- If the battery charging level goes above that
  threshold, then the operational state will change from Idle to ReadyToStart
  automatically.
  * **Working** --- The robot cleaner is in cleaning operation or on the way
  back to the base station.
  * **Pasued** --- During cleaning operaition, if the robot cleaner receives
  "Pause" command, then it pauses its cleaning operation and waits for "Resume"
  command to resume its cleaning operation.
  * **EndOfCycle** --- The robot cleaner has completed its cleaning operation
  and waits for user acknowledge or time-out to move to the next state. After
  user's acknowledge or time-out, it may or may not return back to the base
  station depending on device implementation.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = false                                 |

This interface has no critical information that should be protected, so does not
require security.

### Properties

#### OperationalCycleId

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It indicates the currently selected operational cycle identifier. The property
values are organized in two ranges.

  * 0x0000-0x7FFF --- **standard cycle id** --- the meanings are shared among
    every appliance supporting the RobotCleaner interface
  * 0x8000-0xFFFE --- **vendor-defined cycle id** --- the meanings depend on
    manufacturer so different appliances can use the same values with different
    meanings
  * 0xFFFF --- **not supported** : the reserved special value for
    "not supported". If there is no supported operational cycle ids,
    this value can be set as 0xFFFF.

At the moment the list of **standard cycle ids** is still under discussion.

#### SupportedOperationalCycleIds

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16[]                                                       |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

It lists the values of operational cycle identifiers which are supported by the
appliance. It is used to know in advance and which are the values that the
**OperationalCycleId** can assume.

The elements of the array belongs to the **standard mode id** and
**vendor-defined mode id** ranges. In case there can be only element of one
of the range. If the array is empty, OperationalModeId shall be set to 0xFFFF
for "not supported".

#### SelectableOperationalCycleIds

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16[]                                                       |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It lists the values of operational cycle identifiers of the appliances which can
be selected remotely. It is used to know in advance which are the values that
can be used to set from remote the **OperationalCycleId** property using the
**SetOperationalCycleId** method.

The elements of the array belongs to the **standard cycle id** and
**vendor-defined cycle id** ranges.
If the array is empty the operational cycle identifier of the appliance can not
be set from remote.

The elements **SelectableOperationalCycleIds** shall be a subset of the elements
of **SupportedOperationalCycleIds**.

#### CyclePhaseId

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It indicates the currently selected cycle phase identifier. The property
values are organized in two ranges.

  * 0x00-0x7F --- **standard phase id** --- the meanings is shared among
    every appliance supporting the RobotCleaner interface
  * 0x80-0xFF --- **vendor-defined phase id** --- the meanings depends on
    manufacturer so different appliances can use the same values with different
    meanings

The enumeration below lists cycles of **standard phase id**.

  * **0** --- **Cleaning** : Clean the area.
  * **1** --- **Homing** : Come back to the home station.

#### SupportedCyclePhaseIds

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte[]                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

It lists the values of cycle phase identifiers which are supported by the
appliance. It is used to know in advance and which are the values that the
**CyclePhaseId** can assume.

The elements of the array belongs to the **standard phase id** and
**vendor-defined phase id** ranges. In case there can be only element of one of the
range.
If the array is empty the appliance doesn't communicate the cycle phase
identifier value information to the controller.


#### TurboMode

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The Robot Cleaner runs more powerful giving cleaner results.

  * **0** --- **Off** : turbo mode off
  * **1** --- **On** : turbo mode on
  * **0xFF** --- **Not Supported** : turbo mode not supported

#### RepeatMode

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The Robot Cleaner will continuously clean until the battery runs out.

  * **0** --- **Off** : repeat mode off
  * **1** --- **On** : repeat mode on
  * **0xFF** --- **Not Supported** : repeat mode not supported

### Methods

#### SetOperationalCycleId (operationalCycleId)

Set an operational cycle id. A robot cleaner starts its operational cycle
immediately after setting or changing its target operational cycle id. If the
device receives an invalid operational cycle id or can’t accept a valid
operational cycle due to its internal state, then an appropriate error
shall be returned.

Input arguments:

  * **operationalCycleId** --- uint16 --- an operational cycle id to set

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if there is no selectable
  operational mode id.
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpace.NotAcceptableDueToInternalState --- Returned if
  value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpace.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### GetOperationalCyclesDescription (languageTag) -> (cyclesDescription)

Get added information about the cycles which are supported by the appliance.
It is used to communicate to controller the names and descriptions of the
vendor-defined cycles supported by the appliance, so they can be available by the
remote controller.
In principle standard cycles have standards names and descriptions which are
defined at specification level, anyway the method can be give information

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
  using IETF language tags specified by RFC 5646.

Output arguments:

  * **cyclesDescription** --- OperationalCycleDescriptor[] --- the list of cycle
    descriptions, they contain only **vendor-defined cycle id**

Errors raised by this method:

  * org.alljoyn.Error.LanguageNotSupported --- the language specified is not
    supported

#### GetCyclePhasesDescription (languageTag) -> (phasesDescription)

Get added information about the phases which are supported by the appliance.
It is used to communicate to controller the names and descriptions of the
vendor-defined phases supported by the appliance, so they can be available by the
remote controller.
In principle standard phases have standard names and descriptions which are
defined at specification level, anyway the method can be give information

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
  using IETF language tags specified by RFC 5646.

Output arguments:

  * **phasesDescription** --- CyclePhaseDescriptor[] --- the list of phase
    descriptions, they contain only **vendor-defined phase id**

Errors raised by this method:

  * org.alljoyn.Error.LanguageNotSupported --- the language specified is not
    supported

#### EnableTurboMode (turboMode)

Enable/disable the turbo mode. The turbo mode is an additional feature for
a powerful clean, so it can be applied to all operational cycles. If the device
can’t enable/disable the turbo mode due to its internal state, then an
appropriate error shall be returned.

Input arguments:

  * **turboMode** --- boolean --- true: enable, false: disable

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if there is no selectable
  operational mode id.
  * org.alljoyn.Error.SmartSpace.NotAcceptableDueToInternalState --- Returned if
  value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpace.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### EnableRepeatMode (repeatMode)

Enable/disable the repeat mode. The repeat mode is an additional feature that
repeats the cleaning in progress until the battery runs out, so it can be
applied to all operational cycles. If the device can’t enable/disable
the repeat mode due to its internal state, then an appropriate error
shall be returned.

Input arguments:

  * **repeatMode** --- boolean --- true: enable, false: disable

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if there is no selectable
  operational mode id.
  * org.alljoyn.Error.SmartSpace.NotAcceptableDueToInternalState --- Returned if
  value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpace.RemoteControlDisabled --- Returned if remote
  control is disabled.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct OperationalCycleDescriptor

This structure is used to give added information about a cycle, using its
operational cycle id as reference.

  * **cycleId** --- uint16 --- operational cycle id
  * **name** --- string --- name of the operational cycle (e.g. "Zigzag", ...)
  * **description** --- string --- description of the operational cycle, it can
  be empty string in case there is no description

#### struct CyclePhaseDescriptor

This structure is used to give added information about a phase, using its
cycle phase id as reference.

  * **phaseId** --- byte --- cycle phase id
  * **name** --- string --- name of the cycle phase (e.g. "Cleaning", ...)
  * **description** --- string --- description of the cycle phase, it can
  be empty string in case there is no description


### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not supported                              |
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.Error.LanguageNotSupported                        | The language specified is not supported            |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

# References

  * The XML definition of the [RobotCleaner interface](RobotCleaner-v1.xml)
  * The definition of the [Operation Control interface](/org.alljoyn.SmartSpaces.Operation/Control-v1)
