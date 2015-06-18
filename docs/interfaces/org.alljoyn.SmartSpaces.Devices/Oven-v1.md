# org.alljoyn.SmartSpaces.Devices.Oven version 1

## Theory of Operation

The Oven is a home appliance used to roast and heat food in a complete stove.
This interface is applicable to different types of Ovens: Gas Ovens, Electrical
Ovens, Steam ovens, Microwave Ovens ...
This interface provides capabilities to interact with specific functions and
resources of FOvens. It can be used:
  * stand alone, to describe a simple oven (single cavity)
  * as sub-unit of a complex device (e.g. a cavity of a multi-cavity oven)

This interfaces provides a set of properties and methods, which let the
_producer_ (i.e. the appliance) to be monitored and controlled by a _consumer_
(usually it is a remote application).

The minimum required shared interface for an Oven is:
  * **org.alljoyn.SmartSpaces.Operation.Control** --- for monitoring and
    controlling the appliance operation state

Following interfaces can be supported when a specific Oven implements extra
features:
  * **org.alljoyn.SmartSpaces.Operation.Timer** --- for monitoring and
    controlling the appliance operation time
  * **org.alljoyn.SmartSpaces.Operation.Alerts** --- for communicating alerts
  * **org.alljoyn.SmartSpaces.Environment.TargetTemperature** --- for monitoring
    the temperature of the cavity
  * **org.alljoyn.SmartSpaces.Environment.CurrentTemperature** --- for setting
    the temperature of the cavity

In some Oven appliances there can be other temperatures, beside the air cavity
one, which are used to execute the operations (the most typical case is the
Food Probe); in this case the added temperature interfaces are defined in a
dedicated object path.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### CyclePhaseId

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the current phase of the operational cycle.

The data type is an enumeration; the property values are organized in two
ranges:

  * 0x00-0x7F --- **standard phase id** --- the meanings is shared among
    every appliance supporting the Oven interface
  * 0x80-0xFF --- **vendor-defined phase id** --- the meanings depends on
    manufacturer so different appliances can use the same values with different
    meanings

At the moment the list of **standard cycle phases id** is still under
discussion; the only standard value are:

  * 0x00 --- **Unavailable** --- the phase value is not available (no phase is
    selected)
  * 0x7F --- **Not Supported** --- the phase value is not communicated to
    _consumer_

#### SupportedCyclePhaseIds

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte[]                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It lists the values of cycle phase identifiers which are supported by the
appliance. It is used to know in advance and which are the values that the
**CyclePhaseId** can assume.

The elements of the array belongs to the **standard phase id** and
**vendor-defined phase id** ranges. In case there can be only element of one of
the ranges.

If the array is empty the appliance doesn't communicate the cycle phase
identifier value information to the _consumer_.
  
#### OperationalCycleId

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | uint16                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates the currently selected operational cycle identifier.

The property values are organized in two ranges:

  * 0x0000-0x7FFF --- **standard cycle id** --- the meanings is shared among
    every appliance supporting the Oven interface; the value 0x7FFF means
    **Not Supported** and it is used when the appliance doesn't communicate the
    property information to the _consumer_
  * 0x8000-0xFFFF --- **vendor-defined cycle id** --- the meanings depends on
    manufacturer so different appliances can use the same values with different
    meanings

At the moment the list of **standard cycle ids** is still under discussion.

#### SupportedOperationalCycleIds

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | uint16[]                                                 |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It lists the values of operational cycle identifiers which are supported by the
appliance. It is used to know in advance and which are the values that the
**OperationalCycleId** property can assume.

The elements of the array belongs to the **standard cycle id** and
**vendor-defined cycle id** ranges. The list can be composed by:

  * both standard and vendor-defined cycle ids
  * only standard cycle ids
  * only vendor-defined cycle ids

If the array is empty the appliance doesn't communicate the operational cycle
identifier value information to the _consumer_.

#### SelectableOperationalCycleIds

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | uint16[]                                                 |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It lists the values of operational cycle identifiers of the appliances which can
be selected by the _consumer_. It is used to know in advance which are the
values that can be used to set the **OperationalCycleId** property using the
**SetOperationalCycleId** method.

The elements of the array belongs to the **standard cycle id** and
**vendor-defined cycle id** ranges.
If the array is empty the operational cycle identifier of the appliance can not
be set by _consumer_.

The elements **SelectableOperationalCycleIds** shall be a subset of the elements
of **SupportedOperationalCycleIds**.

### Methods

#### GetCyclePhaseIdsInfo (languageTag) -> (info)

Get information about the cycle phases which are supported by the appliance.
It is used to communicate to _consumer_ the names of the vendor-defined cycle
phases supported by the appliance, so they can be available remotely.
In principle standard cycle phases have standards names (in English language)
which are defined at specification level and so this method returns information
only about cycle phases belonging to vendor-defined range [0x80 - 0xFF] of
**CyclePhaseId** propriety.
It is possible the case no information is provided as output (i.e. empty array
is returned).

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **info** --- CyclePhaseInfo[] --- the info list of cycle phases

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

#### SetOperationalCycleId (cycleId)

Set the value of operational cycle id.
If the _consumer_ tries to set value which is not supported (i.e. it is not in
the list of **SelectableOperationalCycleIds** property), then a invalid value
error should be returned.

Input arguments:

  * **cycleId** --- int16 --- the operational cycle id value to be set

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- if the command value is not one of the
    **SelectableOperationalCycleIds** list
  * org.alljoyn.Error.FeatureNotAvailable --- if the feature mode is not
    supported by the appliance, i.e. the **SelectableOperationalCycleIds** list
    is empty
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command value is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### GetOperationalCyclesDescription (languageTag) -> (description)

Get information about the cycle which are supported by the appliance.
It is used to communicate to _consumer_ the names and descriptions of the
proprietary cycles supported by the appliance, so they can be available
remotely.
In principle standard cycles have standards names and descriptions (in English
language) which are defined at specification level and so this method returns
information only about operational cycles belonging to "proprietary" range
[0x8000 - 0xFFFF] of **OperationalCycleId** propriety.

Input arguments:

  * **languageTag** --- string --- language to be used in the output strings using
    IETF language tags specified by RFC 5646.

Output arguments:

  * **description** --- OperationalCycleDescriptor[] --- the list of cycle
    descriptions

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

### Signals

No signals are emitted by this interface.

### Named Types

#### struct CyclePhaseInfo

This structure is used to give added information about a cycle phase, using the
value of related temperature as reference.

  * **cyclePhase** --- byte --- cycle phase value
  * **name** --- string --- name of the cycle phase

#### struct OperationalCycleDescriptor

This structure is used to give added information about a cycle, using its
operational cycle id as reference.

  * **cycleId** --- uint16 --- operational cycle id
  * **name** --- string --- name of the operational cycle (e.g. "Cottons", ...)
  * **description** --- string --- description of the operational cycle, it can
  be empty string in case there is no description

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

  * The XML definition of the [Oven interface](Oven-v1.xml)

  * The definition of the [Control interface](/org.alljoyn.SmartSpaces.Operation/Control)
  * The definition of the [Timer interface](/org.alljoyn.SmartSpaces.Operation/Timer)
  * The definition of the [Alerts interface](/org.alljoyn.SmartSpaces.Operation/Alerts)
  * The definition of the [TargetTemperature interface](/org.alljoyn.SmartSpaces.Environment/TargetTemperature)
  * The definition of the [CurrentTemperature interface](/org.alljoyn.SmartSpaces.Environment/CurrentTemperature)

