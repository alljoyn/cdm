## Speaker Theory of Operation version 1

This theory of operation defines the _Common Device Model (CDM) Type_ to be used to identify a device as a speaker and explains the interaction of 
various interfaces to assemble a speaker.

### Overview

A speaker is defined as a device that receives an incoming signal and emits it as sound.
The CDM service framework defines a common set of standard interfaces that work
across multiple device types. This document illustrates how to combine a subset
of those interfaces to create a speaker.

### CDM Type

|  CDM Type ID  |
| ------------- |
| Speaker       |

See the [SmartSpaces](/org.alljoyn.SmartSpaces/theory-of-operation-v2) theory of operation for more details on how to use the CDM types.

#### org.alljoyn.SmartSpaces.Operation.AudioVolume

This interface exposes the ability to monitor and control the volume of the speaker. It also contains the ability
to mute the speaker without changing the current volume level.

#### org.alljoyn.SmartSpaces.Operation.OnOffStatus

This interface provides the capability to monitor the current power status of the speaker and establish whether it's currently 
active or inactive. This interface does not provide the ability to control the power status and requires the act of activating/deactivating 
to be done elsewhere, e.g., via a physical switch.

#### org.alljoyn.SmartSpaces.Operation.OnControl

This interface provides the capability to activate the speaker.

#### org.alljoyn.SmartSpaces.Operation.OffControl

This interface provides the capability to deactivate the speaker.

#### org.alljoyn.SmartSpaces.Operation.RemoteControllability

This interface provides the capability for a speaker to have its remote controllability enabled or disabled. 
When RemoteControllability is disabled, all remote functionality that modifies or controls the speaker will return an error.