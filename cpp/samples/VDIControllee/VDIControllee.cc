#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/hae/DeviceTypeDescription.h>
#include "ControlleeCommands.h"
#include "ControlleeSample.h"
#include "AudioVolumeListener.h"
#include "VendorDefinedIntfControllee.h"
#include "VendorDefinedIntfControlleeImpl.h"
#include "VendorDefinedIntfControlleeListener.h"
#include "VendorDefinedListener.h"
#include <alljoyn/hae/interfaces/operation/AudioVolumeIntfControllee.h>

using namespace std;
using namespace qcc;

class VDIControllee : public ControlleeSample
{
  public:
    HaeInterfaceType m_vendorDefinedIntfType;
    AudioVolumeListener* m_audioVolumeListener;
    VendorDefinedListener* m_vendorDefinedListener;

    AudioVolumeIntfControllee* m_audioVolumeIntfControllee;
    VendorDefinedIntfControllee* m_vendorDefinedIntfControllee;

    VDIControllee(BusAttachment* bus, HaeAboutData* aboutData);
    ~VDIControllee();

    void InitSample();
    void CreateInterfaces();
    void SetInitialProperty();

    static void OnCmdEmitTestSignal(Commands* commands, std::string& cmd);
};

VDIControllee::VDIControllee(BusAttachment* bus, HaeAboutData* aboutData)
: ControlleeSample(bus, aboutData),
  m_audioVolumeListener(NULL), m_vendorDefinedListener(NULL),
  m_audioVolumeIntfControllee(NULL), m_vendorDefinedIntfControllee(NULL)
{
    m_audioVolumeListener = new AudioVolumeListener();
    m_vendorDefinedListener = new VendorDefinedListener();
}

VDIControllee::~VDIControllee()
{
    if (m_audioVolumeListener) {
        delete m_audioVolumeListener;
    }
    if (m_vendorDefinedListener) {
        delete m_vendorDefinedListener;
    }
}

void VDIControllee::OnCmdEmitTestSignal(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();
    if (static_cast<VDIControllee*>(sample)->m_vendorDefinedIntfControllee) {
        static_cast<VDIControllee*>(sample)->m_vendorDefinedIntfControllee->EmitTestSignal();
    }
}

void VDIControllee::InitSample()
{
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }
    m_vendorDefinedIntfType = haeControllee->RegisterVendorDefinedInterface("com.foo.bar.test", static_cast<CreateIntfControlleeFptr>(&VendorDefinedIntfControlleeImpl::CreateInterface));

    m_rootCommands->RegisterCommand(&VDIControllee::OnCmdEmitTestSignal, "ets", "emit test signal");
}

void VDIControllee::CreateInterfaces()
{
    HaeInterface* intf = NULL;
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }

    intf = haeControllee->CreateInterface(AUDIO_VOLUME_INTERFACE, "/Hae/Test", *m_audioVolumeListener);
    m_audioVolumeIntfControllee = static_cast<AudioVolumeIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(m_vendorDefinedIntfType, "/Hae/Test", *m_vendorDefinedListener);
    m_vendorDefinedIntfControllee = static_cast<VendorDefinedIntfControllee*>(intf);
}

void VDIControllee::SetInitialProperty()
{
    if (m_audioVolumeIntfControllee) {
        uint8_t volume = 1;
        uint8_t maxVolume = 100;
        bool mute = false;
        m_audioVolumeIntfControllee->SetVolume(volume);
        m_audioVolumeIntfControllee->SetMaxVolume(maxVolume);
        m_audioVolumeIntfControllee->SetMute(mute);
    }

    if (m_vendorDefinedIntfControllee) {
//        int property1 = 100;
//        std::string property2 = "This is a property2.";

//        m_vendorDefinedIntfControllee->SetProperty1(property1);
//        m_vendorDefinedIntfCotnrollee->SetProperty2(property2);
    }

}

QStatus FillAboutData(HaeAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc01a";
    String app_name = "VDIControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "VDI"));

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

    aboutData->SetModelNumber("Wxfy388i");
    aboutData->SetDateOfManufacture("10/1/2199");
    aboutData->SetSoftwareVersion("12.20.44 build 44454");
    aboutData->SetHardwareVersion("355.499. b");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("VDIControllee", "en");
    }

    aboutData->SetDescription("This application is a sample programe that supports the vendor defined interface", "en");
    aboutData->SetManufacturer("Manufacturer", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // HAE custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("Test Brand", "en");
    aboutData->SetProductBrand("Test", "en");
    aboutData->SetLocation("Room1", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(TELEVISION, "/Hae/Test");
    aboutData->SetDeviceTypeDescription(&description);

    if (!aboutData->IsValid()) {

        return ER_FAIL;
    }

    return ER_OK;
}

int main()
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
    QCC_SetLogLevels("HAE_MODULE_LOG_NAME=15;");

    BusAttachment* bus = new BusAttachment("VDIControllee", true);
    if (!bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    HaeAboutData* aboutData = new HaeAboutData();
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

    VDIControllee controllee(bus, aboutData);

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
