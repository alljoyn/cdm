## Lock Theory of Operation version 1

This theory of operation explains the interaction of various interfaces to
assemble a locking mechanism for a device.

### Overview

A lock is defined as a device or mechanism that can be put into a locked/unlocked
state. The Common Device Model service framework defines a common set of standard interfaces that work
across multiple device types. This document illustrates how to combine a subset
of those interfaces to create a lock.


### A Secure System

#### org.alljoyn.SmartSpaces.Operation.IsLocked

This interface provides the capability to monitor the current
status of the locking mechanism and establish whether its currently engaged (locked) or
disengaged (unlocked). A minimal lock may only implement this interface.

The lock on a front door or a safe may only implement the capability to be monitored 
for security reasons. The locking/unlocking would still require a physical
action by a person.

The door on a front loading washing machine may also want to expose this interface. 
The engagement/disenagement of the lock is governed by the washing machine's cycle but an
event may be sent to the user to collect their clothes when the door is unlocked.


### A Security System

#### Adding org.alljoyn.SmartSpaces.Operation.LockControl

This interface provides the capability to engage the locking mechanism.

Locks may have this capability so that multiple locks can be engaged at once (for example, in the event of an alarm).


### A More General Purpose System

#### Adding org.alljoyn.SmartSpaces.Operation.UnlockControl

This interface provides the capability to disengage the locking mechanism.

The addition of this interface is better suited to a more general purpose locking mechanism
where the convenience of being able to have complete control over the mechanism outweighs
any potential security risks in having the unlocking mechanism exposed over a network. 
The vendor may choose to govern the usage of the locking/unlocking interfaces through a software solution.


#### org.alljoyn.SmartSpaces.Operation.RemoteControllability

This interface provides the capability for a locking mechanism to be have its
locking/unlocking controls enabled or disabled. When RemoteControllability is
disabled, the Lock/Unlock functionality will return an error.
