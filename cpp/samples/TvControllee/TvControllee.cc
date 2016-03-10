#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/hae/DeviceTypeDescription.h>
#include "ControlleeSample.h"
#include "AudioVolumeListener.h"
#include "ChannelListener.h"
#include "AudioVideoInputListener.h"
#include "ClosedStatusListener.h"
#include "HidListener.h"
#include <alljoyn/hae/interfaces/operation/AudioVolumeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ClosedStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ChannelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AudioVideoInputIntfControllee.h>
#include <alljoyn/hae/interfaces/input/HidIntfControllee.h>

using namespace std;
using namespace qcc;

class TvControllee : public ControlleeSample
{
  private:
    AudioVolumeListener* m_audioVolumeListener;
    ChannelListener* m_channelListener;
    AudioVideoInputListener* m_avInputListener;
    HidListener *m_hidListener;
    ClosedStatusListener *m_closedStatusListener;
    AudioVolumeIntfControllee* m_audioVolumeIntfControllee;
    ChannelIntfControllee* m_channelIntfControllee;
    AudioVideoInputIntfControllee* m_avInputIntfControllee;
    HidIntfControllee* m_hidIntfControllee;
    ClosedStatusIntfControllee* m_closedStatusIntfControllee;

  public:
    TvControllee(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~TvControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

TvControllee::TvControllee(BusAttachment* bus, HaeAboutData* aboutData)
  : ControlleeSample(bus, aboutData),
    m_audioVolumeListener(NULL), m_channelListener(NULL), m_avInputListener(NULL), m_hidListener(NULL),
    m_audioVolumeIntfControllee(NULL), m_channelIntfControllee(NULL), m_avInputIntfControllee(NULL), m_hidIntfControllee(NULL), m_closedStatusIntfControllee(NULL)
{
    m_audioVolumeListener = new AudioVolumeListener();
    m_channelListener = new ChannelListener();
    m_avInputListener = new AudioVideoInputListener();
    m_hidListener = new HidListener();
    m_closedStatusListener = new ClosedStatusListener();
}

TvControllee::~TvControllee()
{
    if (m_audioVolumeListener) {
        delete m_audioVolumeListener;
    }
    if (m_channelListener) {
        delete m_channelListener;
    }
    if (m_avInputListener) {
        delete m_avInputListener;
    }
    if (m_hidListener) {
        delete m_hidListener;
    }
    if(m_closedStatusListener){
    	delete m_closedStatusListener;
    }
}

void TvControllee::CreateInterfaces()
{
    HaeInterface* intf = NULL;
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }

    intf = haeControllee->CreateInterface(AUDIO_VOLUME_INTERFACE, "/Hae/Tv", *m_audioVolumeListener);
    m_audioVolumeIntfControllee = static_cast<AudioVolumeIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(CHANNEL_INTERFACE, "/Hae/Tv", *m_channelListener);
    m_channelIntfControllee = static_cast<ChannelIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(AUDIO_VIDEO_INPUT_INTERFACE, "/Hae/Tv", *m_avInputListener);
    m_avInputIntfControllee = static_cast<AudioVideoInputIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(HID_INTERFACE, "/Hae/Tv", *m_hidListener);
    m_hidIntfControllee = static_cast<HidIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(CLOSED_STATUS_INTERFACE, "/Hae/Tv", *m_closedStatusListener);
    m_closedStatusIntfControllee = static_cast<ClosedStatusIntfControllee*>(intf);

}

void TvControllee::SetInitialProperty()
{
    if (m_audioVolumeIntfControllee) {
        uint8_t volume = 1;
        uint8_t maxVolume = 100;
        bool mute = false;
        m_audioVolumeIntfControllee->SetVolume(volume);
        m_audioVolumeIntfControllee->SetMaxVolume(maxVolume);
        m_audioVolumeIntfControllee->SetMute(mute);
    }

    if (m_channelIntfControllee) {
        String channelId = "0_1_2_3_4";
        uint16_t totalNumberOfChannels = 50;
        m_channelIntfControllee->SetChannelId(channelId);
        m_channelIntfControllee->SetTotalNumberOfChannels(totalNumberOfChannels);
    }

    if (m_avInputIntfControllee) {
        AudioVideoInputInterface::InputSources inputSources;
        AudioVideoInputInterface::InputSource inputSource1, inputSource2;
        uint16_t inputSource1Id = 8080;
        inputSource1.sourceType = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SOURCE_TYPE_HDMI;
        inputSource1.signalPresence = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_ABSENT;
        inputSource1.portNumber = 1;
        inputSource1.friendlyName = "HDMI1";
        inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(inputSource1Id, inputSource1));
        uint16_t inputSource2Id = 8000;
        inputSource2.sourceType = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SOURCE_TYPE_TUNER;
        inputSource2.signalPresence = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_PRESENT;
        inputSource2.portNumber = 1;
        inputSource2.friendlyName = "TUNER";
        inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(inputSource2Id, inputSource2));
        uint16_t inputSourceId = inputSource1Id;
        m_avInputIntfControllee->SetSupportedInputSources(inputSources);
        m_avInputIntfControllee->SetInputSourceId(inputSourceId);
    }

    if (m_hidIntfControllee) {
        HidInterface::SupportedInputEvents supportedEvents;
        HidInterface::SupportedInputEvent supportedEvent;
        // synchronization event (required to synchronize other events)
        supportedEvent.type = 0x00; // EV_SYN
        supportedEvent.code = 0; //SYN_REPORT
        supportedEvent.min = 0;
        supportedEvent.max = 0;
        supportedEvents.push_back(supportedEvent);
        // all numeric keys
        for(uint16_t code = 0x200; code <= 0x209; code++) { // KEY_NUMERIC_0 to KEY_NUMERIC_9
            supportedEvent.type = 0x01; // EV_KEY
            supportedEvent.code = code;
            supportedEvent.min = 0; // release state
            supportedEvent.max = 1; // press state
            supportedEvents.push_back(supportedEvent);
        }
        // all volume keys
        for(uint16_t code = 0x71; code <= 0x73; code++) { // KEY_MUTE to KEY_VOLUMEUP
            supportedEvent.type = 0x01; // EV_KEY
            supportedEvent.code = code;
            supportedEvent.min = 0; // release state
            supportedEvent.max = 1; // press state
            supportedEvents.push_back(supportedEvent);
        }
        m_hidIntfControllee->SetSupportedEvents(supportedEvents);
    }
}

QStatus FillAboutData(HaeAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc02d";
    String app_name = "TVControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "TV"));

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
        aboutData->SetDeviceName("My device name", "en");
    }

    aboutData->SetDescription("This is an TV Controllee Application", "en");
    aboutData->SetManufacturer("Manufacturer", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // HAE custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("TV Brand", "en");
    aboutData->SetProductBrand("TV", "en");
    aboutData->SetLocation("Room1", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(TELEVISION, "/Hae/Tv");
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

    BusAttachment* bus = new BusAttachment("TVControllee", true);
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

    TvControllee controllee(bus, aboutData);

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
