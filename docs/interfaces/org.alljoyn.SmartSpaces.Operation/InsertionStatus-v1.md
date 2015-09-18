# org.alljoyn.SmartSpaces.Operation.InsertionStatus version 1

## Theory of Operation

This interface provides the status of any object that can report a two state
"inserted"/"not inserted" condition.
It is used for some components which can work only if it is inserted or
connected to the hosting device: e.g. a Food Probe to be used with an oven.

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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

Interface version.
The EmitsChangedSignal of this property should be modified to const once that
feature is available.


#### IsInserted

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | boolean                                                 |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

True indicates that device is inserted, false indicates the it is not inserted.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors

No unique errors are associated with this interface.

## References

  * The XML definition of the [InsertionStatus interface](InsertionStatus-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)

