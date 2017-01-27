## Water Sensor Theory of Operation version 1

This theory of operation defines the _Common Device Model (CDM) Type_ to be used to identify a device as a water sensor and explains the interaction of 
various interfaces to assemble a water sensor.

### Overview

A water sensor is defined as a device that detects the presence of water and emits an alarm, usually audible.

### CDM Type

|  CDM Type ID  |
| ------------- |
| Water Sensor  |

See the [SmartSpaces](/org.alljoyn.SmartSpaces/theory-of-operation-v2) theory of operation for more details on how to use the CDM types.

#### A water sensor is a binary sensor

Please refer to the [Binary Sensor](binary-sensor-theory-of-operation-v1) theory of operation to see how the CDM interfaces interact to assemble
a water sensor.