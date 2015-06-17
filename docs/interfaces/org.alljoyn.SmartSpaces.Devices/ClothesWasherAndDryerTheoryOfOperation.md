# Theory of Operation

This document describes the common theory of operation for HAE project
interfaces related to the clothes washing and drying area/cluster.
These appliances are:

  * Clothes Dryers
  * Clothes Washers
  * Clothes Washer-Dryers
  * composed appliances which implements Clothes Washers and Clothes Dryers as
    sub-units

In a Clothes Washer-Dryer the washing and drying processes are made using the
same cavity at different times.
In composed appliances the processes are made in different cavities.

So the information of this documents are valid for the following interfaces:

  * **org.alljoyn.SmartSpaces.Devices.ClothesDryer** --- to represent Clothes
    Dryer appliances and sub-units
  * **org.alljoyn.SmartSpaces.Devices.ClothesWasher** --- to represent Clothes
    Washer and sub-units
  * **org.alljoyn.SmartSpaces.Devices.ClothesWasherDryer** --- to represent
    Clothes Washer-Dryers

The above interfaces provide a set of properties and methods, which let the
 _producer_ (i.e. the appliance) to be monitored and controlled by a _consumer_
(usually it is a remote application).

Clothes Washers and Clothes Dryers executes their specific operations using
cycles. These cycles are made of following phases:

  * **Pre-washing** --- the appliance is executing a preliminary wash, to remove
    some particular dirt (not used by Clothes Dryers)
  * **Washing** --- the appliance is executing the main wash (not used by
    Clothes Dryers)
  * **Rinsing** --- the appliance is rinsing the clothes to remove soap (not
    used by Clothes Dryers)
  * **Spinning** --- the appliance is spinning to partially dry the clothes (not
    used by Clothes Dryers)
  * **Steam** --- the appliance is treating the clothes with steam
  * **Drying** --- the appliance is drying the clothes (not used by Clothes
    Washers)
  * **Cooling** --- the appliance is reducing the internal temperature (not used
    by Clothes Washers)
  * **AntiCreasing** --- the appliance is drying executing some operation to
    prevent the formation of creases in the clothes (not used by Clothes
    Washers)

Specific appliance cycles can execute just a sub-set of above phases.

## References

  * The definition of the [ClothesDryer interface](ClothesDryer-v1)
  * The definition of the [ClothesWasher interface](ClothesWasher-v1)
  * The definition of the [ClothesWasherDryer interface](ClothesWasherDryer-v1)
  