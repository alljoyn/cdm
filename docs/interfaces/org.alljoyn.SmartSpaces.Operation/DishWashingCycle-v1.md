# org.alljoyn.SmartSpaces.Operation.DishWashingCycle version 1

## Theory of Operation

DishWasher is a home appliance used to clean dishes and eating utensils.
This interface provides a capability to control and monitor the operational
cycle and its phase of the dish washer.

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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Interface version

#### OperationalCycle

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | uint16                                                  |
| Access     | read-write                                              |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Current operational cycle.

The property values are organized in two ranges:

  * 0x0000-0x7FFF --- **standard cycles** --- the meanings are shared among
    every appliance supporting the DishWashingCycle interface; 
    the value 0x7FFF means **Not Supported** and it is used when the appliance 
    doesn't communicate the property information to the _consumer_
  * 0x8000-0xFFFF --- **vendor-defined cycles** --- the meaning depends on
    manufacturer so different appliances can use the same values with different
    meanings

At the moment the list of **standard cycles** is still under discussion.

Errors raised by setting this property:
  * org.alljoyn.Error.InvalidValue --- if the command value is not one of the
    **SupportedOperationalCycles** list
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command value is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### SupportedOperationalCycles

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | uint16[]                                                 |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

It lists the values of operational cycles which are supported by the appliance.
It is used to know in advance and which are the values that the
**OperationalCycle** property can assume.

The elements of the array belongs to the **standard cycles** and
**vendor-defined cycles** ranges. The list can be composed by:

  * both standard and vendor-defined cycles
  * only standard cycle(s)
  * only vendor-defined cycle(s)

If the array is empty the appliance doesn't communicate the operational cycle
identifier value information to the _consumer_.

#### CyclePhase

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the current phase of the operational cycle.

The data type is an enumeration; the property values are organized in two
ranges:

  * 0x00-0x7F --- **standard cycle phases** --- the meanings are shared among
    every appliance supporting the DishWashingCycle interface
  * 0x80-0xFF --- **vendor-defined phases** --- the meanings depend on
    manufacturer so different appliances can use the same values with different
    meanings

At the moment the list of valid **standard cycle phases** is:
  * 0x00 --- **Unavailable** --- the phase value is not available (no phase is
    selected)
  * 0x01 --- **Pre-Wash** --- the appliance is executing a preliminary wash, to
    remove some particular kind of dirt
  * 0x02 --- **Wash** --- the appliance is executing the main wash
  * 0x03 --- **Rinse** --- the appliance is rinsing the dishes to remove soap
  * 0x04 --- **Dry** --- the appliance is drying the dishes
  * 0x7F --- **Not Supported** --- the phase value is not communicated to
    _consumer_

If the appliance doesn't implement the functionality of monitoring the phase,
this property is always **Not Supported**.

#### SupportedCyclePhases

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte[]                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

It lists the values of cycle phases which are supported by the appliance.
It is used to know in advance and which are the values that the **CyclePhase**
can assume.

The elements of the array belongs to the **standard phases** and
**vendor-defined phases** ranges. In case there can be only elements of one of
the range.

If the array is empty the appliance doesn't communicate the supported
cycle phases information to the _consumer_.

### Methods

#### GetOperationalCyclesDescription (languageTag) -> (cyclesDescription)

Get information about the cycle which are supported by the appliance.
It is used to communicate to _consumer_ the names and descriptions of the
vendor-defined cycles supported by the appliance, so they can be available
remotely.
In principle standard cycles have standards names and descriptions (in English
language) which are defined at specification level and so this method returns
information only about operational cycles belonging to "vendor-defined" range
[0x8000 - 0xFFFF] of **OperationalCycle** propriety.

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings using
    IETF language tags specified by RFC 5646.

Output arguments:

  * **cyclesDescription** --- OperationalCycleDescriptor[] --- the list of cycle
    descriptions

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

#### GetCyclePhasesDescription (languageTag) -> (phasesDescription)

Get information about the cycle phases which are supported by the appliance.
It is used to communicate to _consumer_ the names of the vendor-defined cycle
phases supported by the appliance, so they can be available remotely.
In principle standard cycle phases have standards names (in English language)
which are defined at specification level and so this method returns information
only about cycle phases belonging to vendor-defined range [0x80 - 0xFF] of
**CyclePhase** propriety.
It is possible the case no information is provided as output (i.e. empty array
is returned).

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **phasesDescription** --- CyclePhaseDescriptor[] --- the list of cycle phases
    descriptions

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

### Signals

No signals are emitted by this interface.

### Named Types

#### struct OperationalCycleDescriptor

This structure is used to give added information about a cycle, using its
operational cycle id as reference.

  * **cycle** --- uint16 --- identifier of the operational cycle
  * **name** --- string --- name of the operational cycle (e.g. "Cottons", ...)
  * **description** --- string --- description of the operational cycle,
    it can be empty string in case there is no description

#### struct CyclePhaseDescriptor

This structure is used to give added information about a cycle phase, using the
value of related temperature as reference.

  * **phase** --- byte --- identifier of the cycle phase
  * **name** --- string --- name of the cycle phase
  * **description** --- string --- description of the operational cycle phase,
    it can be empty string in case there is no description

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                     |
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not available                             |
| org.alljoyn.Error.LanguageNotSupported                        | Language specified is not supported               |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |

## Examples

No examples associated to this interface.

## References

  * The XML definition of the [DishWashingCycle interface](DishWashingCycle-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1.md)
