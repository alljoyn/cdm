# org.alljoyn.SmartSpaces.Environment.MoistureOutputRate version 1

## Theory of Operation

This interface provides a capability to control and monitor the output rate of
moisture. Humidifier or air purifier can have this MoistureOutputRate interface
to adjust the moisture output rate for humidification. The moisture output rate
is about how fast a device reaches a given level of moisture. While the
[TargetHumidity](TargetHumidity-v1) interface is about a set-point
level of moisture or humidity to be reached, this interface provides an 
interaction capability about how fast a device reaches a given level of moisture. 
Some low-end humidifiers just have a capability to set the rate of moisture output
and don't care about the current and target humidity level. That's just left
as end-users' responsibility.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Properties

#### Version

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The interface version.

#### MoistureOutputRate

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It is a qualitative representation of the current rate of moisture output.
1 means the smallest rate of moisture output. MaxMoistureOutputRate means
the largest setting of moisture output rate.
MoistureOutputRate can be set to 0 when the AutoMode is on and the device
stops temporarily the moisture output to provide users with comfortable
surroundings.

Special reserved values listed below:
  * 0x00 --- **Off** --- Moisture output is turned off

For example, if there are 6 rates of moisture output then
MaxMoistureOutputRate = 5, and the rates will be {0, 1, 2, 3, 4, 5}.

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### MaxMoistureOutputRate

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

It indicates a maximum rate of moisture output.

#### AutoMode

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

If AutoMode is enabled, the device decides the moisture output rate for
providing comfortable surroundings automatically and the MoistureOutputRate
property shall be changed according to changing moisture output rate.
If AutoMode is disabled, the moisture output rate will remain at an appropriate
fixed moisture output rate determined by the device. (The fixed value of
moisture output rate can be a default value or the value when the AutoMode
is disabled. It depends on the device implementation.).

The property data type is an enumeration and its allowed value are listed below:

  * **0x00** --- **Off** : Auto mode is disabled
  * **0x01** --- **On** : Auto mode is enalbed
  * **0xFF** --- **Not Supported** : Auto mode is not supported by the device.

Errors raised when setting this property:

  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.FeatureNotAvailable --- Returend if a controller tries
  to set this property when the value is 0xFF.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

### Methods

No methods are implemented by this interface.

### Signals

No signals are emitted by this interface.

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.FeatureNotAvailable                         | Feature not supported                              |
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

### References

  * The XML definition of the [MoistureOutputRate interface](MoistureOutputRate-v1.xml)
  * The theory of operation of the HAE service framework [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [TargetHumidity interface](TargetHumidity-v1)
  * The definition of the [RemoteControllability interface](/org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)
