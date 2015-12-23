#include "ControlleeSample.h"
#include "ControlleeCommands.h"

using namespace std;
using namespace ajn;
using namespace services;

#define ABOUT_SESSION_PORT 900

ControlleeSample::ControlleeSample(BusAttachment* bus, HaeAboutData* aboutData)
  : m_bus(bus), m_aboutData(aboutData), m_aboutObj(NULL), m_aboutSessionListener(NULL),
    m_controllee(NULL), m_rootCommands(NULL)
{
}

ControlleeSample::~ControlleeSample()
{
}

QStatus ControlleeSample::Init()
{
    QStatus status = ER_OK;

    if (!m_bus) {
        status = ER_FAIL;
        printf("m_bus is NULL. (%s)\n", QCC_StatusText(status));
        return status;
    }

    if (!m_aboutData) {
        status = ER_FAIL;
        printf("m_aboutData is NULL. (%s)\n", QCC_StatusText(status));
        return status;
    }

    m_controllee = new HaeControllee(*m_bus, m_aboutData);
    if (!m_controllee) {
        status = ER_OUT_OF_MEMORY;
        printf("HaeControllee creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }
    m_rootCommands = new ControlleeCommands(this);
    if (!m_rootCommands) {
        status = ER_OUT_OF_MEMORY;
        printf("ControlleeCommands creation failed. (%s)\n", QCC_StatusText(status));
        delete m_controllee;
        return status;
    }
    PushCommands(m_rootCommands);

    InitSample();

    CreateInterfaces();

    m_controllee->Start();

    SetInitialProperty();

    status = AnnounceAboutObj();
    if (status != ER_OK){
        printf("AnnounceAboutObj failed. (%s)\n", QCC_StatusText(status));
        delete m_controllee;
        return status;
    }

    return status;
}

void ControlleeSample::Deinit()
{
    m_controllee->Stop();
    if (m_controllee) {
        delete m_controllee;
        m_controllee = 0;
    }

    UnannounceAboutObj();

    if (m_rootCommands) {
        delete m_rootCommands;
        m_rootCommands = 0;
    }
}

QStatus ControlleeSample::AnnounceAboutObj()
{
    QStatus status = ER_OK;

    if (!m_bus) {
        status = ER_FAIL;
        printf("bus is NULL. (%s)", QCC_StatusText(status));
        return status;
    }

    m_aboutSessionListener = new AboutSessionListener();
    if (!m_aboutSessionListener) {
        status = ER_OUT_OF_MEMORY;
        printf("SessionPortListener creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }
    SessionPort port = ABOUT_SESSION_PORT;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    status = m_bus->BindSessionPort(port, opts, *m_aboutSessionListener);
    if (status != ER_OK) {
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;
        printf("BindSessionPort failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    m_aboutObj = new AboutObj(*m_bus, BusObject::ANNOUNCED);
    if (!m_aboutObj) {
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;
        printf("About Object creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    status = m_aboutObj->Announce(ABOUT_SESSION_PORT, *m_aboutData);
    if (status != ER_OK) {
        delete m_aboutObj;
        m_aboutObj = NULL;
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;
        printf("About announcement failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    return status;
}

void ControlleeSample::UnannounceAboutObj()
{
    if (m_aboutObj) {
        m_aboutObj->Unannounce();
        delete m_aboutObj;
        m_aboutObj = NULL;
    }

    if (m_bus) {
        m_bus->UnbindSessionPort(ABOUT_SESSION_PORT);
    }

    if (m_aboutSessionListener) {
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;

    }
}
