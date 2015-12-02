#include "ControllerSample.h"
#include "BasicCommands.h"
#include "DeviceCommands.h"

using namespace std;
using namespace ajn;
using namespace services;

ControllerSample::ControllerSample(BusAttachment* bus)
  : m_bus(bus), m_controller(NULL), m_rootCommands(NULL)
{
}

ControllerSample::~ControllerSample()
{
}

QStatus ControllerSample::Init()
{
    QStatus status = ER_OK;

    m_controller = new HaeController(*m_bus, this);
    if (!m_controller) {
        status = ER_OUT_OF_MEMORY;
        printf("Controller creation failed (%s)\n", QCC_StatusText(status));
        return status;
    }
    m_rootCommands = new BasicControllerCommands(this);
    if (!m_rootCommands) {
        status = ER_OUT_OF_MEMORY;
        delete m_controller;
        printf("m_rootCommand creation failed (%s)\n", QCC_StatusText(status));
        return status;
    }
    PushCommands(m_rootCommands);

    InterestDeviceList list;
    status = m_controller->Init(list);
    if (ER_OK != status) {
        delete m_controller;
        m_controller = NULL;
        delete m_rootCommands;
        m_rootCommands = NULL;
        printf("Controller init failed (%s)\n", QCC_StatusText(status));
        return status;
    }

    status = m_controller->Start();
    if (ER_OK != status) {
        delete m_controller;
        m_controller = NULL;
        delete m_rootCommands;
        m_rootCommands = NULL;
        printf("Controller start failed (%s)\n", QCC_StatusText(status));
        return status;
    }

    return status;
}

void ControllerSample::Deinit()
{
    m_controller->Stop();
    if (m_controller) {
        delete m_controller;
        m_controller = 0;
    }

    if (m_rootCommands) {
        delete m_rootCommands;
        m_rootCommands = 0;
    }
}

void ControllerSample::OnDeviceAdded(const char* busname,
        SessionPort port,
        const HaeAboutData& data,
        const AboutObjectDescription& description)
{
    cout << "Device Added (bus: " << busname <<",  port: "<< port << ")" << endl;
    //printAboutData(const_cast<HaeAboutData&>(data), "en", 2);

    FoundDeviceInfo info(busname, port, const_cast<HaeAboutData&>(data), const_cast<AboutObjectDescription&>(description));
    m_deviceList[busname] = info;
}

void ControllerSample::OnDeviceRemoved(const char* busname)
{
    // printf("lost device \n");
}

void ControllerSample::OnDeviceSessionJoined(const DeviceInfoPtr& info)
{
    cout << "Device session joined (session id: "<< info->GetSessionId() << ")" << endl;

    m_deviceList[info->GetBusName()].sessionId = info->GetSessionId();

    DeviceCommands* command = new DeviceCommands(this, const_cast<DeviceInfoPtr&>(info));
    GetCurrentCommands()->RegisterChildCommands(info->GetBusName(), command);
    PushCommands(command);
}

void ControllerSample::OnDeviceSessionLost(SessionId id)
{
    cout << "Device session lost(session id: "<< id << ")" << endl;

    //sessionId info of FoundDeviceInfo object in g_deviceList should be updated.
}

FoundDeviceInfo* ControllerSample::GetFoundDeviceInfo(int index)
{
    FoundDeviceMap::iterator itr = m_deviceList.begin();
    while (index != 1 && itr != m_deviceList.end()) {
        ++itr;
        --index;
    }
    if (itr != m_deviceList.end()) {
        return &(itr->second);
    }
    return 0;
}

HaeInterface* ControllerSample::CreateInterface(const HaeInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener)
{
    return m_controller->CreateInterface(type, busName, objectPath, sessionId, listener);
}
