# org.alljoyn.SmartSpaces.Devices.IceMaker version 1

## Theory of Operation

Ice maker is a home appliance used to make, store and dispense ice. It can
be stand-alone or embedded in a bigger refrigeration appliance
Ice maker typically is an auxiliary device, that belongs to a refrigerator
appliance.
This interface provides capabilities to interact with specific functions and
resources of Ice makers.

There are no minimum required shared interface for the Ice maker:

Some Ice makers have the capability to be monitored and in case controlled by a
remote controller, in this case the following shared interface is implemented:

  * **org.alljoyn.SmartSpaces.Operation.Control** --- to monitor and control

The operational states that the IceMaker supports to be monitored are:

  * **0** --- **Off**
  * **2** --- **Working**

If the IceMaker can only be monitored it doesn't support any operational
commands (empty array).

If it can be also controlled from remote, the operational commands that it
supports are:

  * **0** --- **Off**
  * **1** --- **On**

Some Ice makers have the capability to be communicate information about their
water source; in this case the following shared interface is implemented:

  * **org.alljoyn.SmartSpaces.Environment.WaterLevel** --- for providing level
    and supply source of water

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

It indicates the currently selected cycle phase identifier. The property
values are organized in two ranges.

  * 0x00-0x7F --- **standard phase id** --- the meanings is shared among
    every appliance supporting the IceMaker interface; the value 0x7F is means
    **Not Supported** and it is used the appliance doesn't communicate the cycle
    phase identifier information to the _consumer_

  * 0x80-0xFF --- **vendor-defined phase id** --- the meanings depends on
    manufacturer so different appliances can use the same values with different
    meanings

At the moment the list of **standard cycle phases** is still under discussion.

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
the range.

If the array is empty the appliance doesn't communicate the cycle phase
identifier value information to the _consumer_.

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

### Signals

No signals are emitted by this interface.

### Named Types

#### struct CyclePhaseInfo

This structure is used to give added information about a cycle phase, using the
value of related temperature as reference.

  * **cyclePhase** --- byte --- cycle phase value
  * **name** --- string --- name of the cycle phase

## Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                             | Error                               |
| -------------------------------------- | ----------------------------------- |
| org.alljoyn.Error.LanguageNotSupported | Language specified is not supported |

## References

  * The XML definition of the [IceMaker interface](IceMaker-v1.xml)
  * The definition of the [Control interface](org.alljoyn.SmartSpaces.Operation/Control-v1)
  * The definition of the [WaterLevel interface](org.alljoyn.SmartSpaces.Environment/WaterLevel-v1)
