## Switch Theory of Operation version 1

This theory of operation explains the interaction of various interfaces to
assemble a switch.

### Overview

A switch is defined as a device or mechanism that can be activated or deactivated.
The Common Device Model service framework defines a common set of standard interfaces that work
across multiple device types. This document illustrates how to combine a subset
of those interfaces to create a switch.

#### org.alljoyn.SmartSpaces.Operation.OnOffStatus

This interface provides the capability to monitor the current
status of the switch and establish whether it's currently active or
inactive. A minimal switch may only implement this interface and
require the act of activating and deactivating to be done via a physical switch.

#### org.alljoyn.SmartSpaces.Operation.OnControl

This interface provides the capability to activate the switch.

#### org.alljoyn.SmartSpaces.Operation.OffControl

This interface provides the capability to deactivate the switch.

#### org.alljoyn.SmartSpaces.Operation.RemoteControllability

This interface provides the capability for a switch to be have its controls
enabled or disabled. When RemoteControllability is disabled, the OnControl/OffControl
functionality will return an error.
