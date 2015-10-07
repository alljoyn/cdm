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


#### Version

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | uint16                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |



#### ExpectedLifeDays

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | uint16                                               |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

ExpectedLifeInDays is the manufacturers expected time between cleaning/
replacement.  This is the design life of the recommended filter, and can be used 
to convert percentage into days remaining. using the formula:

* DaysRemaining: = ExpectedLifeDays*LifeRemaining.

0xFFFF indicate no life estimate available.  0 indicates less than 1 day.  
Should change to const once that feature is available in Core.

#### IsCleanable

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | boolean                                                  |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

If the property is true a new filter does not need to be ordered, just clean. 

#### OrderPercentage

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | byte                                                     |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The LifeRemaining value  at which it is recommended that a new filter be 
ordered.  It can have a value of 0 because the filter is cleanable, or 
because the remaining life is unpredictable, for example a psid switch.

#### Manufacturer 

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | String                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The manufacturer of the recommended filter for the device. Manufacturer and 
PartNumber act as a tuple to determine type of filter.  A null string is 
acceptable.  Should change to const once that feature is available in Core.

#### PartNumber 

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | String                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

The manufacturer of the recommended filter for the device. Manufacturer and 
PartNumber act as a tuple to determine type of filter.  A null string is 
acceptable.  Should change to const once that feature is available in Core.

#### Url 

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | String                                                   |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Url can be just a domain or a complete URL to the exact filter.  It may provide
additional information of a site for ordering.  A null string is acceptable.
Should change to const once that feature is available in Core.


#### LifeRemaining

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

Lifespan Remaining in percentage (100 - 0).  0 indicates replace/clean. 
A simple device may just implement 100/0 or 100/OrderPercent/0 instead of 
implementing the entire range of values

### Methods

No methods are defined for this interface.

### Signals

No signals are emitted by this interface.

### Named Types

No Named Types are required by this interface.

### Interface Errors

No errors are raised by this interface

## References

  * The XML definition of the [FilterStatus interface](FilterStatus-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
