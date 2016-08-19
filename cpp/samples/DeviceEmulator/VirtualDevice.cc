#include "VirtualDevice.h"
#include "../BaseSample/Controllee/CommandsFactory.h"
#include "BasicCommands.h"

using namespace ajn;
using namespace services;

VirtualDevice::VirtualDevice(BusAttachment* bus, CdmAboutData* aboutData, InterfaceList* list)
: ControlleeSample(bus, aboutData)
, m_interfaceList(list)
{
}

VirtualDevice::~VirtualDevice()
{
}

void VirtualDevice::InitSample()
{
    m_rootCommands = new BasicCommands(this);
    if (!m_rootCommands) {
        printf("ControlleeCommands creation failed.\n");
        delete m_controllee;
    }
    PushCommands(m_rootCommands);
}

void VirtualDevice::CreateInterfaces()
{
    CommandsFactory* factory = CommandsFactory::GetInstance();
    for (InterfaceList::iterator itr = m_interfaceList->begin(); itr != m_interfaceList->end(); ++itr) {
        ControlleeCommands* commands = factory->CreateCommands(itr->first, this, itr->second.c_str());
        if (commands) {
            char buf[1024];
            sprintf(buf, "%u:%s", itr->first, itr->second.c_str());
            string key(buf);
            m_rootCommands->RegisterChildCommands(key, commands);
            commands->Init();
        }
    }
}

void VirtualDevice::SetInitialProperty()
{
    if (m_rootCommands) {
        static_cast<ControlleeCommands*>(m_rootCommands)->InitializeProperties();
    }
}

InterfaceList* VirtualDevice::GetInterfaceList()
{
    return m_interfaceList;
}
