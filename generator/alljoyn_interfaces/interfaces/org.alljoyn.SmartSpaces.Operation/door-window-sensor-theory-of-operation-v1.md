## Door/Window Sensor Theory of Operation version 1

This theory of operation defines the _Common Device Model (CDM) Type_ to be used to identify a device as a door/window sensor and explains the interaction of 
various interfaces to assemble a door/window sensor.

### Overview

A door/window sensor is defined as a device that detects if a door/window is closed or not.

### Common Device Model (CDM) Type

|  CDM Type IDs |
| ------------- |
| Door Sensor   |
| Window Sensor |

See the [SmartSpaces](/org.alljoyn.SmartSpaces/theory-of-operation-v2) theory of operation for more details on how to use the CDM types.

#### org.alljoyn.SmartSpaces.Operation.ClosedStatus

This interface exposes the capability to monitor whether the door/window sensor has detected that the door/window is or isn't closed.  

A door/window sensor must implement this interface.

#### A Battery powered door or window sensor

Please refer to the [BatteryPowered](batter-powered-theory-of-operation-v1) theory of operation.