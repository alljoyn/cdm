# org.alljoyn.SmartSpaces.Operation.Mouse version 1

## Theory of Operation
This interface provides capabilities to control and monitor mouse movement
and action.

## Specification

|            |                                                                |
|------------|----------------------------------------------------------------|
| Version    | 1                                                              |
| Annotation | org.alljoyn.Bus.Secure = true                                  |

### Methods

#### MoveMouse (relativeX, relativeY)

|            |                                                                |
|------------|----------------------------------------------------------------|
| Annotation | org.freedesktop.DBus.Method.NoReply = true                     |

Move a mouse pointer on a controlle screen. The reply is not needed. The mouse
sensitiviy depends on both a mouse's DPI (dots per linear inch) and the controllee's
screen resolution. Dots per inch (DPI) is a measurement of how sensitive a mouse
is. The higher the mouse’s DPI, the farther the mouse pointer will move on the
controllee screen, when a user moves the mouse. The lower the controllee's
screen resolution, the farther the mouse pointer will move on the screen with
the same displacement values. The mouse sensitivity can be controlled by scaling
of the displcement (X,Y) values at the end points. Thus, it is recommended that
both the controller and the conrollee have a user interface setting for mouse
sensitivity control.

Input arguments:
  * **relativeX** --- int16 --- Displacement value for the X coordinate. From
  the current mouse pointer on the screen, a negative value denotes the movement
  to the left and a positive value denotes the movement to the right.
  * **relativeY** --- int16 --- Displacement value for the Y coordinate. From
  the current mouse pointer on the screen, a negative value denotes an upward
  movement and a positive value denotes a downward movement.

Output arguments: None.

#### PressMouseButton (button)

Press the mouse button. The arguments indicate left button or right button.

Input arguments:
  * **button** --- byte --- The enumeration below lists button type.
    * Left : 0
    * Right : 1

Output arguments: None.

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

### ReleaseMouseButton (button)

Release the mouse button. The parameter indicates left button or right button.

Input arguments:
  * **button** --- byte --- The enumeration below lists button type.
    * Left : 0
    * Right : 1

Output arguments: None.

Errors raised by this method:
  * org.alljoyn.Error.InvalidValue --- Returned if value is not valid.
  * org.alljoyn.Error.SmartSpaces.NotAcceptableDueToInternalState --- Returned
  if value is not acceptable due to internal state.
  * org.alljoyn.Error.SmartSpaces.RemoteControlDisabled --- Returned if remote
  control is disabled.

#### WheelMouse (scroll)

|            |                                                                |
|------------|----------------------------------------------------------------|
| Annotation | org.freedesktop.DBus.Method.NoReply = true                     |

Wheel mouse in specific direction. The reply is not needed.

Input arguments:
  * **scroll** --- byte --- The enumeration below lists scroll direction.
    * Scroll Up : 0
    * Scroll Down : 1

Output arguments: None.

### Signals

No signals are emitted by this interface.

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

  * The XML definition of the [Mouse interface](Mouse-v1.xml)
