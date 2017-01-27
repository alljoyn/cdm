## HVAC Theory of Operation version 1

This theory of operation explains the interaction of various interfaces to 
assemble an air conditioner or thermostat.


### Overview

HVAC is the abbreviation for Heating, Ventilation, and Air Conditioning, and is
typically used for installed devices.  It includes other air comfort devices as
well, for example humidifiers, de-humidifiers, and thermostats.  The CDM service 
framework does not differentiate between installed and portable versions of 
these products. Since the CDM service framework defines a common set of standard 
interfaces that works across multiple device types, this document illustrates how 
to use those interfaces for typical HVAC applications.

### Simple System

Consider a simple Air Conditioner that just offers the ability to cool air and 
to move air with its fan.  Although this appliance also dehumidifies the air, 
it does not have controls in that area and does not need to implement any 
Humidity interfaces. It would implement the following interfaces:

- CurrentTemperature
- TargetTemperature
- ClimateControlMode
- HvacFanMode 

The minimum supported modes for ClimateControlMode are Off & Cool.

The minimum supported modes for HvacFanMode is Auto. 

This appliance only supports one TargetTemperature temperature interface, and it 
can be placed on the root node.

##### Off
To turn the device off set:
- ClimateControlMode = Off
- HvacFanMode = Auto

##### To Run just the Fan Continuously
Set HvacFanMode = Continuous

##### To Run in Cool
Set:
- ClimateControlMode = Cool
- HvacFanMode = Auto or Continuous

##### To Adjust the Setpoint
Write Property TargetValue = 25

A simple thermostat that only controlled a furnace would be implemented similary.

### Complex System

Consider a PTAC (Packaged Terminal Air Conditioner) that supports Heat/Cool/Auto
/AuxillaryHeat/Dry/ContinuosDry and a ResourceSavingsMode (Often called 
Home/Away, Day/Night, Occupied/Unoccupied or EnergySavings).   It also supports 
the option to be used as a dehumidifier by supporting ContinuousDry. This device 
also supports two fan speeds and a circulate mode for the fan.

The interfaces are:

- CurrentTemperature
- ClimateControlMode
- TargetTemperature (x2)
- HvacFanMode
- FanSpeedLevel
- ResourceSaving
- TargetHumidity

To disambiguate the two TargetTemperature interfaces each must be placed on 
their own endpoint.  Based on current CDM rules of max two levels of path,
no children are allowed  for /Heat and /Cool.  Any additional interfaces should 
either be on /root or its own child /root/feature unless they are directly 
related to the heating or cooling targets.
- /root/Cool
- /root/Heat

###  Interactions of Temperature and other controls
In general if a thermostat supports the ability to program more than two 
temperatures then the TargetTemperatures on the /root/Heat/ and /root/Cool/
endpoints should be interpreted as a temporary hold.  It will remain in effect 
as long as the temperature it replaced would have remained in effect.

#### Schedules
At the present time AllJoyn does not support thermostat schedules.  If a 
thermostat supports a schedule through either a manufacturer app or its user
interface.

Example:  At 0700 the current heating target is 23 degrees, and at 0800 the 
schedule will change to 21 degrees.  Controller writes TargetValue = 22 to the 
TargetTemperature interface on the /root/Heat.  The thermostat will adjust its 
setpoint and the TargetValue to 22.  At 0800 the thermostat will again adjust its
setpoint and the TargetValue to 21.  If a controller would like the temperature
set to 22, it must write to the TargetValue again.

#### Modes 
Mode is loosely coupled to TargetTemperature, changing mode should not normally
change the TargetTemperature.  Writing to the /root/Cool target temperature
while the ClimateControlMode is Heat is allowed, and would have an effect if the 
mode were to change in the future.
The exception is if a Mode has a unique TargetValue associated with that mode in 
the manufacturer app or local UI.

Example:
Consider the above device that does not support a schedule.  In its local 
memory it supports 4 temperatures, with the following values Heat(21), Cool(25),
AwayHeat(19), AwayCool(26).  The away modes are triggered by the 
ResourceSavingsMode.  It also has an EmergencyHeatMode that disables the heat 
pump but does not have its own temperature. At start the ClimateControlMode=Off.  


In the table headings below:
- Heat TV  means the /root/Heat TargetTemperature Interface TargetValue
- Cool TV  means the /root/Cool TargetTemperature Interface TargetValue

| Action                    | Heat TV | Cool TV | notes                        |
|---------------------------|---------|---------|------------------------------|
| Start                     |  21     | 25      | TVs are not active           |
| ClimateControlMode = Heat |  21     | 25      | Heat is Active; Cool is not  |
| /root/Heat/Target = 23    |  23     | 25      | Heat is Active; Cool is not  |
| ClimateControlMode = Cool |  23     | 25      | Cool is Active; Heat is not  |
| ResourceSavingMode = True |  19     | 26      | Heat is Active; Cool is not  |
| ClimateControlMode = Auto |  19     | 26      | Both Active                  |
| /root/Cool/Target = 27    |  19     | 27      | Both Active                  |
| ResourceSavingMode = False|  23     | 25      | Both Active                  |
| ClimateControlMode = Dry  |  19     | 26      | Neither Active               |


### Wind Interactions.

There is an Auto in HvacFanModes and an Auto in FanSpeedLevel
This causes some confusion, but they are two different items.  One controls how
often the fan is on (Duty Cyle).  The other controls the speed of operation.
Consider 

|  HvacFanMode | FanSpeedLevel | FanSpeedLevel Auto | Behavior                         |
|--------------|---------------|--------------------|----------------------------------|
| Continuous   |   1           |   Off              | Fan Always on Low                |
| Continuous   |   1           |   On               | Fan Always on Speed Varies       |
| Continuous   |   2           |   Off              | Fan Always on High               |
| Continuous   |   2           |   On               | Fan Always on Speed Varies       |
| Auto         |   1           |   Off              | Fan Intermittent on Low Speed    |
| Auto         |   1           |   On               | Fan Intermittent on Speed Varies |
| Auto         |   2           |   Off              | Fan Intermittent on High Speed   |
| Auto         |   2           |   On               | Fan Intermittent on Speed Varies |
