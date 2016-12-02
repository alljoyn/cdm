#include <iostream>
#include <map>
#include <algorithm>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>
#include "ControlleeCommands.h"
#include "ControlleeSample.h"
#include "OnOffStatusListener.h"
#include "CycleControlListener.h"
#include "SoilLevelListener.h"
#include "SpinSpeedLevelListener.h"
#include "WaterLevelListener.h"
#include "DishWashingCyclePhaseListener.h"
#include "LaundryCyclePhaseListener.h"
#include "TimerListener.h"
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllee.h>

using namespace std;
using namespace qcc;

class LaundryControllee : public ControlleeSample
{
  private:
    OnOffStatusListener *m_onOffStatusListener;
    CycleControlListener *m_cycleControlListener;
    SoilLevelListener *m_soilLevelListener;
    SpinSpeedLevelListener *m_spinSpeedLevelListener;
    WaterLevelListener *m_waterLevelListener;
    DishWashingCyclePhaseListener* m_dishWashingCyclePhaseListener;
    LaundryCyclePhaseListener* m_laundryCyclePhaseListener;
    TimerListener * m_timerListener;

    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    CycleControlIntfControllee* m_cycleControlIntfControllee;
    SoilLevelIntfControllee* m_soilLevelIntfControllee;
    SpinSpeedLevelIntfControllee* m_spinSpeedLevelIntfControllee;
    WaterLevelIntfControllee* m_waterLevelIntfControllee;
    DishWashingCyclePhaseIntfControllee* m_dishWashingCyclePhaseIntfControllee;
    LaundryCyclePhaseIntfControllee* m_laundryCyclePhaseIntfControllee;
    TimerIntfControllee* m_timerIntfControllee;

  public:
    LaundryControllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~LaundryControllee();
    void CreateInterfaces();
    void SetInitialProperty();
    void InitSample();

    static void OnCmdSetState(Commands* commands, std::string& cmd);
    static void OnCmdSetCurWaterLvl(Commands* commands, std::string& cmd);

};

LaundryControllee::LaundryControllee(BusAttachment* bus, CdmAboutData* aboutData)
  : ControlleeSample(bus, aboutData),m_onOffStatusIntfControllee(NULL), m_cycleControlIntfControllee(NULL),m_soilLevelIntfControllee(NULL),m_spinSpeedLevelIntfControllee(NULL),
    m_waterLevelIntfControllee(NULL), m_dishWashingCyclePhaseIntfControllee(NULL), m_laundryCyclePhaseIntfControllee(NULL), m_timerIntfControllee(NULL)

{
    m_onOffStatusListener = new OnOffStatusListener();
    m_cycleControlListener = new CycleControlListener();
    m_soilLevelListener = new SoilLevelListener();
    m_spinSpeedLevelListener = new SpinSpeedLevelListener();
    m_waterLevelListener = new WaterLevelListener();
    m_dishWashingCyclePhaseListener = new DishWashingCyclePhaseListener();
    m_laundryCyclePhaseListener = new LaundryCyclePhaseListener();
    m_timerListener = new TimerListener();
}

LaundryControllee::~LaundryControllee()
{
    if(m_onOffStatusListener){
        delete m_onOffStatusListener;
    }
    if(m_cycleControlListener){
        delete m_cycleControlListener;
    }
    if(m_soilLevelListener){
        delete m_soilLevelListener;
    }
    if(m_spinSpeedLevelListener){
        delete m_spinSpeedLevelListener;
    }
    if(m_waterLevelListener) {
        delete m_waterLevelListener;
    }
    if(m_dishWashingCyclePhaseListener) {
        delete m_dishWashingCyclePhaseListener;
    }
    if(m_laundryCyclePhaseListener) {
        delete m_laundryCyclePhaseListener;
    }
    if(m_timerListener) {
        delete m_timerListener;
    }
}
void LaundryControllee::InitSample()
{
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }
    m_rootCommands->RegisterCommand(&LaundryControllee::OnCmdSetState, "ss", "set state");
    m_rootCommands->RegisterCommand(&LaundryControllee::OnCmdSetCurWaterLvl, "scw", "set cur water lvl");
}
void LaundryControllee::OnCmdSetState(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();

    int state = strtol(cmd.c_str(), NULL, 10);

    if (static_cast<LaundryControllee*>(sample)->m_cycleControlIntfControllee) {
        static_cast<LaundryControllee*>(sample)->m_cycleControlIntfControllee->SetOperationalState((CycleControlInterface::CycleControlOperationalState)state);
    }
}
void LaundryControllee::OnCmdSetCurWaterLvl(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();

    int lvl = strtol(cmd.c_str(), NULL, 10);

    if (static_cast<LaundryControllee*>(sample)->m_waterLevelIntfControllee) {
        static_cast<LaundryControllee*>(sample)->m_waterLevelIntfControllee->SetCurrentLevel(lvl);
    }
}
void LaundryControllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    intf = cdmControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Cdm/Laundry", *m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CYCLE_CONTROL_INTERFACE, "/Cdm/Laundry", *m_cycleControlListener);
    m_cycleControlIntfControllee = static_cast<CycleControlIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(SOIL_LEVEL_INTERFACE, "/Cdm/Laundry", *m_soilLevelListener);
    m_soilLevelIntfControllee = static_cast<SoilLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(SPIN_SPEED_LEVEL_INTERFACE, "/Cdm/Laundry", *m_spinSpeedLevelListener);
    m_spinSpeedLevelIntfControllee = static_cast<SpinSpeedLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(WATER_LEVEL_INTERFACE, "/Cdm/Laundry", *m_waterLevelListener);
    m_waterLevelIntfControllee = static_cast<WaterLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(DISH_WASHING_CYCLE_PHASE_INTERFACE, "/Cdm/Laundry", *m_dishWashingCyclePhaseListener);
    m_dishWashingCyclePhaseIntfControllee = static_cast<DishWashingCyclePhaseIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(LAUNDRY_CYCLE_PHASE_INTERFACE, "/Cdm/Laundry", *m_laundryCyclePhaseListener);
    m_laundryCyclePhaseIntfControllee = static_cast<LaundryCyclePhaseIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TIMER_INTERFACE, "/Cdm/Laundry", *m_timerListener);
    m_timerIntfControllee = static_cast<TimerIntfControllee*>(intf);
}

void LaundryControllee::SetInitialProperty()
{
    cout << "LaundryControllee::SetInitialProperty()" << endl;

    //CycleCControlInterface
    CycleControlInterface::SupportedOperationalCommands comm;
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_STOP);
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_PAUSE);
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_RESUME);
    m_cycleControlIntfControllee->SetSupportedCommands(comm);

    CycleControlInterface::SupportedOperationalStates states;
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING);

    m_cycleControlIntfControllee->SetSupportedStates(states);

    //SoilLevelInterface
    uint8_t maxLvl = m_soilLevelIntfControllee->GetMaxLevel();
    std::vector<uint8_t> selectableLevelsSoil;
    for(uint8_t i = 0; i < maxLvl; i++)
        selectableLevelsSoil.push_back((uint8_t)i);
    QStatus status = m_soilLevelIntfControllee->SetSelectableLevels(selectableLevelsSoil);

    //SpinSpeedLevel Interface
    maxLvl = m_spinSpeedLevelIntfControllee->GetMaxLevel();
    std::vector<uint8_t> selectableLevelsSpin;
    for(int i = 0; i < maxLvl; i++)
        selectableLevelsSpin.push_back((uint8_t)i);
    m_spinSpeedLevelIntfControllee->SetSelectableLevels(selectableLevelsSpin);

    //DishWashingCyclePhase Interface
    m_dishWashingCyclePhaseIntfControllee->SetCyclePhase(DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_DRY);

    DishWashingCyclePhaseInterface::SupportedCyclePhases phases;
    phases.push_back(DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_DRY);
    phases.push_back(DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_PRE_WASH);
    phases.push_back(DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_RINSE);
    phases.push_back(DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_UNAVAILABLE);
    phases.push_back(DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_WASH);

    m_dishWashingCyclePhaseIntfControllee->SetSupportedCyclePhases(phases);

    //LaundryCyclePhase Interface
    m_laundryCyclePhaseIntfControllee->SetCyclePhase(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_STEAM);

    LaundryCyclePhaseInterface::SupportedCyclePhases aphases;
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_UNAVAILABLE);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_STEAM);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_ANTICREASING);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_COOLING);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_DRYING);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_PRE_WASHING);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_RINSING);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_RINSING);
    aphases.push_back(LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_SPINNING);

    m_laundryCyclePhaseIntfControllee->SetSupportedCyclePhases(aphases);
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc002";
    String app_name = "LaundryControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "ClothesWasher"));

    if (!app_id.empty()) {
        aboutData->SetAppId(app_id.c_str());
    }

    if (device_id != "") {
        aboutData->SetDeviceId(device_id.c_str());
    }

    vector<String> languages(1);
    languages[0] = "en";

    for (size_t i = 0; i < languages.size(); i++) {
        aboutData->SetSupportedLanguage(languages[i].c_str());
    }

    if (defaultLanguage != "") {
        aboutData->SetDefaultLanguage(defaultLanguage.c_str());
    }

    if (app_name != "") {
        aboutData->SetAppName(app_name.c_str(), languages[0].c_str());
    }

    aboutData->SetModelNumber("ModelNumber");
    aboutData->SetDateOfManufacture("15/1/2199");
    aboutData->SetSoftwareVersion("55.55.55 build 555");
    aboutData->SetHardwareVersion("555.555. b");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("Laundry device", "en");
    }

    aboutData->SetDescription("This is an Laundry Controllee Application", "en");
    aboutData->SetManufacturer("Nik", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("SP", "en");
    aboutData->SetCorporateBrand("Laundry", "en");
    aboutData->SetProductBrand("Model 1", "en");
    aboutData->SetLocation("Basement", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(CLOTHES_WASHER, "/Cdm/Laundry");
    aboutData->SetDeviceTypeDescription(&description);

    if (!aboutData->IsValid()) {

        return ER_FAIL;
    }

    return ER_OK;
}

int CDECL_CALL main()
{


    if (AllJoynInit() != ER_OK) {
        printf("FAILED to init alljoyn\n");
        exit(1);
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        printf("FAILED to init router\n");
        exit(1);
    }
#endif
    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());
    QCC_SetLogLevels("CDM_MODULE_LOG_NAME=15;");

    BusAttachment* bus = new BusAttachment("TVControllee", true);
    if (!bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    CdmAboutData* aboutData = new CdmAboutData();
    if (!aboutData) {
        printf("AboutData creation failed.\n");
        delete bus;
        exit(1);
    }
    FillAboutData(aboutData);

    QStatus status = bus->Start();
    if (ER_OK != status) {
        printf("BusAttachment::Start failed (%s)\n", QCC_StatusText(status));
        delete bus;
        delete aboutData;
        exit(1);
    }

    status = bus->Connect();
    if (ER_OK != status) {
        printf("BusAttachment::Connect failed (%s)\n", QCC_StatusText(status));
        bus->Stop();
        bus->Join();
        delete bus;
        delete aboutData;
        exit(1);
    }

    LaundryControllee controllee(bus, aboutData);

    controllee.Startup();

    controllee.Shutdown();

    if (bus) {
        bus->Disconnect();
        bus->Stop();
        bus->Join();

        delete bus;
    }

    if (aboutData) {
        delete aboutData;
    }

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();

    return 0;
}
