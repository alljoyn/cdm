# org.alljoyn.SmartSpaces.Environment.CurrentHumidity version 1

## Theory of Operation
This interface provides capability to represent current
relative humidity.

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

#### CurrentValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = true        |

The current relative humidity, expressed in percentage(0~100%). Relative humidity
is the ratio of the partial pressure of water vapor to the equilibrium vapor
pressure of water at the same temperature.

#### MaxValue

|            |                                                                |
|------------|----------------------------------------------------------------|
| Type       | byte                                                           |
| Access     | read-only                                                      |
| Annotation | org.freedesktop.DBus.Property.EmitsChangedSignal = false       |

Maximum value allowed for represented relative humidity.
If MaxValue is 100, CurrentValue is a percentage rate of Relative humidity. 
And if MaxValue is less than 100, CurrentValue is qualitative representation 
of current relative humidity level. 

### Methods

#### GetHumidityLevelsInfo(languageTag) -> (info)

Get added information about the humidity levels in string format. It is used to
communicate to controller the strings associated to the humidity level supported
values, so it can display them.

Input arguments:

  * **languageTag** --- string --- languageTag to be used in the output strings
  using IETF language tags specified by RFC 5646.

Output arguments:

  * **info** --- string[] --- the list of strings
  associated to the humidity levels, each element of the array refers
  to the level expressed by its index; the array can be:
    * empty: there are no string to communicate
    * list a string for each element from 0 to **MaxHumidityLevel**
    examples of output are: "Low", "Med", "High"

Errors raised by this method:

  * org.alljoyn.Error.FeatureNotAvailable --- Returend if the MaxValue   
  is 100.                                                                       
  * org.alljoyn.Error.LanguageNotSupported --- The language
  specified is not supported

### Signals

No signals are emitted by this interface.

### Interface Errors                                                            
                                                                                
The method calls in this interface use the AllJoyn error message handling       
feature (`ER_BUS_REPLY_IS_ERROR_MESSAGE`) to set the error name and error       
message. The table below lists the possible errors raised by this interface.    
                                                                                
|                          Error name             |                     Error                     |
|-------------------------------------------------|---------------------------------------------- |
| org.alljoyn.Error.FeatureNotAvailable           | Feature not supported                         |
| org.alljoyn.Error.LanguageNotSupported          | The language specified is not supported       |

## References

  * The XML definition of the [CurrentHumidity interface](CurrentHumidity-v1.xml)
