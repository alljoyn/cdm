# org.alljoyn.SmartSpaces.Devices.FoodProbe version 1

## Theory of Operation

The Food Probe is a device used for checking the preparation of foods (typically
the meat) to ensure that the appropriate and safe internal temperature has been
achieved. Some probes are inserted into the food, other are just placed close to
it.
This interface provides capabilities to interact with specific functions and
resources of Food Probes. It can be used:
  * as stand-alone when it represent an independent device
  * as a sub-unit of another appliance, typically an oven.

The minimum required shared interface for a Food Probe is:
  * **org.alljoyn.SmartSpaces.Environment.TargetTemperature** --- for monitoring
    the measured temperature

Following interfaces can be supported when a specific Food Probe implements
extra features:
  * **org.alljoyn.SmartSpaces.Environment.CurrentTemperature** --- for
    controlling the temperature
  * **org.alljoyn.SmartSpaces.Operation.Control** --- for controlling the on/off
    status

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

### InsertionStatus

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

In some case the Food Probe can work only if it is inserted/connected it the
hosting device, e.g. the oven.
This property indicates whether the Food Probe inserted, not inserted or doesn't
support this feature.

The data type is an enumeration and its allowed values and descriptions are
listed below:

  * 0 --- **not inserted** ---  the Food Probe is inserted
  * 1 --- **inserted** --- the Food Probe is not inserted
  * 255 --- **not supported** --- the Food Probe doesn't communicate the
    insertion status

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No error associated to this interface.

## Examples

No example associated to this interface.

## References

  * [The XML definition of FoodProbe](FoodProbe-v1.xml)
  * The definition of the [TargetTemperature interface](/org.alljoyn.SmartSpaces.Environment/TargetTemperature)
  * The definition of the [CurrentTemperature interface](/org.alljoyn.SmartSpaces.Environment/CurrentTemperature)
  * The definition of the [Control interface](/org.alljoyn.SmartSpaces.Operation/Control)

