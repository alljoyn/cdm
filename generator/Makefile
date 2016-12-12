
IFACES    = $(AJ_ROOT)/alljoyn_interfaces/interfaces/
CDM       = $(AJ_ROOT)/services/cdm/
THIN      = $(AJ_ROOT)/services/cdm_tcl/

ifeq ($(which),tcl)
INSTALL_DIR = $(THIN)/
TEMPLATES   = $(CDM)/generator/templates/interface_templates/cdm_tcl/
PATCHES     = templates/patches_tcl/
GENERATE_TARGETS = generate_tcl generate_tcl_samples
INSTALL_TARGETS  = install_tcl
else
INSTALL_DIR = $(CDM)/cpp
TEMPLATES   = $(CDM)/generator/templates/interface_templates/cdm/cpp/
PATCHES     = templates/patches/cpp
GENERATE_TARGETS = generate_common generate_controllee generate_controller generate_samples generate_factory
INSTALL_TARGETS  = install_common install_controllee install_controller install_samples install_factory
endif

OUTPUT    = ./output

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
    org.alljoyn.SmartSpaces.Operation/UnlockControl-v1.xml \
    org.alljoyn.SmartSpaces.Environment/CurrentAirQuality-v1.xml \
    org.alljoyn.SmartSpaces.Environment/CurrentAirQualityLevel-v1.xml \
    org.alljoyn.SmartSpaces.Environment/CurrentHumidity-v1.xml \
    org.alljoyn.SmartSpaces.Environment/CurrentTemperature-v1.xml \
    org.alljoyn.SmartSpaces.Environment/TargetHumidity-v1.xml \
    org.alljoyn.SmartSpaces.Environment/TargetTemperature-v1.xml \
    org.alljoyn.SmartSpaces.Environment/TargetTemperatureLevel-v1.xml \
    org.alljoyn.SmartSpaces.Environment/WaterLevel-v1.xml \
    org.alljoyn.SmartSpaces.Environment/WindDirection-v1.xml

XML_PATHS = $(addprefix $(IFACES),$(XML_FILES))

all:
	@ echo "Will process:"
	@ for x in $(XML_FILES); do echo $$x; done

generate: $(GENERATE_TARGETS)

generate_common:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches $(PATCHES) --components=common $(TEMPLATES) $$x || exit 1;\
	done

generate_controllee:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches $(PATCHES) --components=controllee $(TEMPLATES) $$x || exit 1;\
	done

generate_controller:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches $(PATCHES) --components=controller $(TEMPLATES) $$x || exit 1;\
	done

generate_samples:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches $(PATCHES) --components=samples $(TEMPLATES) $$x || exit 1;\
	done

generate_tcl:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches $(PATCHES) --components=tcl $(TEMPLATES) $$x || exit 1;\
	done

generate_tcl_samples:
	@for x in $(XML_PATHS); do \
            ./generate.py --patches $(PATCHES) --components=samples $(TEMPLATES) $$x || exit 1;\
	done

generate_factory:
	@./genFactory.py $(XML_PATHS)

install: $(INSTALL_TARGETS)

install_interfaces:
	(cd $(OUTPUT); find interfaces -type f|cpio -dump $(INSTALL_DIR))

install_samples:
	(cd $(OUTPUT); find samples -type f|cpio -dump $(INSTALL_DIR))

install_tcl:
	(cd $(OUTPUT); find inc src samples -type f|cpio -dump $(INSTALL_DIR))

install_factory:
	cp ControllerFactory.cc $(INSTALL_DIR)/interfaces/src

clean:
	$(RM) -rf $(OUTPUT)
