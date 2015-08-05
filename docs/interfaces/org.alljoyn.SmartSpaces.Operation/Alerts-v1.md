# org.alljoyn.SmartSpaces.Operation.Alerts version 1

## Theory of Operation

This information provides the status of the alerts of an appliance.

When the appliance (the _producer_) detects by itself an improper functioning on
executing its operations, it can generate some alert messages in order to
communicate it to the controller app (the _consumer_).

Information about alerts can be sent also using the AllJoyn Notification
Service. Anyway Notifications are not suitable in the case of appliances
because:
  * Notifications can inform about alerts as events, not as status; i.e. an
    alert is detected by the _consumer_ only if this one is working and
    connected at the time the alert happens; it is not possible to know the list
    of previous alerts even if they are still pending
  * Notifications don't define a hierarchy based on alerts gravity and user
    intervention.
  * Notifications send human readable strings, which are not inter-operable
  * Notifications are "session-less"

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

#### Version

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | uint16                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

#### Alerts

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | AlertRecord[]                                           |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The list of current pending alerts with information about:
  * the severity
  * the type
  * the state of user acknowledge
If there are no pending alerts the array is empty.

### Methods

#### GetAlertCodesDescription (languageTag) -> (description)

Get information about the Alert code which can be provided by the appliance.
It is used to communicate to _consumer_  descriptions of the alert codes in
order to give to the user some awareness of it.

Input arguments:
  * **languageTag** --- string --- language to be used in the output strings
    using IETF language tags specified by RFC 5646.

Output arguments:
  * **description** --- AlertCodesDescriptor[] --- the list of alert codes
    descriptions; it could be empty if the appliance doesn't have any alert code
    description

Errors raised by this method:
  * org.alljoyn.LanguageNotSupported --- the language specified is not supported

#### AcknowledgeSpecificAlert (alertCode)

Reset the user acknowledgment request state of a specific pending alert, using
the **alertCode** to identify it.
It sets to false the **requestedAcknowledgement** field of related element of
the **Alerts** list.
If there is no pending alert with this **alertCode** or the alert acknowledgment
request state is false, the method has no effect.

If the remote control state of the appliance is disabled, an error is returned.

Input arguments:

  * **alertCode** --- uint16 --- Alert code of the alert to be acknowledge

Errors raised by this method:
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

#### AcknowledgeAllAlerts()

Reset the user acknowledgment request state of any pending alerts.
It sets to false the **requestedAcknowledgement** field of any element of the
**Alerts** list.
If there are no pending alerts or if the acknowledgment request state of any
pending alert is false, the method has no effect.

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
  * **alertCode** --- uint16 --- at the moment the allowed values are in the
    range from 0x8000 to 0xFFFF, their meaning depends on the specific
    appliances
  * **requestedAcknowledgement** --- boolean --- acknowledgment request state:
    it indicates whether there is a request of user acknowledgment for this
    specific alert;
      * **false** --- the user acknowledgment is not requested from the beginning
        or this alert has been already acknowledged
      * **true** -- the user acknowledgment is needed

Enumeration values of **severity** are:

  * 0 --- **warning** --- see "Theory of Operation"
  * 1 --- **alarm** --- see "Theory of Operation"
  * 2 --- **fault** --- see "Theory of Operation"

The first purpose in defining this type is to standardize only the data
structure; finding also common values for the alerts is more complex because in
principle they are manufacturer dependent.

Note about **alertCode**:

So far it is not possible to have interoperability on these codes because they
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

#### struct AlertCodesDescriptor

This structure is used to give added information about alert, using its alert
code as reference.

  * **alertCode** --- uint16 --- the alert code value of the **AlertRecord**
    structure
  * **description** --- string --- description of the alert code;
    e.g. "missing polishing", "open door", ...

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
    * **requestedAcknowledgement** of this element is true

2. the user detect and acknowledge it (locally or remotely):
  * the appliance stops the acoustic (buzzer) feedbacks;
    anyway the alert condition is still present
  * the interface properties are updated:
    * **requestedAcknowledgement** is set to false; if the user action is remote
      it is done via **AcknowledgeSpecificAlert** or **AcknowledgeAllAlerts**
      methods
    * The "open door" element is still present in **Alerts** array

3. the door is closed:
  * the alert is no more present, appliance and its User Interface work in
    normal way
  * the interface properties are updated:
    * the "open door" element is removed from **Alerts** array

## References

  * The XML definition of the [Alerts interface](Alerts-v1.xml)
