# org.alljoyn.SmartSpaces.Operation.TriggerSensor version 1

## Theory of Operation

This interface provides to the _consumer_ (i.e., a remote application) the capability to monitor if a sensor on the _producer_ (i.e., the appliance) 
has met its trigger condition.

The requirements for what causes the sensor to meet its trigger condition is dependent on the context of the _producer_. This could come 
from a single event (i.e., the laser on a door sensor is blocked) or a threshold is reached (i.e., a smoke/water sensor has 
detected a sufficient quantity of smoke/water).  

If the sensor detects that its trigger condition has been met, then it should enter the **Triggered** state.  
When the condition that caused the trigger is no longer true, the sensor should return back into the **Condition not met** state.

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### Version

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | uint16                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const|

The interface version.

#### CurrentlyTriggered

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | boolean                                                 |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The state of whether or not the sensor has detected its trigger condition.

  * false --- **Condition not met** --- the sensor is not in a triggered state
  * true --- **Triggered** --- the sensor is in a triggered state

### Methods

No methods are exposed by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

No error associated to this interface.

## References

  * The [TriggeredSensor interface](TriggeredSensor-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v2)