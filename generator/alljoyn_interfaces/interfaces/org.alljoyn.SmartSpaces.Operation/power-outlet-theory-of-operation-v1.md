## Plug Theory of Operation version 1

This theory of operation defines the _Common Device Model (CDM) Type_ to be used to identify a device as a power outlet and explains the interaction of 
various interfaces to assemble a power outlet.

### Overview

A power outlet is defined as a device that connects portable electronic equipment to a power supply. The CDM service framework defines a common set 
of standard interfaces that work across multiple device types. This document illustrates how to combine a subset of those interfaces to create a 
power outlet.

### CDM Type

|  CDM Type ID  |
| ------------- |
| Power Outlet  |

See the [SmartSpaces](/org.alljoyn.SmartSpaces/theory-of-operation-v2) theory of operation for more details on how to use the CDM types.

### A system to monitor power and usage

#### org.alljoyn.SmartSpaces.Operation.OnOffStatus

This interface provides the capability to monitor the current power status of the outlet.
Electricity can only pass through the outlet to the connected equipment if the _IsOn_ property is set to true.  

By providing this interface, with no controls (see below), the act of activating and deactivating would 
have to be done by other means, e.g., via an external, physical mechanism.

#### org.alljoyn.SmartSpaces.Operation.CurrentPower

This interface can be added to provide the capability to monitor the instantaneous
power consumption (in watts) of the power outlet.

### Extending to add controls

#### org.alljoyn.SmartSpaces.Operation.OnControl

This interface can be added to provide the capability to activate the power outlet to allow electricity to pass through it.

#### org.alljoyn.SmartSpaces.Operation.OffControl

This interface can be added to provide the capability to deactivate the power outlet thus stopping electricity from passing through it.

#### org.alljoyn.SmartSpaces.Operation.EnergyUsage

This interface can be added to provide access to monitor and reset the cumulative 
energy consumption of the device (in kWh) of the power outlet.

#### org.alljoyn.SmartSpaces.Operation.RemoteControllability

This interface provides the capability to enable or disable all controls on the power outlet. When RemoteControllability is
disabled, all attempts to remotely control the outlet will return an error.
