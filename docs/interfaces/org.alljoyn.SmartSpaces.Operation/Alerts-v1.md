# org.alljoyn.SmartSpaces.Operation.Alerts version 1

## Theory of Operation

This information provides the status of the alerts of an appliance.

When the appliance (the _producer_) detects by itself an improper functioning on
executing its operations, it can generate some alert messages in order to
communicate it to the controller app (the _consumer_).

There are three kinds of alerts in term of severity, they are listed and
described below:

  * **warning**:
    * there is no risk of damage
    * appliance can work anyway without the best performance
    * it can be removed by user intervention
      * e.g.: missing polishing in Dish Washer

  * **alarm**:
    * there is risk of damage of something (e.g. food) after some time
    * appliance can work, but results are not sure
    * it can be removed by user intervention
      * e.g.: fridge open door

  * **fault**
    * appliance can not work
    * service intervention is needed
      * e.g.: broken components like temperature sensor or water pumps

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### Alerts

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | AlertRecord[]                                           |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The list of current pending alerts.
If there is no pending alert the array is empty.

#### AlertsRequestedAcknowledgement

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | boolean                                                 |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

It indicates whether there is a need of user acknowledgment to give a feedback
for pending alerts.
True means the user acknowledgment is needed.

### Methods

#### AcknowledgeAlerts()

Reset a pending user acknowledgment request. **AlertsRequestedAcknowledgement**
property is set to false.
If the remote control state of the appliance is disabled, an error is returned.

Errors raised by this method:
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

### Signals

No signals are emitted by this interface.

### Named Types

#### struct AlertRecord

**AlertRecord** structure

  * **severity** --- byte --- enumeration field
  * **alertCode** --- uint16 --- st the moment the allowed values are in the
    range from 0x8000 to 0xFFFF, their meaning depends on the specific
    appliances

The first purpose in define this type is to standardize only data structure;
finding also common values to the alerts it is more complex because in principle
they are manufacturer dependent.

Enumeration fields of **severity** are:

  * 0 --- **warning** --- see "Theory of Operation"
  * 1 --- **alarm** --- see "Theory of Operation"
  * 2 --- **fault** --- see "Theory of Operation"

Note about **alertCode**:

So far it is not possible to have interoperability on this codes because they
depends by the specific manufacturer and sometimes by the specific appliance
type.
To understand the **alertCode** values it is expected that separate
documentation are provided and maintained by manufacturers.
This information can be used by _consumers_ to interpret correctly the alerts.

Anyway it is expected that in the future (at the release one of the next
version of the interface) a list of some basic standard cross-manufacturer
**alertCode** values will be defined, e.g. for most common alerts like
Refrigerator Door Open, ...
For this reason the **alertCode** values are organized in two ranges:
  * 0x0000-0x7FFF --- standard codes, reserved for future inter-operable alerts
    codes
  * 0x8000-0xFFFF --- vendor-defined codes

At the moment only the vendor-defined codes range is used.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                          | Error message           |
| --------------------------------------------------- | ----------------------- |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled | Remote control disabled |

## Examples

The following sequence describes an example of "Open Door" alert for
refrigeration appliances.

1. A "Open Door" alert in a refrigerator comes up:
  * the appliance activates visual (User Interface) and acoustic (buzzer)
    feedbacks
  * the interface properties are updated:
    * an "open door" element is loaded in **Alerts** array
    * **AlertsRequestedAcknowledgement** is set to true

2. the user detect and acknowledge it (locally or remotely):
  * the appliance stops the acoustic (buzzer) feedbacks;
    anyway the alert condition is still present
  * the interface properties are updated:
    * **AlertsRequestedAcknowledgement** is set to false
    * The "open door" element is still present in **Alerts** array

3. the door is closed:
  * the alert is no more present, appliance and its User Interface work in
    normal way
  * the interface properties are updated:
    * the "open door" element is removed from **Alerts** array

## References

  * The XML definition of the [Alerts interface](Alerts-v1.xml)
