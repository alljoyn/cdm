# org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase version 1

## Theory of Operation

Dishwasher is a home appliance used to clean dishes and eating utensils.  This
interface provides a capability to monitor the cycle phase of the dishwasher.

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

Interface version.

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
    every appliance supporting the DishWashingCyclePhase interface
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


### Methods


#### GetVendorPhasesDescription (languageTag) -> (phasesDescription)

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

  * **languageTag** --- string --- preferred language to be used in selecting 
the output strings using IETF language tags specified by RFC 5646.  The supported 
language tags match those from the SupportedLanguages property of the 
AboutInterface.  If an array or phase description is returned empty in one 
language, then it must be returned empty in all supported languages.

Output arguments:

  * **phasesDescription** --- CyclePhaseDescriptor[] --- the list of cycle phases
    descriptions

Errors raised by this method:

  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

### Signals

No signals are emitted by this interface.

### Named Types

#### struct CyclePhaseDescriptor

This structure is used to give added information about a phase, using its
cycle phase as reference.

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
| org.alljoyn.Error.LanguageNotSupported                        | Language specified is not supported               |

## Examples

No examples associated to this interface.

## References

  * The XML definition of the [DishWashingCyclePhase interface](DishWashingCyclePhase-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
