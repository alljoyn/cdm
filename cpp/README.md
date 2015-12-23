HAE Service Framework
=====================

Welcom to the HAE Service Framework.

HAE Service Framework provides easy methods to implement HAE controllee and controller applications.


Folder Structure
----------------
<pre>
+---code_template
|   +---interface_template
|   +---vendor_defined_interface_template
|   \---xml
|       +---org.alljoyn.SmartSpaces.Environment
|       +---org.alljoyn.SmartSpaces.Operation
|       \---org.alljoyn.SmartSpaces.UserInterfaceSettings
+---inc
|   \---alljoyn
|       \---hae
|           \---interfaces
|               +---environment
|               +---input
|               \---operation
+---samples
|   +---BaseSample
|   |   +---Controllee
|   |   +---Controller
|   |   \---VendorDefinedInterfaces
|   +---IntegratedController
|   +---TvControllee
|   \---VDIControllee
\---src
    \---interfaces
        +---environment
        +---input
        \---operation
</pre>

 * cpp/code_template : Generator of HAE interfaces skeleton codes
 * cpp/code_template/xml : Interospection XML files of HAE interfaces
 * cpp/inc/alljoyn/hae : HAE common header files
 * cpp/inc/alljoyn/hae/interfaces : HAE interface-related header files
 * cpp/samples/BaseSample : Base sample for making other device sample
 * cpp/samples/IntegratedController :
   - Integrated controller based on BaseSample controller
   - The current version supports only TV-related interfaces. (Channel, AudioVolume, AudioVideoInput, Hid)
   - Intergrated controller is designed to make it easier to add other interfaces.
 * cpp/samples/TVControllee :
   - Example of hae device composed of Base sample controllee
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
        \---hae
</pre>

  * Build
<pre>
cd root-source-dir/services/hae
scons BINDINGS=cpp WS=off BT=off ICE=off
</pre>

  * Output
<pre>
hae/
    +---bin
    +---inc
    |   \---alljoyn
    |       \---hae
    |           \---interfaces
    |               +---environment
    |               +---input
    |               \---operation
    \---lib
</pre>

    - path : root-source-dir/services/hae/build/$OS/$TARGET_CPU/debug/dist/hae
    - bin : IntegratedController, TvControllee
    - lib : liballjoyn_hae.a, liballjoyn_hae.so
    - inc : header files

Doxygen
-------
  * Make manual
<pre>
cd root-source-dir/services/hae/cpp/docs
doxygen Doxygen_html
</pre>

  * Make manual in the building step
<pre>
cd root-source-dir/services/hae
scons BINDINGS=cpp WS=off BT=off ICE=off DOCS=html
</pre>

How to add new interface
------------------------
  1. Generate the skeleton codes using make_interface.py script.
  2. Fill the codes for properties, methods and signals in all files generated.

    * create skeleton codes for new interface
<pre>
cd root-source-dir/services/hae/cpp/code_template
python make_interface.py -n InterfaceName -c CategoryName
(InterfaceName and CategoryName are case sensitive.)
[example]
python make_interface.py -n TargetTemperature -c Environment
Created: ../inc/alljoyn/hae/interfaces/environment/TargetTemperatureInterface.h
Created: ../inc/alljoyn/hae/interfaces/environment/TargetTemperatureIntfControllee.h
Created: ../inc/alljoyn/hae/interfaces/environment/TargetTemperatureIntfControlleeListener.h
Created: ../inc/alljoyn/hae/interfaces/environment/TargetTemperatureIntfController.h
Created: ../inc/alljoyn/hae/interfaces/environment/TargetTemperatureIntfControllerListener.h
Created: ../src/interfaces/environment/TargetTemperatureInterface.cc
Created: ../src/interfaces/environment/TargetTemperatureIntfControlleeImpl.h
Created: ../src/interfaces/environment/TargetTemperatureIntfControlleeImpl.cc
Created: ../src/interfaces/environment/TargetTemperatureIntfControllerImpl.h
Created: ../src/interfaces/environment/TargetTemperatureIntfControllerImpl.cc
</pre>

    * delete files related new interface
<pre>
cd root-source-dir/services/hae/cpp/code_template
python make_interface.py -n InterfaceName -c Category -d
</pre>

How to add vendor defined interface
------------------------------------
  1. Generate the skeleton codes using make_interface.py script.
  2. Copy all files to your application folder
  3. Fill the codes for properties, methods and signals in all files generated.

    * create skeleton codes for vendor defined interface
<pre>
cd root-source-dir/services/hae/cpp/code_template
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

    * delete files related vendor defined interface
<pre>
cd root-source-dir/services/hae/cpp/code_template
python make_interface.py -n InterfaceName -v -d
</pre>

