# org.alljoyn.SmartSpaces.Devices.CookerHood version 1

## Theory of Operation

The Cooker Hood is a home appliance that usually hangs above the stove or
cook-top and it is used to removes airborne grease, combustion products, fumes,
smoke, odors, heat, and steam from the air by evacuation of the air and
filtration.

The minimum required shared interface for an Cooker Hood is:

  * **org.alljoyn.SmartSpaces.Operation.Control** --- for monitoring and
    controlling the appliance operation time
  * **org.alljoyn.SmartSpaces.Environment.WindStrength** --- for monitoring and
    controlling the fan

Following interfaces can be supported when a specific Cooker Hood implements
extra features:
  * **org.alljoyn.SmartSpaces.Operation.Timer** --- for monitoring and
    controlling the appliance operation time
  * **org.alljoyn.SmartSpaces.Operation.Alerts** --- for communicating alerts
  * **org.alljoyn.SmartSpaces.Operation.FilterStatus** --- for monitoring the
    filter state

Because usually the Cooker Hood are equipped with lighting devices, it is also
possible that these devices implements some interfaces of Lighting Service.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

### AirFlowExtractionMode

|            |                                                          |
| ---------- | -------------------------------------------------------- |
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false |

It indicates the mode of air flow extraction.

The data type is an enumeration and its allowed values and descriptions are
listed below:

  * 0x00 --- **exhaust** --- the hood remove air from the kitchen through a
    pipe to the outside
  * 0x01 --- **recirculation** ---  the hood recycles the air back into the
    kitchen after removing grease and odors using filters.
  * 0xFF --- **not supported** --- the hood doesn't communicate its extraction
    mode

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No error associated to this interface.

## Examples

No example associated to this interface.

## References

  * The XML definition of the [CookerHood interface](CookerHood-v1.xml)
  * The definition of the [Control interface](/org.alljoyn.SmartSpaces.Operation/Control-v1)
  * The definition of the [WindStrength interface](/org.alljoyn.SmartSpaces.Environment/WindStrength-v1)
  * The definition of the [Timer interface](/org.alljoyn.SmartSpaces.Operation/Timer-v1)
  * The definition of the [Alerts interface](/org.alljoyn.SmartSpaces.Operation/Alerts-v1)
  * The definition of the [FilterStatus interface](/org.alljoyn.SmartSpaces.Operation/FilterStatus-v1)
