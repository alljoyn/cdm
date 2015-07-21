# org.alljoyn.Hae.Device.Dryer version 1

## Theory of Operation

Clothes Dryer is a home appliance used to dry laundry, such as clothing and sheets.
This interface provides capabilities to control and monitor resources of
Clothes Dryers.
Those devices share similar features with other of the clothes washing and
drying area/cluster, which are Clothes Washer-Dryers and Clothes Washers.

The followings are minimum required shared interfaces for Clotes Dryers.

  * **org.alljoyn.SmartSpaces.Operation.Control** --- for monitoring and
  controlling the appliance operational state

Some Clothes Dryers have also capabilities allowing:

  * to monitor and control the time of operations
  * to communicate the status of the alerts
  * to monitor and control the clothes moisture level

in those cases following shared interface are implemented:

  * **org.alljoyn.SmartSpaces.Operation.Timer** --- for monitoring and
    controlling the appliance operational times
  * **org.alljoyn.SmartSpaces.Operation.Alerts** --- to communicate alerts
  * **org.alljoyn.SmartSpaces.Environment.MoistureLevel** --- for
    monitoring and controlling the water moisture level

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

It indicates the current phase identifier of the operational cycle.

The data type is an enumeration; the property values are organized in two
ranges:

  * 0x00-0x7F --- **standard phase id** --- the meanings is shared among
    every appliance supporting the DishWasher interface
  * 0x80-0xFF --- **vendor-defined phase id** --- the meanings depends on
    manufacturer so different appliances can use the same values with different
    meanings

At the moment the list of valid **standard cycle phases** is:

  * 0x00 --- **Unavailable** --- the phase value is not available (no phase is
    selected)
  * 0x01 --- ~~**Pre-washing**~~ ---
  * 0x02 --- ~~**Washing**~~ ---
  * 0x03 --- ~~**Rinsing**~~ ---
  * 0x04 --- ~~**Spinning**~~ ---
  * 0x05 --- **Steam** --- see
    [Washer and Dryers Theory Of Operation](ClothesWasherAndDryerTheoryOfOperation)
  * 0x06 --- **Drying** ---  see
    [Washer and Dryers Theory Of Operation](ClothesWasherAndDryerTheoryOfOperation)
  * 0x07 --- **Cooling** ---  see
    [Washer and Dryers Theory Of Operation](ClothesWasherAndDryerTheoryOfOperation)
  * 0x08 --- **AntiCreasing** ---  see
    [Washer and Dryers Theory Of Operation](ClothesWasherAndDryerTheoryOfOperation)
  * 0x7F --- **Not Supported** --- the phase value is not communicated to
    _consumer_

~~Strikethrough~~ values are not used for Dryers.

If the appliance doesn't implement the functionality of monitoring the phase,
this property is always **Not Supported**.

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
    every appliance supporting the ClothesDryer interface; the value 0x7FFF
    means **Not Supported** and it is used when the appliance doesn't
    communicate the property information to the _consumer_
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
the list of **SelectableOperationalCycleIds** property), then a an error should
be returned.

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

  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:

  * **description** --- OperationalCycleDescriptor[] --- the list of cycle
    descriptions

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

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


The following sequence diagram shows an example of which can be the exchanged
messages between _producer_ and _consumer_ to select the operational cycle from
remote.

![Clothes Dryer Selection Example][ClothesDryerSelectionExample]

[ClothesDryerSelectionExample]: ClothesDryerSelectionExample.png

**Figure 1:** Clothes Washer operational cycle selection example


## References

  * The XML definition of the [ClothesDryer interface](ClothesDryer-v1.xml)
  * [Clothes Washer and Dryers Theory Of Operation](ClothesWasherAndDryerTheoryOfOperation)
  * The definition of the [Control interface](/org.alljoyn.SmartSpaces.Operation/Control-v1)
  * The definition of the [Timer interface](/org.alljoyn.SmartSpaces.Operation/Timer-v1)
  * The definition of the [Alerts interface](/org.alljoyn.SmartSpaces.Operation/Alerts-v1)
  * The definition of the [MoistureLevel interface](/org.alljoyn.SmartSpaces.Environment/MoistureLevel-v1)

