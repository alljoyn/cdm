# org.alljoyn.SmartSpaces.Operation.HvacFanMode version 1

## Theory of Operation

This interface controls the fan mode of  a  home appliance used to
alter the properties of air (primarily temperature and humidity) to more
comfortable conditions.
If the control is physically part of the device it is typically called an air
conditioner or heater.  If the control is remote from the appliance it is
typically called a thermostat.  A controller can recognize this device as an air
conditioner or thermostat by the DeviceDescription metadata field.
This interface is used instead of an "OnOff" control because of ambiguity in
what the On/Off on the interface would control, and because of the need for an
intermittent mode.


## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### Version

|            |                                                         |
| ---------- | ------------------------------------------------------- |
| Type       | uint16                                                  |
| Access     | read-only                                               |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const|

Interface version.

#### Mode

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It indicates the currently selected operational mode identifier.

  * **0** --- **Auto** : Fan runs as required by the appliance to support heating
and cooling operations.
  * **1** --- **Circulation** : Fan runs intermittently for a balance of energy
savings and air circulation
  * **2** --- **Continuous** : Fan runs continuously.

Errors raised by setting this property:

* org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- Returned
if value is not acceptable due to internal state.
* org.alljoyn.SmartSpaces.Operation.Error.RemoteControlDisabled --- Returned if 
remote control is disabled.   See the RemoteControl property in the
[RemoteControllability interface](RemoteControllability-v1) for further information.


#### SupportedModes

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16[]                                                       |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

An array of supported  modes. After getting the list of supported modes, a valid
one should be chosen out of the list.  It lists the values that the **Mode** can
assume.

The EmitsChangedSignal of this is property should be "const" once that feature
is implemented in core.


### Methods

No methods are implemented by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling feature
(`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error message.
The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Value not supported                                       |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control is disabled                         |

## References

* The XML definition of the [HvacFanMode interface](HvacFanMode-v1.xml)
* The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
* The [RemoteControllability interface](RemoteControllability-v1)

