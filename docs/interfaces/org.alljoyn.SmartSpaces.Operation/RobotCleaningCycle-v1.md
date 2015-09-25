# org.alljoyn.SmartSpaces.Operation.RobotCleaningCycle version 1

## Theory of Operation

Robot cleaner is an autonomous robotic vacuum cleaner that has intelligent
programming and a limited vacuum cleaning system. This interface provides
a capability to control and monitor the operational cycle and its phase
of the robot cleaner.

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

#### OperationalCycle

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It indicates the currently selected operational cycle. The property values are
organized in two ranges.

  * 0x0000-0x7FFF --- **standard cycles** --- the meanings are shared among
    every appliance supporting the RobotCleaningCycle interface
  * 0x8000-0xFFFE --- **vendor-defined cycles** --- the meanings depend on
    manufacturer so different appliances can use the same values with different
    meanings
  * 0xFFFF --- **not supported** : the reserved special value for "not supported".
    If there is no supported operational cycle, this value can be set as 0xFFFF.

At the moment the list of **standard cycles** is still under discussion.

Errors raised by setting this property:

  * org.alljoyn.Error.InvalidValue --- if the command value is not one of the 
    **SupportedOperationalCycles** list
  * org.alljoyn.Error.SmartSpace.NotAcceptableDueToInternalState --- if value 
    is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpace.RemoteControlDisabled --- if remote control 
    is disabled.

#### SupportedOperationalCycles

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16[]                                                       |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It lists the values of operational cycles which are supported by the appliance.
It is used to know in advance and which are the values that the
**OperationalCycle** can assume.

The elements of the array belongs to the **standard cycles** and
**vendor-defined cycles** ranges. In case there can be only element of one
of the range. If the array is empty, OperationalCycle shall be set to 0xFFFF
for "not supported".

#### CyclePhase

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It indicates the currently selected cycle phase. The property values are organized
in two ranges.

  * 0x00-0x7F --- **standard phases** --- the meanings are shared among
    every appliance supporting the RobotCleaningCycle interface
  * 0x80-0xFF --- **vendor-defined phases** --- the meanings depend on
    manufacturer so different appliances can use the same values with different
    meanings

The enumeration below lists the defined **standard phases**.

  * **0** --- **Cleaning** : Clean the area.
  * **1** --- **Homing** : Come back to the home station.

#### SupportedCyclePhases

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte[]                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It lists the cycle phases which are supported by the appliance. It is used to
know in advance and which are the values that the **CyclePhase** can assume.

The elements of the array belongs to the **standard phases** and
**vendor-defined phases** ranges. In case there can be only element of one of the
range. If the array is empty the appliance doesn't communicate the supported
cycle phase information to the controller.

### Methods

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
    descriptions, they contain only **vendor-defined cycles**

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
    descriptions, they contain only **vendor-defined phases**

Errors raised by this method:

  * org.alljoyn.Error.LanguageNotSupported --- the language specified is not
    supported

### Signals

No signals are emitted by this interface.

### Named Types

#### struct OperationalCycleDescriptor

This structure is used to give added information about a cycle, using its
operational cycle as reference.

  * **cycle** --- uint16 --- operational cycle id
  * **name** --- string --- name of the operational cycle (e.g. "Zigzag", ...)
  * **description** --- string --- description of the operational cycle, it can
  be empty string in case there is no description

#### struct CyclePhaseDescriptor

This structure is used to give added information about a phase, using its
cycle phase as reference.

  * **phase** --- byte --- identifier of the cycle phase
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

  * The XML definition of the [RobotCleaningCycle interface](RobotCleaningCycle-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)
