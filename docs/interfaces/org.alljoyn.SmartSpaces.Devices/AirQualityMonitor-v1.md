# org.alljoyn.SmartSpaces.Devices.AirQualityMonitor version 1

## Theory of Operation

Air Quality Monitor is a type of home appliances that has the capability of
monitoring pollutants in the air.This interface is an abstract type so that
it covers any home appliance who has the function of getting the quantitative
load or qualitative level of any air pollutants.

The followings are minimum required shared interfaces for an Air Quality
Monitor.
  * **org.alljoyn.SmartSpaces.Operation.OperationControl** --- for start/stop
operation

There are many kinds of air pollutants that can be monitored, such as PM2.5,
PM10,VOC,CH2O,CO and CO2. Each specific Air Quality Monitor can monitor
certain or all air pollutants.
Considering the specific function of Air Quality Monitor, the following shared
interfaces may be implemented:
  * **org.alljoyn.SmartSpaces.Environment.CurrentAirQuarityLevel**
  * **org.alljoyn.SmartSpaces.Environment.CurrentCo2Concentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentCoConcentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentPm2_5Concentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentPm10Concentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentCh2oConcentration**
  * **org.alljoyn.SmartSpaces.Environment.CurrentVocConcentration**

## Specification

|               |                                                       |
|---------------|-------------------------------------------------------|
| Version       | 1                                                     |
| Annotation    | org.alljoyn.Bus.Secure = true                         |

## References

  * [The XML definition of AirQualityMonitor]
    (AirQualityMonitor-v1.xml)
  * [The definition of OperationalControl]
    (/org.alljoyn.SmartSpaces.Operation/OperationControl-v1)
  * [The definition of CurrentAirQualityLevel]
    (/org.alljoyn.SmartSpaces.Environment/CurrentAirQuarityLevel-v1)
  * [The definition of CurrentPm2_5Concentration]
    (/org.alljoyn.SmartSpaces.Environment/CurrentPm2_5Concentration-v1)
  * [The definition of CurrentPm10Concentration]
    (/org.alljoyn.SmartSpaces.Environment/CurrentPm10Concentration-v1)
  * [The definition of CurrentVocConcentration]
    (/org.alljoyn.SmartSpaces.Environment/CurrentVocConcentration-v1)
  * [The definition of CurrentCh2oConcentration]
    (/org.alljoyn.SmartSpaces.Environment/CurrentCh2oConcentration-v1)
  * [The definition of CurrentCoConcentration]
    (/org.alljoyn.SmartSpaces.Environment/CurrentCoConcentration-v1)
  * [The definition of CurrentCo2Concentration]
    (/org.alljoyn.SmartSpaces.Environment/CurrentCo2Concentration-v1)