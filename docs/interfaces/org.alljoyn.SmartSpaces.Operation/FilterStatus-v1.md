# org.alljoyn.SmartSpaces.Operation.FilterStatus version 1

## Theory of Operation


This interface provides the status of a filter.  It is intended to be part of a 
larger object that might have multiple filters.  Example a refrigerator with a 
water filter and odor filter.
The _producer_ has one or more filters and implements a separate interface for 
each filter.  The _consumer_ is an application that is interested in the state 
of the filter.  Possibly to provide an email or push notification to a consumer 
when a filter needs to be replaced.  (The consumer notification portion of the 
use case is outside the scope of AllJoyn HAE).

## Specification

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Version               | 1                                                                     |
| Annotation            | org.alljoyn.Bus.Secure = true                                         |

### Properties

#### FilterType

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                  |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

0 = Water
1 = Air

#### FilterStatusType

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                  |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

0 : Filter Condition
1 : Day Counter
2 : % Lifespan Counter 


#### FilterStatus

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | uint16                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |


The meaning of the FilterStatus Property depends on the value of the FilterStatusType.

|  Filter Status Type  |   Status Value Meaning                                                                      |
|----------------------|---------------------------------------------------------------------------------------------|
| 0                    |  0 - normal condition                                                                       |
|                      |  1 - need to order:  The filter will expire soon and a new one should be obtained.          |
|                      |  2 - need to replace:  The filter has reached the end of life and should be replaced.       |
|                      |  3 - need to clean:  The filter needs to be cleaned, after cleaning it can be reinstalled.  |
| 1                    | Days remaining.  0 indicates replace/clean.                                                 |
| 2                    | Lifespan Remaining in percentage (100 - 0).  0 indicates replace/clean.                     |

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors

No unique errors are associated with this interface.

## References

* The XML definition of the [FilterStatus interface](FilterStatus-v1.xml)
