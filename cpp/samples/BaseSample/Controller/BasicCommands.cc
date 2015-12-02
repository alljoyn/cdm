#include "BasicCommands.h"
#include "ControllerSample.h"

BasicControllerCommands::BasicControllerCommands(ControllerSample* sample)
: ControllerCommands(sample)
{
}

BasicControllerCommands::~BasicControllerCommands()
{
}

void BasicControllerCommands::Init()
{
    RegisterCommand(&BasicControllerCommands::OnCmdDeviceList, "dl", "show device list");
    RegisterCommand(&BasicControllerCommands::OnCmdDeviceInfo, "di", "show device info");
    RegisterCommand(&BasicControllerCommands::OnCmdDeviceJoin, "sd", "select device(join)");
}

void BasicControllerCommands::OnCmdDeviceList(Commands* commands, std::string& cmd)
{
    ControllerSample* sample = static_cast<ControllerCommands*>(commands)->GetControllerSample();
    FoundDeviceMap& map = sample->GetDeviceMap();
    FoundDeviceMap::iterator itr = map.begin();
    int count = 0;
    while (itr != map.end()) {
        FoundDeviceInfo& info = itr->second;
        cout << ++count << ": " << info.deviceName << " (" << info.busName << ")" << endl;
        ++itr;
    }
}

void BasicControllerCommands::OnCmdDeviceInfo(Commands* commands, std::string& cmd)
{

}

void BasicControllerCommands::OnCmdDeviceJoin(Commands* commands, std::string& cmd)
{
    BasicControllerCommands::OnCmdDeviceList(commands, cmd);
    int index = ReadIndex();

    ControllerSample* sample = static_cast<ControllerCommands*>(commands)->GetControllerSample();
    FoundDeviceInfo* info = sample->GetFoundDeviceInfo(index);
    if (!info) {
        return;
    }
    cout << "selected device: " << info->deviceName << " (" << info->busName << ")" << endl;
    Commands* child = commands->GetChild(info->busName);
    if (child) {
        sample->PushCommands(child);
    }
    else {
         QStatus status = sample->GetController()->JoinDevice(info->busName,
                info->sessionPort, info->aboutData, info->aboutObjectDescription);
        if (ER_OK != status) {
            cout << "Session joining is failed." << endl;
        }
  }
}

