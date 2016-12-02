#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>

#include <alljoyn/cdm/DeviceTypeDescription.h>
#include <alljoyn/cdm/CdmSystem.h>
#include <alljoyn/cdm/CdmAnnouncer.h>
#include <alljoyn/cdm/CdmSecurity.h>

#include "ControlleeCommands.h"
#include "ControlleeSample.h"
#include "AudioVolumeListener.h"
#include "VendorDefinedIntfControllee.h"
#include "VendorDefinedIntfControlleeImpl.h"
#include "VendorDefinedIntfControlleeListener.h"
#include "VendorDefinedListener.h"
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllee.h>

using namespace std;
using namespace qcc;

class VDIControllee : public ControlleeSample
{
  public:
    CdmInterfaceType m_vendorDefinedIntfType;
    AudioVolumeListener* m_audioVolumeListener;
    VendorDefinedListener* m_vendorDefinedListener;

    AudioVolumeIntfControllee* m_audioVolumeIntfControllee;
    VendorDefinedIntfControllee* m_vendorDefinedIntfControllee;

    VDIControllee(BusAttachment* bus, Ref<CdmAnnouncer> announcer, Ref<CdmSecurity> security);
    ~VDIControllee();

    void InitSample();
    void CreateInterfaces();
    void SetInitialProperty();

    static void OnCmdEmitTestSignal(Commands* commands, std::string& cmd);
};

VDIControllee::VDIControllee(BusAttachment* bus, Ref<CdmAnnouncer> announcer, Ref<CdmSecurity> security)
: ControlleeSample(bus, announcer, security),
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
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }
    m_vendorDefinedIntfType = cdmControllee->RegisterVendorDefinedInterface("com.foo.bar.test", static_cast<CreateIntfControlleeFptr>(&VendorDefinedIntfControlleeImpl::CreateInterface));

    m_rootCommands->RegisterCommand(&VDIControllee::OnCmdEmitTestSignal, "ets", "emit test signal");
}

void VDIControllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    intf = cdmControllee->CreateInterface(AUDIO_VOLUME_INTERFACE, "/Cdm/Test", *m_audioVolumeListener);
    m_audioVolumeIntfControllee = static_cast<AudioVolumeIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(m_vendorDefinedIntfType, "/Cdm/Test", *m_vendorDefinedListener);
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



int CDECL_CALL main()
{
    CdmSystem system("VDIControllee");

    QStatus status = system.Start();

    if (status != ER_OK) {
        cerr << "Failed to start the VDIControllee " << QCC_StatusText(status) << "\n";
        return 1;
    }

    // Note that QCC_SetLogLevels can't be called until CdmSystem has been started.
    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());
    QCC_SetLogLevels("CDM_MODULE_LOG_NAME=15;");

    auto announcer = mkRef<CdmAnnouncer>(system.GetBusAttachment());
    auto security  = mkRef<CdmSecurity>(system.GetBusAttachment());

    announcer->SetAboutData(
       "<AboutData>"
       "  <AppId>4a354637-5649-4518-8a48-323c158bc005</AppId>"
       "  <DefaultLanguage>en</DefaultLanguage>"
       "  <DeviceName>TV</DeviceName>"
       "  <DeviceId>deviceID</DeviceId>"
       "  <AppName>VDIControllee</AppName>"
       "  <Manufacturer>Manufacturer</Manufacturer>"
       "  <ModelNumber>Wxfy388i</ModelNumber>"
       "  <Description>This application is a sample programe that supports the vendor defined interface</Description>"
       "  <DateOfManufacture>10/1/2199</DateOfManufacture>"
       "  <SoftwareVersion>12.20.44 build 44454</SoftwareVersion>"
       "  <HardwareVersion>355.499.b</HardwareVersion>"
       "  <SupportUrl>http://www.alljoyn.org</SupportUrl>"
       "  <CountryOfProduction>USA</CountryOfProduction>"
       "  <CorporateBrand>Test Brand</CorporateBrand>"
       "  <ProductBrand>Test</ProductBrand>"
       "  <Location>Room1</Location>"
       "  <DeviceTypeDescription>"
       "      <TypeDescription>"
       "          <device_type>21</device_type>"
       "          <object_path>/Cdm/Test</object_path>"
       "      </TypeDescription>"
       "  </DeviceTypeDescription>"
       "</AboutData>");

    VDIControllee controllee(&system.GetBusAttachment(), announcer, security);

    controllee.Startup();

    controllee.Shutdown();
    return 0;
}
