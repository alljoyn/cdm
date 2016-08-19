HAE Service Framework
=====================

Welcome to the HAE Service Framework.

HAE Service Framework provides easy methods to implement HAE controllee and controller applications.


Folder Structure
----------------
<pre>
cpp
+---code_template
|   +---interface_template
|   +---vendor_defined_interface_template
|   \---xml
|       +---org.alljoyn.SmartSpaces.Environment
|       +---org.alljoyn.SmartSpaces.Operation
|       \---org.alljoyn.SmartSpaces.UserInterfaceSettings
+---inc
|   \---alljoyn
|       \---cdm
|           \---interfaces
|               +---environment
|               +---input
|               \---operation
+---samples
|   +---ACControllee
|   +---BaseSample
|   |   +---Controllee
|   |   +---Controller
|   |   \---VendorDefinedInterfaces
|   +---CookTopControllee
|   +---DeviceEmulator
|   |   \---config
|   +---IntegratedController
|   +---IntegratedControllee
|   +---LaundryControllee
|   +---RobotCleanerControllee
|   +---TimerSimulator
|   +---TvControllee
|   \---VDIControllee
+---src
|   \---interfaces
|       +---environment
|       +---input
|       \---operation
\---unittest
    +---DUT
    |   +---environment
    |   +---input
    |   \---operation
    \---ServiceFramework
</pre>

 * cpp/code_template : Generator of HAE interfaces skeleton codes
 * cpp/code_template/xml : Interospection XML files of HAE interfaces
 * cpp/inc/alljoyn/cdm : HAE common header files
 * cpp/inc/alljoyn/cdm/interfaces : HAE interface-related header files
 * cpp/samples/BaseSample : Base sample for making other device sample
 * cpp/samples/ACControllee :
   - Example of cdm device composed of Base sample controllee
   - Emulated virtual air conditioner sample. It has 11 interfaces. (OnOffStatus, OnControl,
     OffControl, ResourceSaving, ClimateControlMode, FanSpeedLevel, CurrentPower, EnergyUsage,
     CurrentTemperature, TargetTemperature, WindDirection)
 * cpp/samples/CookTopControllee :
   - Example of cdm device composed of Base sample controllee
   - Emulated virtual cook top sample. It has 3 interfaces. (HeatingZone, OvenCyclePhase, RapidMode)
 * cpp/samples/DeviceEmulator :
   - Device emulator (Refer to Device Emulator section in this document.)
 * cpp/samples/IntegratedControllee :
   - Integrated controllee based on Base sample controllee
   - Integrated controllee is designed to make it easier to add other interfaces.
 * cpp/samples/IntegratedController :
   - Integrated controller based on Base sample controller
   - Integrated controller is designed to make it easier to add other interfaces.
 * cpp/samples/LaundryControllee :
   - Example of cdm device composed of Base sample controllee
   - Emulated virtual laundry sample. It has 8 interfaces. (OnOffStatus, CycleControl, SoilLevel,
     SpinSpeedLevel, WaterLevel, DishWashingCyclePhase, LaundryCyclePhase, Timer)
 * cpp/samples/RobotCleanerControllee :
   - Example of cdm device composed of Base sample controllee
   - Emulated virtual robot cleaner sample. It has 5 interfaces. (OnOffStatus, BatteryStatus,
     RepeatMode, RobotCleaningCyclePhase, CurrentPower)
 * cpp/samples/TimerSimulator :
   - Timer simulator. It has CycleControl and Timer interfaces.
 * cpp/samples/TVControllee :
   - Example of cdm device composed of Base sample controllee
   - Emulated virtual TV sample. It has 4 interfaces. (Channel, AudioVolume, AudioVideoInput, Hid)


Building
--------
You can build HAE Service Framework using 'scons'.
Please refer to
<a name="AllJoyn build instructions" href="https:///allseenalliance.org/developers/develop/building">AllJoyn Build Instruction </a>
for more details on setting up your environment.

  * Folder structure
<pre>
root-source-dir
    +---core
    |   +---alljoyn
    |   \---ajtcl
    \---services
        +---base
        \---cdm
</pre>

  * Build
<pre>
cd root-source-dir/services/cdm
scons BINDINGS=cpp WS=off BT=off ICE=off
</pre>

  * Output
<pre>
cdm/
    +---bin
    +---inc
    |   \---alljoyn
    |       \---cdm
    |           \---interfaces
    |               +---environment
    |               +---input
    |               \---operation
    \---lib
</pre>

    - path : root-source-dir/services/cdm/build/$OS/$TARGET_CPU/debug/dist/cdm
    - bin : IntegratedController, TvControllee
    - lib : liballjoyn_cdm.a, liballjoyn_cdm.so
    - inc : header files

Unit Tests
-------
  * Build unit tests
To build the unit tests add a GTEST_DIR='<your local path>/GTEST/googletest'
parameter to the scons command line.

tests can be found and run from:
<root-source-dir>/services/cdm/build/{OS}/{CPU}/{VARIANT}/test/cdm/bin

Doxygen
-------
  * Make manual
<pre>
cd root-source-dir/services/cdm/cpp/docs
doxygen Doxygen_html
</pre>

  * Make manual in the building step
<pre>
cd root-source-dir/services/cdm
scons BINDINGS=cpp WS=off BT=off ICE=off DOCS=html
</pre>

How to add new interface
------------------------
  1. Generate the skeleton codes using make_interface.py script.
  2. Fill the codes for properties, methods and signals in all files generated.

  * Create skeleton codes for new interface
<pre>
cd root-source-dir/services/cdm/cpp/code_template
python make_interface.py -n InterfaceName -c CategoryName
(InterfaceName and CategoryName are case sensitive.)
[example]
python make_interface.py -n TargetTemperature -c Environment
Created: ../inc/alljoyn/cdm/interfaces/environment/TargetTemperatureInterface.h
Created: ../inc/alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllee.h
Created: ../inc/alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControlleeListener.h
Created: ../inc/alljoyn/cdm/interfaces/environment/TargetTemperatureIntfController.h
Created: ../inc/alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllerListener.h
Created: ../src/interfaces/environment/TargetTemperatureInterface.cc
Created: ../src/interfaces/environment/TargetTemperatureIntfControlleeImpl.h
Created: ../src/interfaces/environment/TargetTemperatureIntfControlleeImpl.cc
Created: ../src/interfaces/environment/TargetTemperatureIntfControllerImpl.h
Created: ../src/interfaces/environment/TargetTemperatureIntfControllerImpl.cc
</pre>

  * Delete files related new interface
<pre>
cd root-source-dir/services/cdm/cpp/code_template
python make_interface.py -n InterfaceName -c Category -d
</pre>

How to add vendor defined interface
------------------------------------
  1. Generate the skeleton codes using make_interface.py script.
  2. Copy all files to your application folder
  3. Fill the codes for properties, methods and signals in all files generated.

  * Create skeleton codes for vendor defined interface
<pre>
cd root-source-dir/services/cdm/cpp/code_template
python make_interface.py -n InterfaceName -v
(InterfaceName is case sensitive.)
[example]
python make_interface.py -n Test -v
Created: ./vendor_defined/TestInterface.h
Created: ./vendor_defined/TestIntfControllee.h
Created: ./vendor_defined/TestIntfControlleeListener.h
Created: ./vendor_defined/TestIntfController.h
Created: ./vendor_defined/TestIntfControllerListener.h
Created: ./vendor_defined/TestInterface.cc
Created: ./vendor_defined/TestIntfControlleeImpl.h
Created: ./vendor_defined/TestIntfControlleeImpl.cc
Created: ./vendor_defined/TestIntfControllerImpl.h
Created: ./vendor_defined/TestIntfControllerImpl.cc
</pre>

  * Delete files related vendor defined interface
<pre>
cd root-source-dir/services/cdm/cpp/code_template
python make_interface.py -n InterfaceName -v -d
</pre>

Device Emulator
---------------
Device emulator is an emulator for the HAE Service Framework based devices.
You can launch the virtual device using the configuration XML file.

  * Run emulator
<pre>
cd <root-source-dir>/services/cdm/build/{OS}/{CPU}/{VARIANT}/dist/cdm/bin
./DeviceEmulator config.xml
</pre>

 * Sample config.xml for air conditioner
<pre>
&ltDeviceEmulator&gt
    &ltAboutData&gt
        &ltAppId&gt000102030405060708090A0B0C0D0E0C&lt/AppId&gt
        &ltDefaultLanguage&gten&lt/DefaultLanguage&gt
        &ltDeviceName&gtMy Device Name&lt/DeviceName&gt
        &ltDeviceName lang = 'es'&gtNombre de mi dispositivo&lt/DeviceName&gt
        &ltDeviceId&gtbaddeviceid&lt/DeviceId&gt
        &ltAppName&gtMy Application Name&lt/AppName&gt
        &ltAppName lang = 'es'&gtMi Nombre de la aplicación&lt/AppName&gt
        &ltManufacturer&gtCompany&lt/Manufacturer&gt
        &ltManufacturer lang = 'es'&gtEmpresa&lt/Manufacturer&gt
        &ltModelNumber&gtWxfy388i&lt/ModelNumber&gt
        &ltDescription&gtA detailed description provided by the application.&lt/Description&gt
        &ltDescription lang = 'es'&gtUna descripción detallada proporcionada por la aplicación.&lt/Description&gt
        &ltDateOfManufacture&gt2014-01-08&lt/DateOfManufacture&gt
        &ltSoftwareVersion&gt1.0.0&lt/SoftwareVersion&gt
        &ltHardwareVersion&gt1.0.0&lt/HardwareVersion&gt
        &ltSupportUrl&gtwww.example.com&lt/SupportUrl&gt
        &ltUserDefinedTag&gtCan only accept strings anything other than strings must be done using the AboutData Class SetField method&lt/UserDefinedTag&gt
        &ltUserDefinedTag lang='es'&gtSólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField&lt/UserDefinedTag&gt
        &ltCountryOfProduction&gtRoom1&lt/CountryOfProduction&gt
        &ltLocation&gtRoom1&lt/Location&gt
        &ltProductBrand&gtRoom1&lt/ProductBrand&gt
        &ltLocation&gtupstairs bedroom&lt/Location&gt
        &ltLocation lang='es'&gthabitación del segundo piso&lt/Location&gt
        &ltDeviceTypeDescription&gt
            &ltTypeDescription&gt
                &ltdevice_type&gt5&lt/device_type&gt
                &ltobject_path&gt/Cdm/AirConditioner&lt/object_path&gt
            &lt/TypeDescription&gt
        &lt/DeviceTypeDescription&gt
    &lt/AboutData&gt
    &ltInterfaceList&gt
        &ltObject path='/Cdm/AirConditioner'&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Environment.TargetTemperature'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Environment.CurrentTemperature'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Environment.WindDirection'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Operation.OnControl'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Operation.OffControl'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Operation.OnOffStatus'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Operation.FanSpeedLevel'/&gt
            &ltInterface name='org.alljoyn.SmartSpaces.Operation.ClimateControlMode'/&gt
        &lt/Object&gt
    &lt/InterfaceList&gt
&lt/DeviceEmulator&gt
</pre>

Android Controller
==================

Folder Structure
----------------
<pre>
java
   \---CdmController
       +---app
       |   +---libs
       |   \---src
       \---gradle
</pre>

 * java/CdmController/app/libs: alljoyn.jar, alljoyn_about.jar, liballjoyn_java.so
 * java/CdmController/app/src: source files
 * java/CdmController/gradle: build script for Android Studio

Building
--------
 * Open project folder(/java/CdmController/) in the Android Studio
 * If you are using the Android Studio 2.0, you should change your config of the Android Studio. (http://tools.android.com/tech-docs/instant-run)
   1. Open the Settings or Preferences dialog.
   2. Navigate to Build, Execution, Deployment > Instant Run.
   3. Uncheck the box next to Restart activity on code changes.
   4. Uncheck the box next to Enable Instant Run to ~~~
   5. Run > Clean and Rerun 'app'

