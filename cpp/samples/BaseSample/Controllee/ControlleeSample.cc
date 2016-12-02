#include <qcc/String.h>
#include "ControlleeSample.h"
#include "ControlleeCommands.h"
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/CdmAnnouncer.h>

using namespace std;
using namespace qcc;
using namespace ajn;
using namespace services;

/////////////////////////////////////////////////////////////////////////////////////////
ControlleeSample::ControlleeSample(
    BusAttachment* bus,
    Ref<CdmAnnouncer> announcer,
    Ref<CdmSecurity> security
    )
  : m_bus(bus),
    m_announcer(announcer),
    m_security(security),
    m_controllee(NULL),
    m_rootCommands(NULL)
{
}



ControlleeSample::~ControlleeSample()
{
    Deinit();
}



CdmAboutData* ControlleeSample::GetAboutData()
{
    return m_announcer->GetAboutData().get();
}



void ControlleeSample::InitSample()
{
    m_rootCommands = new ControlleeCommands(this);
    if (!m_rootCommands) {
        printf("ControlleeCommands creation failed.\n");
        delete m_controllee;
    }
    PushCommands(m_rootCommands);
}



CdmInterface* ControlleeSample::CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener)
{
    return m_controllee->CreateInterface(type, objectPath, listener);
}



QStatus ControlleeSample::Init()
{
    QStatus status = ER_OK;

    if (!m_bus) {
        status = ER_FAIL;
        printf("m_bus is NULL. (%s)\n", QCC_StatusText(status));
        return status;
    }

    m_controllee = new CdmControllee(*m_bus, m_announcer, m_security);
    if (!m_controllee) {
        status = ER_OUT_OF_MEMORY;
        printf("CdmControllee creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }
    InitSample();

    CreateInterfaces();

    m_controllee->Start();

    SetInitialProperty();

    status = m_announcer->Announce();
    if (status != ER_OK){
        printf("AnnounceAboutObj failed. (%s)\n", QCC_StatusText(status));
        delete m_controllee;
        return status;
    }

    m_isInit = true;
    return status;
}



void ControlleeSample::Deinit()
{
    if (m_isInit) {
        if (m_controllee) {
            m_controllee->Stop();
            delete m_controllee;
            m_controllee = 0;
        }

        m_announcer->Unannounce();

        delete m_rootCommands;
        m_rootCommands = 0;
        m_isInit = false;
    }
}
