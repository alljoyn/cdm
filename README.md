CDM Service Framework
=====================

Welcome to the CDM Service Framework.

CDM Service Framework provides easy methods to implement CDM controllee and controller applications.

C++ Framework and Interfaces
==================

Folder Structure
----------------
Please note that the folder structure in 16.10 has changed since the 16.04 release
<pre>
cpp
+---framework
|   +---inc
|   |   \---alljoyn
|   |       \---cdm
|   |           +---common
|   |           +---controllee
|   |           +---controller
|   |           \---util
|   |
|   \---src
|       +---common
|       +---controllee
|       +---controller
|       \---util
|
+---interfaces
|   +---inc
|   |   \---interfaces
|   |       +---common
|   |       |   +---environment
|   |       |   +---input
|   |       |   +---operation
|   |       |   \---userinterfacesetting
|   |       |
|   |       +---controllee
|   |       |   +---environment
|   |       |   +---input
|   |       |   +---operation
|   |       |   \---userinterfacesetting
|   |       |
|   |       \---controller
|   |           +---environment
|   |           +---input
|   |           +---operation
|   |           \---userinterfacesetting
|   |
|   \---src
|       +---common
|       |   +---environment
|       |   +---input
|       |   +---operation
|       |   \---userinterfacesetting
|       |
|       +---controllee
|       |   +---environment
|       |   +---input
|       |   +---operation
|       |   \---userinterfacesetting
|       |
|       \---controller
|           +---environment
|           +---input
|           +---operation
|           \---userinterfacesetting
|
+---samples
|   +---certificates
|   +---DeviceEmulator
|   |   \---Model
|   |       +---environment
|   |       +---input
|   |       +---operation
|   |       \---userinterfacesetting
|   |
|   +---DeviceXML
|   +---LampDevice
|   +---Migration
|   |   +---16.04
|   |   |   +---BaseSample
|   |   |   |   \---Controllee
|   |   |   |
|   |   |   \---CookTopControllee
|   |   |
|   |   +---16.10
|   |       +---BaseSample
|   |       |   \---Controllee
|   |       |
|   |       \---CookTopControllee
|   |
|   +---QController
|   |   \---interfaces
|   |
|   +---SampleLauncher
|   |   \---cdm_os
|   |       +---bin
|   |       \---conf
|   |           +---cdm
|   |           \---cdm_tcl
|   |
|   +---Utils
|   \---WarpCoreInterface
|       +---common
|       \---controllee
|
\---unittest
    +---DUT
    |   +---environment
    |   +---input
    |   \---operation
    |
    \---ServiceFramework

generator
+---alljoyn_interfaces
\---templates
    +---interface_templates
    |   +---cdm
    |   |   +---cpp
    |   |   |   +---interfaces
    |   |   |   |   +---inc
    |   |   |   |   |   +---interfaces
    |   |   |   |   |       +---common
    |   |   |   |   |       |   \---{{InterfaceCategory}}
    |   |   |   |   |       +---controllee
    |   |   |   |   |       |   \---{{InterfaceCategory}}
    |   |   |   |   |       \---controller
    |   |   |   |   |           \---{{InterfaceCategory}}
    |   |   |   |   |
    |   |   |   |   \---src
    |   |   |   |       +---common
    |   |   |   |       |   \---{{InterfaceCategory}}
    |   |   |   |       +---controllee
    |   |   |   |       |   \---{{InterfaceCategory}}
    |   |   |   |       \---controller
    |   |   |   |           \---{{InterfaceCategory}}
    |   |   |   |
    |   |   |   \---samples
    |   |   |       +---DeviceEmulator
    |   |   |       |   \---Models
    |   |   |       |       \---{{InterfaceCategory}}
    |   |   |       |
    |   |   |       \---QController
    |   |   |           \---interfaces
    |   |   |
    |   |   +---ios
    |   |   |   \---CDMController
    |   |   |       \---cdm_controller
    |   |   |           \---view_controllers
    |   |   |               \---{{InterfaceCategory}}
    |   |   |
    |   |   \---java
    |   |       \---CdmController
    |   |           \---app
    |   |               \---src
    |   |                   \---main
    |   |                       \---java
    |   |                           \---org
    |   |                               \---alljoyn
    |   |                                   +---cdmcontroller
    |   |                                   |   \---fragment
    |   |                                   |       \---{{InterfaceCategory}}
    |   |                                   |
    |   |                                   \---smartspaces
    |   |                                       \---{{InterfaceCategory}}
    |   |
    |   \---cdm_tcl
    |       +---inc
    |       |   \---interfaces
    |       |       \---{{InterfaceCategory}}
    |       |
    |       +---samples
    |       |   \---DeviceEmulator
    |       |       \---Models
    |       |           \---{{InterfaceCategory}}
    |       |
    |       \---src
    |           \---interfaces
    |               \---{{InterfaceCategory}}
    |
    +---patches
    |   \---cpp
    |       +---interfaces
    |       |   \---src
    |       |       \---controllee
    |       |           +---environment
    |       |           \---operation
    |       |
    |       \---samples
    |           +---DeviceEmulator
    |           |   \---Models
    |           |       +---environment
    |           |       +---input
    |           |       \---operation
    |           |
    |           \---QController
    |               \---interfaces
    |
    \---patches_tcl
        +---samples
        |   \---DeviceEmulator
        |       \---Models
        |           +---environment
        |           +---input
        |           +---operation
        |           \---userinterfacesettings
        |
        \---src
            \---interfaces
                +---environment
                \---operation


</pre>

##### cpp/framework : The CDM framework libraries
   - The framework is segregated into common, controllee, controller and utility libraries
     * The controllee and controller libraries contain code directly related to their respective functionality
     * The common library is required by both controllee and controller libraries
     * The utility library contains utilities that wrap some boiler plate and make working with AllJoyn and CDM easier but it is not required
       - CdmAnnouncer can be given the devices about xml and then used to announce a device
       - CdmMsgCvt is a utility that converts to and from an Alljoyn MsgArg
       - CdmSecurity is a utility that can manage keys/certificates and be used to enable security
       - CdmSystem is used to manage AllJoyn and the router

##### cpp/interfaces : CDM interfaces libraries
   - The interfaces are segregated into common, controllee and controller libraries
     * The controlle and controller libraries contain the respective interface implementations
     * The common library is required by both controllee and controller libraries

##### cpp/samples : Samples that demonstrate the features and use of CDM
   * certificates contains some certficates used by the samples
   * DeviceEmulator - Refer to Device Emulator section in this document
   * DeviceXML contains device xml files used by the device emulator
   * LampDevice is sample that uses the CDM utilities and implements an HSV model and a Switch model
     - The HSV model composes of the Brightness and the Color interfaces
     - The Switch model composes of the OnOffStatus, OnControl and OffControl interfaces
   * Migration contains an example of the changes required to make a 16.04 sample work with 16.10
     - The 16.04 directory contains all the required code for the 16.04 cook top sample
     - The 16.10 contains all the modifications required to make it work with 16.10
     - 16.04_16.10.diff is a diff of the two directories to highlight the changes required
   * QController is a Qt controller implementation
   * SampleLauncher - Refer to the CDM OS section in this document
   * Utils contains utilities used by the samples
     - Command is a rework of the concept from 16.04 and listens for input from stdin. It simulates an interrupt handler
     - HAL simulates a Hardware Abstraction Layer. It is used in the sample model implementations read and write data to the "device's hardware"
   * WarpCoreInterface demonstrates how to build and integrate a custom interface starting from an xml file

##### generator : The CDM code generator
   * The generator is written in python and uses the jinja2 module
   * There are a number of custom annotations that are supported.
   * The alljoyn_intefraces contains modified CDM xml files. The modifications are the new annotations. All the new annotations are under org.twobulls.
   * Please refer to the README under the generator directory for instructions.

Building
--------
You can build CDM Service Framework using 'scons'.
Please refer to
<a name="AllJoyn build instructions" href="https:///allseenalliance.org/developers/develop/building">AllJoyn Build Instruction </a>
for more details on setting up your environment.

  * Folder structure
<pre>
root-source-dir
    +---core
    |   \---alljoyn
    |
    \---services
        +---base
        \---cdm
</pre>

### Build Linux
<pre>
$ cd $AJ_ROOT/core/alljoyn
$ scons OS=linux CPU={x86|x86_64} BINDINGS=cpp VARIANT={debug|release} CRYPTO=builtin
$ CORE_DISTDIR=$(pwd)/build/linux/{x86|x86_64}/{debug|release}/dist/
$ cd $AJ_ROOT/services/cdm/
$ scons OS=linux CPU={x86|x86_64} BINDINGS=cpp VARIANT={debug|release} CRYPTO=builtin ALLJOYN_DISTDIR=$CORE_DISTDIR
</pre>
#### Notes:
  libcap-dev may need to be installed

### Build windows
<pre>
> cd %AJ_ROOT%/core/alljoyn
> scons OS={win10|win7} CPU={x86|x86_64} BINDINGS=cpp VARIANT={debug|release} MSVC_VERSION={14.0|12.0}
> set CORE_DISTDIR=%cd%/build/{win10|win7}/{x86|x86_64}/{debug|release}/dist/
> cd %AJ_ROOT%/services/cdm/
> scons OS={win10|win7} CPU={x86|x86_64} BINDINGS=cpp VARIANT={debug|release} MSVC_VERSION={14.0|12.0} ALLJOYN_DISTDIR=%CORE_DISTDIR%
</pre>

### Build Darwin
<pre>
$ cd $AJ_ROOT/core/alljoyn
$ PLATFORM_NAME=macosx scons OS=darwin CPU={x86|x86_64} BINDINGS=cpp VARIANT={debug|release} SDKROOT=$(xcodebuild -sdk macosx -version Path)
$ CORE_DISTDIR=$(pwd)/build/darwin/{x86|x86_64}/{debug|release}/dist/
$ cd $AJ_ROOT/services/cdm/
$ PLATFORM_NAME=macosx scons OS=darwin CPU={x86|x86_64} BINDINGS=cpp VARIANT={debug|release} SDKROOT=$(xcodebuild -sdk macosx -version Path) ALLJOYN_DISTDIR=$CORE_DISTDIR
</pre>

### Build QController Sample
<pre>
$ cd cpp/samples/QController
$ cmake . -DCMAKE_BUILD_TYPE={Release|Debug} -DOS={darwin} -DCPU={x86|x86_64} -DCMAKE_PREFIX_PATH=<path_to_qt5_installation>
$ make
</pre>
#### Notes:
  The QController isn't built with the other samples as it has a dependency on Qt5 and needs to be build manually<br>
  The QController can be built for windows but it isn't actively supported at this stage.


### Build Output
<pre>
cdm/
    +---bin
    |   +---cdm_os
    |   |   +---bin
    |   |   \---conf
    |   |       +---cdm
    |   |       \---cdm_tcl
    |   |
    |   +---certificates
    |   \---DeviceXML
    |
    +---framework
    |   +---inc
    |       \---alljoyn
    |           \---cdm
    |               +---common
    |               +---controllee
    |               +---controller
    |               \---util
    |
    +---interfaces
    |   +---inc
    |       +---interfaces
    |           +---common
    |           |   +---environment
    |           |   +---input
    |           |   +---operation
    |           |   \---userinterfacesettings
    |           |
    |           +---controllee
    |           |   +---environment
    |           |   +---input
    |           |   +---operation
    |           |   \---userinterfacesettings
    |           |
    |           \---controller
    |               +---environment
    |               +---input
    |               +---operation
    |               \---userinterfacesettings
    \---lib
</pre>

  - output path : root-source-dir/services/cdm/build/$OS/$TARGET_CPU/$VARIANT/dist/cdm
  - bin : CookTopControllee, DeviceEmulator, LampDevice, launch.py and WarpCore
  - lib : liballjoyn_cdm.a, liballjoyn_cdm.so
  - framework : public header files for the framework
  - interfaces : public header files for the CDM interfaces

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

  * Make manual in the building step by adding DOCS=html to the scons command
<pre>
  PLATFORM_NAME=macosx scons OS=darwin CPU=x86_64 BINDINGS=cpp VARIANT=release SDKROOT=$(xcodebuild -sdk macosx -version Path) ALLJOYN_DISTDIR=$CORE_DISTDIR DOCS=html
</pre>

How to add a non CDM, custom interface
--------------------------------------

There are three parts to creating a new interface - the common, controllee and controller parts.

### Common part
The common part is used by both the controllee and controller parts to attach the interface to the AllJoyn bus attachment.

A class is created that inherits from CdmInterface, declared in framework/{inc}/common/CdmInterface.h
CdmInterface is an abstract base class and some methods require implementation.

This class is used to define static definitions relating to the interface, such as property names and its introspection xml.

### Controllee Side
The controllee implementation needs to create a class that inherits and implements two pure virtual classes:
 - CdmControlleeInterface, declared in framework/{inc}/controllee/CdmControlleeInterface.h
 - InterfaceReceiver, framework/{inc}/controllee/InterfaceReceiver.h

as well as the common class created above.

This class is responsible for receiving requests from a controller, unpacking the AllJoyn MsgArg, input validation and passing the request on to the model class (see next section).

##### Controllee Model
A model must also be implemented. The model is designed to implement the functionality that is exposed by the Alljoyn interface i.e.,
If a property is read only, then it has a Get{property_name}() method only and if it is readwrite then a Set{property_name}() method will be needed. The model is also responsible for implementing any methods declared in the interface xml.

The model is the integration point with the device and all hardware interaction occurs inside the model class.

Note: The CDM implementations of the interfaces actually do data validation of a SetProperty in the controllee implementation mentioned above and not in the model. The models assume the data is valid.

Model classes inherit from InterfaceControlleeModel, declared in framework/{inc}/controllee/InterfaceControlleeModel.h

### Controller Side
The controller implementation needs to create a class that inherits and implements:
 - InterfaceController, declared in framework/{inc}/controller/InterfaceController.h

as well as the common class created above.

##### Controller Listener
The listener is the reciprocal for the model on the controller side. It implements callbacks to the requests that are defined by the interface xml. It is the integration point for the UX/UI side of the controller.

The listener class inherits from InterfaceControllerListener, declared in framework/{inc}/controller/InterfaceControllerListener.h


#### Tutorial

The WarpCore sample provides a simple tutorial and demonstration of the above in the README located in that samples directory.

Device Emulator
---------------
Device emulator is a testing tool to help with the design of interfaces and UX experience by acting as a virtual device.
The emulator takes a device xml file as an input, this xml file contains the devices about data, a list of interfaces it should use and the default values for the properties of those interfaces.

Example device xml files can be found in the DeviceXML directory that exists along side the device emulator.

##### Running the emulator
<pre>
cd <root-source-dir>/services/cdm/build/{OS}/{CPU}/{VARIANT}/dist/cdm/bin
./DeviceEmulator some_devices.xml
</pre>

The emulator also takes three other optional arguments.

--state-dir <path>: This sets the directory that the simulated HAL (hardware abstraction layer) will read and write its property data to.

--certs-dir <path>: This is the location where security certificates are read from. This parameter includes the directory path as well as the certificate files prefix i.e., certificates/security, will used certificates/security.priv and certificates/security.pub

--emit-on-set : This parameter is required if you want the framework to emit signals when a property is set.

A call using all the arguments might look like
<pre>
cd <root-source-dir>/services/cdm/build/{OS}/{CPU}/{VARIANT}/dist/cdm/bin
./DeviceEmulator some_devices.xml --state-dir ../emulated_state --certs-dir certificates/security --emit-on-set
</pre>

CDM OS
------
CMD OS is a tool written in python that is used to launch samples for both CDM and CDM thin client under a predefined configuration.
The entry point is the launch.py found in the bin dir.

launch.py acts like a boot loader for the sample in that reads the sys.conf file under the cdm_os/conf directory to gather data about the system configuration, i.e., cdm or cdm tcl. launch.py also needs a device configuration.

The arguments for launch.py are (all arguments are optional):

--system : Is used to specify either cdm or cdm tcl. Defaults to cdm.
--device : Is used to choose the device.conf file. The file must exist under the conf/{system} directory.
--device-xml : Is used to specify the device xml file for the device emulator.
--list-devices : This will cause launch.py to list all the devices that are available for launch.

If --device arg is not specified, launch.py will prompt the user for a device under the system that was specified (cdm by default)

##### Running the device emulator via CDM OS
<pre>
cd <root-source-dir>/services/cdm/build/{OS}/{CPU}/{VARIANT}/dist/cdm/bin
./launch.py --device DeviceEmulator --device-xml air-conditioner.xml
</pre>

This will launch the device emulator as an air conditioner and allow the user to interact with the device's state via a *nix like shell.

#### CDM OS in more detail
When CDM OS launches, it launches the sample executable as a separate process and is able to communicate with it via stdin.

##### The sys.conf
The sys.conf file is a json file containing keys for all the system configurations.

Each system configuration needs the follow entries:

<pre>
  "bin_dir": "points to the location where all the sample binaries are installed",
  "mount_dir": "points to the base directory where all devices state directories will be written",
  "device_xml_dir": "points to the directory containing all the device xmls"
</pre>

##### A device.conf
The device.conf is a json configuration file used by CDM OS to launch the sample.
It has the required fields

<pre>
"bin": "The sample binary",
"args": ["arg1", "arg2"],
"devicexml": "a path to the device xml",
"boot_program": "the boot program to use",
"state_dir": "the directory name for the devices state to be stored",
"certs_dir": "path/prefix for the security certificates"
</pre>

Notes:
 - Any argument in the args list that starts with %% will act as a macro for any other defined field. e.g., %%devicexml will be replaced with the devicexml field
 - The devicexml field can be set to the value "from args" which means the device xml must be specified via the --devicexml argument from launch.py. If this is required but is absent, the user will be prompted.
 - The boot_program field is the name of the python program that CDM OS will boot into. The .py extension isn't needed.

##### A Boot Program
A boot program is a python module that implements the following:
 1. defines a class that provides a start method with no arguments other than self.
 2. provides a build function that takes two parameters, system and device_name. This function is expected to return the class mentioned above.

The class is typically initialised with the system and device_name parameters of the build function but it's not a requirement.

The boot programs are found in the cdm_os/bin directory.

##### The shell boot program
The shell boot program is used in the DeviceEmulator.conf and the LampDevice.conf. It enables the user to interact with the virtual device's properties in a way that is similar to a *nix shell, i.e., via a command prompt.

The commands available in the shell:
 - help : Entry point to the help system.
 - ls : lists the contents of the current directory.
 - cd : changes the current directory.
 - inspect : Displays the contents of a properties state file.
 - set : Writes new data into a properties state file.
 - reset : Can be used to reset a devices state back to it's 'factory' settings.


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


iOS Controller
==================

Folder Structure
----------------
<pre>
iOS
  \---CDMController
      +---cdm_controller
      |   +---en.lproj
      |   +---logic
      |   +---util
      |   \---view_controllers
      |       +---environment
      |       +---input
      |       +---operation
      |       +---table_view_cells
      |       \---userinterfacesettings
      |
      +---CDMController.xcodeproj
      +---Controller
      \---images
</pre>

 * iOS/CDMController/cdm_controller/view_controllers : contains the views for all the interfaces
 * iOS/CDMController/CDMController.xcodeproj : The xcode project
 * iOS/CDMController/Controller : The app entry point

Building
--------
Xcode 8.0 or above required

<pre>
$ cd $AJ_ROOT/core/alljoyn/
$ PLATFORM_NAME=iphoneos CONFIGURATION={Debug|Release} scons OS=darwin CPU=arm BINDINGS=cpp VARIANT={debug|release} CRYPTO=builtin SDKROOT=$(xcodebuild -sdk iphoneos -version Path)
$ cd alljoyn_objc/AllJoynFramework_iOS/
$ xcodebuild -project AllJoynFramework_iOS.xcodeproj/ -scheme AllJoynFramework_iOS -sdk iphoneos -configuration {Debug|Release}
$ cd $AJ_ROOT/services/cdm/
$ PLATFORM_NAME=iphoneos CONFIGURATION={Debug|Release} scons OS=darwin CPU={armv7,arm64} BINDINGS=cpp VARIANT={debug|release} CRYPTO=builtin SDKROOT=$(xcodebuild -sdk iphoneos -version Path)
$ cd ios/CDMController
$ xcodebuild -project CDMController.xcodeproj/ -sdk iphoneos -configuration {Debug|Release}
</pre>