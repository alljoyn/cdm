DRAFT
## HVAC Theory of Operation version 1

This theory of operation explains the interaction of various interfaces to 
assemble an air conditioner or thermostat.


### Overview

HVAC is the abbreviation for Heating, Ventillation, and Air Conditioning, and is
typically used for installed devices.  It includes other air comfort devices as
well, for example humidifiers, de-humidifiers, and thermostats.  The HAE service 
framework does not differentiate between installed and portable versions of 
these products. Since the HAE service framework defines a common set of standard 
interfaces that work across multiple device types, this document illustrates how 
to use those interfaces for typical hvac applications.

#### Simple System

Consider a simple Air Conditioner that just offers the ability to cool air and 
to move air with it's fan.  Although this appliance also dehumidifies the air, 
it does not have controls in that area and does not need to implement any 
Humidity interfaces. It would implement the following interfaces:

CurrentTemperature
TargetTemperature
ClimateControlMode
HvacFanMode 

The minimum supported modes for ClimateControlMode are Off & Cool.
The minimum supported modes for HvacFanMode is Auto. 

This appliance might only support one temperature in the TargetTemperature for 
example {"cool":23} or {"setpoint":23}

##### Off
To turn the device off set:
ClimateControlMode = Off
HvacFanMode = Auto
You should see:
UpperActiveSetpoint = ""
LowerActiveSetpoint = "" (This will never change)

##### To Run just the Fan Continuously

Set HvacFanMode = Continuous
Nothing else should change

##### To Run in Cool
Set ClimateControlMode = Cool
You should see:
UpperActiveSetpoint = "setpoint"  The name is irrelevent as long as it appears
in the list of SupportedSetPoints in the TargetTemperatureInterface.

##### To Adjust the Setpoint
Call method SetTargetTemperature(["setpoint":25])


A simple thermostat that only controlled a furnace whould be implemented simarily.

#### Complex System

Consider a PTAC (Packaged Terminal Air Conditioner) that supports Heat/Cool/Auto
/AuxillaryHeat and a ResourceSavingsMode (Often called Home/Away, Day/Night,
Occupied/Unoccupied or EnergySavings).   It also supports the option to be used 
as a dehumidifier by supporting ContinuousDry. This device also supports two fan 
speeds and a circulate mode for the fan.

The interfaces are:

CurrentTemperature
ClimateControlMode
TargetTemperature
HvacFanMode
WindStrength
ResourceSaving

The TargetValues for this device could be very complex {"Morning cool":23, 
"Morning heat": 21, "Away Cool 25:, "Away Heat 19", "EmergencyHeat": 17,
"Evening Cool": 23, "Evening Heat":21 ...} 

Controller reads the thermostat Mode = "Auto" 
and
UpperActiveSetpoint = "Morning cool"
LowerActiveSetpoint = "Morning heat"

It wants to reduce the AC expenditure because of a preprogrammed rule of the 
consuners:

It could write ResourceSavingMode = True;
Reading Active setpoints might then return:
UpperActiveSetpoint = "Away cool"
LowerActiveSetpoint = "Away heat"

If more reduction was required, it could call:
SetTargetTemperature("Away cool", 26).


<More examples can be added>
<Still need ClimateControlMode for interoperability, and to destinguish between
an AC using humidity control and one that is off>




Wind Interactions.

There is an Auto in HvacFanModes and an Auto in WindStrength
This causes some confusion, but they are two different items.  One controls how
often the fan is on (Duty Cyle).  The other controls the speed of operation.
Consider 

|  HvacFanMode | WindStrength | WindStrength Auto | Behavior         |
|--------------|--------------|-------------------|------------------|
| Continuous   |   1          |   Off             | Fan Always on Low |
|--------------|--------------|-------------------|-------------------|
| Continuous   |   1          |   On              | Fan Always on Speed Varies |
|--------------|--------------|-------------------|-------------------|
| Continuous   |   2          |   Off             | Fan Always on High |
|--------------|--------------|-------------------|-------------------|
| Continuous   |   2          |   On              | Fan Always on Speed Varies |
|--------------|--------------|-------------------|------------------|
| Auto         |   1          |   Off             | Fan Intermittent on Low |
|--------------|--------------|-------------------|-------------------|
| Auto         |   1          |   On              | Fan Intermittent on Speed Varies |
|--------------|--------------|-------------------|-------------------|
| Auto         |   2          |   Off             | Fan Always on High |
|--------------|--------------|-------------------|-------------------|
| Auto         |   2          |   On              | Fan Always on Speed Varies |
|--------------|--------------|-------------------|-------------------|
