# org.alljoyn.SmartSpaces.Operation.Channel version 1

## Theory of Operation
This interface provides capabilities to set and get the channel of a device
that has a channel list.

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
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = const       |

Interface version.

#### ChannelId

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | string                                                         |
| Access     | read-write                                                     |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Current channel ID.

Errors raised when setting this property:
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### TotalNumberOfChannels

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | uint16                                                         |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

Total number of scanned channels.

### Methods

#### GetChannelList (startingRecord, numRecords) -> (listOfChannelInfoRecords)

Retrieve the list of channels supported by a device which has channel
functionality such as TV. This operation allows to get the number of
ChannelInfoRecords from the starting record number.

Input arguments:
  * **startingRecord** --- uint16 --- Build the list from this record number.
    If the starting Record is out of range, then an error shall be returned.
    The startingRecord starts from 0.
  * **numRecords** --- uint16 --- Only generate at most this many records. If
  the available number of channels is less than numRecords, then the controllee
  device shall return the available channel list without returning an error.

Output arguments:
  * **listOfChannelInfoRecords** --- ChannelInfoRecord[] --- List of channel
  information records.

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.

### Signals

#### ChannelListChanged
|              |             |
|--------------|-------------|
| Signal Type  | sessioncast |

The channel list has changed.

Output arguments: None.

### Named Types

#### struct ChannelInfoRecord

  * **channelID** --- string --- The unique channel ID.
  * **channelNumber** --- string --- The display channel number in the device.
    ex) 11-2, 7, 9-1
  * **channelName** --- string --- the channel short name which is user friendly
  name. ex) CNN, NHK, KBS

### Interface Errors

The method calls in this interface use the AllJoyn error message handling
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error
message. The table below lists the possible errors raised by this interface.

| Error name                                                    | Error message                                      |
|---------------------------------------------------------------|----------------------------------------------------|
| org.alljoyn.Error.InvalidValue                                | Invalid value                                      |
| org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState | The value is not acceptable due to internal state  |
| org.alljoyn.SmartSpaces.Error.RemoteControlDisabled           | Remote control disabled                            |

## References

  * The XML definition of the [Channel interface](Channel-v1.xml)
  * The Common Device Model [Theory of Operation](/org.alljoyn.SmartSpaces/theory-of-operation-v1)
  * The definition of the [RemoteControllability interface](RemoteControllability-v1)



