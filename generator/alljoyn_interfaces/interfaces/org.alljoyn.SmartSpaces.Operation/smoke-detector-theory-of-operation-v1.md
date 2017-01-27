## Smoke Detector Theory of Operation version 1

This theory of operation defines the _Common Device Model (CDM) Type_ to be used to identify a device as a smoke detector and explains the interaction of 
various interfaces to assemble a smoke detector.

### Overview

A smoke detector is defined as a device that detects the presence of smoke/fire and emits an alarm, usually audible.

### CDM Type

|  CDM Type ID   |
| -------------- |
| Smoke Detector |

See the [SmartSpaces](/org.alljoyn.SmartSpaces/theory-of-operation-v2) theory of operation for more details on how to use the CDM types.

#### A smoke detector is a binary sensor

Please refer to the [Binary Sensor](binary-sensor-theory-of-operation-v1) theory of operation to see how the CDM interfaces interact to assemble
a smoke detector.

#### org.alljoyn.SmartSpaces.Environment.CurrentTemperature

This interface can be implemented to provide the capability to monitor the current temperature in degrees celsius at the position of the smoke detector.