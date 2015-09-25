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



#### FilterInformation

|            |                                                          |
|------------|----------------------------------------------------------|
| Type       | FilterData                                               |
| Access     | read-only                                                |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true  |

Holds static information about the fiter.  Should change to const in 16.04

#### FilterLifeRemaining

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | byte                                                                |
| Access                | read-only                                                             |
| Annotation            | org.freedesktop.DBus.Property.EmitsChangedSignal = true               |

Lifespan Remaining in percentage (100 - 0).  0 indicates replace/clean. 
A simple device may just implement 100/0 or  100/OrderPercent/0 instead of 
implementing the entire range of values

### Methods

No methods are defined for this interface.

### Signals

No signals are emitted by this interface.

### Named Types

#### struct FilterData

* **filterLifeInDays --- UInt16
* **isCleanable  --- boolean
* **orderPercentage --- byte
* **filterManufacturer** --- string
* **filterPartNumber** --- string
* **filterUrl** --- string

   
Static property provides filter information.
* filterLifeInDays is the manufacturers expected time between cleaning/
replacement.  Used to convert percentage into days remaining. 0xFFFF indicate no 
life estimate available.  0 indicates <1 day.
* isCleanable  a boolean signal if true at 0% remaining life filter can be 
cleaned and re-installed.
* orderPercentage is the life remaining at which it is recommended that a new
filter be ordered.  It can have a value of 0 because the filter is cleanable, or 
becuase the remaining life is unpredictable, for example a psid switch.
* filterManufacturer & filterPartNumber act as a tuple to determine type of 
filter.  A null string is acceptable.
* Url can be just a domain or a complete URL to the exact filter.  It may provide
additionl information of a site for ordering.  A null string is acceptable.


### Interface Errors

No errors are raised by this interface

## References

  * The XML definition of the [FilterStatus interface](FilterStatus-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
