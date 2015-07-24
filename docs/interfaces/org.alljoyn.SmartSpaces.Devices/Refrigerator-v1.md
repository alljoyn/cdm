# org.alljoyn.SmartSpaces.Devices.Refrigerator version 1

## Theory of Operation

Refrigerator is a home appliance used to store food at temperatures which are a
few degrees above the freezing point of water.
This interface provides capabilities to interact with specific functions and
resources of refrigerators.

The minimum required shared interface for the Refrigerator is:

  * **org.alljoyn.SmartSpaces.Operation.DoorStatus** --- to monitor the opening
    status of the refrigerator door

Some Refrigerators have the capability to be monitored and in case controlled
by a remote controller, in this case the following shared interface is
implemented:

  * **org.alljoyn.SmartSpaces.Operation.Control** --- to monitor and control

The operational states that the Refrigerator supports to be monitored are:

  * **0** --- **Off**
  * **2** --- **Working**

If the Refrigerator can only be monitored it doesn't support any operational
commands (empty array).

If it can be also controlled from remote, the operational commands that it
supports are:

  * **0** --- **Off**
  * **1** --- **On**

Moreover some Refrigerators have one or more of the following features:

  * the current temperature can be monitored
  * the temperature can be set from remote
  * they communicate alerts

in those cases following shared interface are implemented:

  * **org.alljoyn.SmartSpaces.Environment.CurrentTemperature** --- to monitor
    the temperature
  * **org.alljoyn.SmartSpaces.Environment.TargetTemperature** --- to set the
    temperature from remote
  * **org.alljoyn.SmartSpaces.Operation.Alerts** --- to communicate alerts

## Specification

|            |                               |
| ---------- | ----------------------------- |
| Version    | 1                             |
| Annotation | org.alljoyn.Bus.Secure = true |

### Properties

#### RapidCoolingMode

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | byte                                                    |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true |

The "Rapid Cooling" mode is a way of working of the refrigerator which speed up
the process of cooling the food by activating at maximum the reducing
temperature functionality of the appliance; it is selected by the user, usually
when a big quantity of food is inserted in the refrigerator cavity at the same
time.
Sometimes it is called in different way like "Super", "Turbo" or "Fast" ...

The property data type is an enumeration and its allowed value are listed below:

  * 0 --- **Off** --- Rapid Cooling is disabled
  * 1 --- **On** --- Rapid Cooling is enabled
  * 255 --- **Not Supported** --- Rapid Cooling is not supported by the
  specific appliance

### Methods

#### EnableRapidCoolingMode (mode)

Methods used to enable or disable the Rapid Cooling mode (see relative
**RapidCoolingMode** property).

Input arguments:

  * **mode** --- boolean --- the mode to be set: false to disable, true to
    enable

If the device can not execute the setting, an appropriate error shall be
returned.

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- if the Rapid Freezing mode is not
    supported by the appliance
  * org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- when the
    command is not accepted by the _producer_, because it is in a state
    which doesn't allow the execution
  * org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- when the remote
    control is disabled

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                     |
|---------------------------------------------------------------|---------------------------------------------------|
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not available                             |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                           |

## Examples

### Example 1

User wants to activate the "Rapid Cooling" mode in a Refrigerator that support
this feature while the appliance is working.

  * the controller invokes the **EnableRapidCoolingMode** method with the input
    parameter set to **true** , when **RapidCoolingMode** propriety is equal to
    **0x00**
  * the appliance accepts the setting
  * **RapidCoolingMode** propriety value turns to **0x01** and it is emitted to
    _consumer_

### Example 2

User wants to activate the "Rapid Cooling" mode in a Refrigerator while the
appliance is off.

  * the controller invokes the **EnableRapidCoolingMode** method with the input
    parameter set to **true**
  * the appliance does not accepts the setting, so **RapidCoolingMode**
    propriety does not change its value
  * error code is reported to _consumer_ using
    **org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState**

## References

  * The XML definition of the [Refrigerator interface](Refrigerator-v1.xml)
  * The definition of the [Alerts interface](/org.alljoyn.SmartSpaces.Operation/Alerts-v1)
  * The definition of the [DoorStatus interface](org.alljoyn.SmartSpaces.Operation/DoorStatus-v1)
  * The definition of the [Control interface](org.alljoyn.SmartSpaces/Operation/Control-v1)
  * The definition of the [CurrentTemperature interface](/org.alljoyn.SmartSpaces.Environment/CurrentTemperature-v1)
  * The definition of the [TargetTemperature interface](/org.alljoyn.SmartSpaces.Environment/TargetTemperature-v1)
