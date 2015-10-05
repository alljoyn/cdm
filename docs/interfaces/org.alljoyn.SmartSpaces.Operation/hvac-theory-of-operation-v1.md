DRAFT

This theory of operation explains the interaction of various interfaces to 
assemble an air conditioner or thermostat.


AC picture.


The AC Will need to implement several interfaces, they can all co-exist on the 
same bus object:

CurrentTemperature
TargetTemperature
ClmateControlMode
HvacFanMode   (optional - required to have a fan mode other than auto).
            Votes on if this can be optional?
WindStrength (optional -only required if multiple fan speeds available).

The minimum supported modes for ClimateControlMode are Off & Cool.
The minimum supported modes for HvacFanMode is Auto.  Auto support only is 
assumed if interface is not implemented.

The TargetValues for this device would be very simple {"cool":23} 
or {"setpoint":22.5}

UpperActiveSetpoint = "setpoint" or "cool" or ""
LowerActiveSetpoint = ""



Consider a more complex device, the structure is essentially the same except 
with more interfaces.


Thermostat Picture 2




Consider a PTAC (Packaged Terminal Air Conditioner) that supports Heat/Cool/Auto
/AuxillaryHeat and a ResourceSavingsMode (Often called Home/Away, Day/Night,
Occupied/Unoccupied or EnergySavings).  This device also supports two fan 
speeds and a circulate mode for the fan.

The interfaces are:

CurrentTemperature
ClmateControlMode
TargetTemperature
HvacFanMode
WindStrength
EnergySavingsMode
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
an AC using humidity control nd one that is off>




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
