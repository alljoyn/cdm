
ROOT      = /Users/anthonyshipman/Documents/AllJoyn/
IFACES    = $(ROOT)/alljoyn_interfaces/interfaces/

CDM       = $(ROOT)/services/cdm/
TEMPLATES = $(CDM)/generator/templates/interface_templates/cdm/cpp/
OUTPUT    = ./output

INSTALL_DIR = $(CDM)/


XML_FILES = \
    org.alljoyn.SmartSpaces.Operation/AirRecirculationMode-v1.xml \
    org.alljoyn.SmartSpaces.Operation/Alerts-v1.xml \
    org.alljoyn.SmartSpaces.Operation/AudioVideoInput-v1.xml \
    org.alljoyn.SmartSpaces.Operation/AudioVolume-v1.xml \
    org.alljoyn.SmartSpaces.Operation/BatteryStatus-v1.xml \
    org.alljoyn.SmartSpaces.Operation/Brightness-v1.xml \
    org.alljoyn.SmartSpaces.Operation/Channel-v1.xml \
    org.alljoyn.SmartSpaces.Operation/ClimateControlMode-v1.xml \
    org.alljoyn.SmartSpaces.Operation/ClosedStatus-v1.xml \
    org.alljoyn.SmartSpaces.Operation/Color-v1.xml \
    org.alljoyn.SmartSpaces.Operation/ColorTemperature-v1.xml \
    org.alljoyn.SmartSpaces.Operation/CurrentPower-v1.xml \
    org.alljoyn.SmartSpaces.Operation/CycleControl-v1.xml \
    org.alljoyn.SmartSpaces.Operation/DishWashingCyclePhase-v1.xml \
    org.alljoyn.SmartSpaces.Operation/EnergyUsage-v1.xml \
    org.alljoyn.SmartSpaces.Operation/FanSpeedLevel-v1.xml \
    org.alljoyn.SmartSpaces.Operation/FilterStatus-v1.xml \
    org.alljoyn.SmartSpaces.Operation/HeatingZone-v1.xml \
    org.alljoyn.SmartSpaces.Operation/HvacFanMode-v1.xml \
    org.alljoyn.SmartSpaces.Operation/LaundryCyclePhase-v1.xml \
    org.alljoyn.SmartSpaces.Operation/LockControl-v1.xml \
    org.alljoyn.SmartSpaces.Operation/LockedStatus-v1.xml \
    org.alljoyn.SmartSpaces.Operation/MoistureOutputLevel-v1.xml \
    org.alljoyn.SmartSpaces.Operation/OffControl-v1.xml \
    org.alljoyn.SmartSpaces.Operation/OnControl-v1.xml \
    org.alljoyn.SmartSpaces.Operation/OnOffStatus-v1.xml \
    org.alljoyn.SmartSpaces.Operation/OvenCyclePhase-v1.xml \
    org.alljoyn.SmartSpaces.Operation/PlugInUnits-v1.xml \
    org.alljoyn.SmartSpaces.Operation/RapidMode-v1.xml \
    org.alljoyn.SmartSpaces.Operation/RapidModeTimed-v1.xml \
    org.alljoyn.SmartSpaces.Operation/RemoteControllability-v1.xml \
    org.alljoyn.SmartSpaces.Operation/RepeatMode-v1.xml \
    org.alljoyn.SmartSpaces.Operation/ResourceSaving-v1.xml \
    org.alljoyn.SmartSpaces.Operation/RobotCleaningCyclePhase-v1.xml \
    org.alljoyn.SmartSpaces.Operation/SoilLevel-v1.xml \
    org.alljoyn.SmartSpaces.Operation/SpinSpeedLevel-v1.xml \
    org.alljoyn.SmartSpaces.Operation/Timer-v1.xml \
    org.alljoyn.SmartSpaces.Operation/TriggerSensor-v1.xml \
    org.alljoyn.SmartSpaces.Operation/UnlockControl-v1.xml

XML_PATHS = $(addprefix $(IFACES),$(XML_FILES))

all:
	@ echo "Will process:"
	@ for x in $(XML_FILES); do echo $$x; done

generate: generate_common generate_controllee generate_samples

generate_common:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches templates/patches/cpp --components=common $(TEMPLATES) $$x ;\
	done

generate_controllee:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches templates/patches/cpp --components=controllee $(TEMPLATES) $$x ;\
	done

generate_samples:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches templates/patches/cpp --components=samples $(TEMPLATES) $$x ;\
	done

install: install_interfaces install_samples

install_interfaces:
	(cd $(OUTPUT); find interfaces -type f|cpio -dump $(CDM)/cpp)

install_samples:
	(cd $(OUTPUT); find samples -type f|cpio -dump $(CDM)/cpp)

clean:
	$(RM) -rf $(OUTPUT)
