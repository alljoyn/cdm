# org.alljoyn.SmartSpaces.UserInterfaceSettings version 1

## Theory of Operation


The interfaces in this namespace provides access to the setting choices 
appliances often allow consumers to select on the User Interface.  It is 
intended to be part of a larger object that has other features.  Typically 
implemented at the top of the tree as part of the device object.  It is expected 
that most devices will only implement one of these interfaces.

The _producer_ has a user interface wishes to expose the settings to a remote 
object.  If so the supported settings attribute provides
a list of the possible changes.  If the supported settings array is empty then
the device does not allow remote changes, and the associated SetDisplay Method 
will return the related error.

The _consumer_ is an application that is interested in the user interface 
settings.  It may use this information to configure its displays to match the
device, or as a configuration tool to set the device displays.  See some example
use cases in the Examples section.


### Properties

#### DisplayXXXXX

Typically an interface will support a read-write notifiable attribute that 
indicates the current settings.  SupportedDisplayXXXXXs should be read prior to
attempting to write.

Errors raised by writing to this interface:

* org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState --- Value is not 
acceptable due to internal state.  Caller should try again later. This 
potentially could be raised if local user was interacting with the UI.

* org.alljoyn.SmartSpaces.Error.RemoteControlDisabled --- remote control is 
disabled.   See the [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)
* org.alljoyn.Hae.Error.InvalidValue --- Value is not supported.  Caller should 
read SupportedDisplayXXXXXSettings for acceptable values. 
(SetDisplayLanguage uses org.alljoyn.Error.LanguageNotSupported )

#### SupportedDisplayXXXXXs

Typically an interface will support a "const" attribute that indicates the 
available settings.  Currently those interfaces are listed as notifiable until 
the const feature is implemented.  If list has only one item then the display 
cannot be changed.  Attempting to change to an unsupported value will return an 
error.  If list is empty then Interface should not be supported.

### Methods

See individual interface documentation.

### Signals

See individual interface documentation.

### Named Types

See individual interface documentation.

### Interface Errors

See individual interface documentation.


## Examples

Example use cases:

### Display temperature in the same units as on the device.
For example a consumer in the United States chooses to have thermostat display
in degrees Fahrenheit, but they cook with old family recipes and have the oven
set to deg Celcius.

### Help the consumer set the language.
The device defaults to a Japanese user interface.  The UI has a change language
feature, but the consumer cannot find it.  The mobile application knows the 
consumers preference is Spanish. It can interrogate the device over AllJoyn,
determine if Spanish is supported, and offer a choice to the consumer to change
the language to one they can read.

### Configure the timeout on a lock keypad backlight.  
A lock has a keypad that lights up when a key is touched, and then stays 
illuminated for a configurable length of time.  The lock could choose to expose 
a control to not have a backlight, or to control the backlight's duration 
through a BacklightDisplay interface.  (This example shows how interface can be 
generalized.  As of initial release of this interface neither the backlight nor 
lock are supported in an org.alljoyn.SmartSpaces interface. )

## References

* The [Remote Controllability Interface.](../org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1)