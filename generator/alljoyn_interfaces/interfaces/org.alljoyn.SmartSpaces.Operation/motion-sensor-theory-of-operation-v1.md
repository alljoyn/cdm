## Motion Sensor Theory of Operation version 1

This theory of operation defines the _Common Device Model (CDM) Type_ to be used to identify a device as a motion sensor and explains the interaction of 
various interfaces to assemble a motion sensor.

### Overview

A motion sensor is defined as a device that detects the presence of motion. The motion sensor can only report a two state situation
where the sensor has detected enough motion to trigger a state switch. An alert can be emitted when the sensor switches state, or another device with an 
audible alarm can listen for the signal from the state switch of the sensor to sound its alarm.

### CDM Type

|  CDM Type ID  |
| ------------- |
| Motion Sensor |

See the [SmartSpaces](/org.alljoyn.SmartSpaces/theory-of-operation-v2) theory of operation for more details on how to use the CDM types.

#### A motion sensor is a binary sensor

Please refer to the [Binary Sensor](binary-sensor-theory-of-operation-v1) theory of operation to see how the CDM interfaces interact to assemble
a motion sensor.