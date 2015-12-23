#include <iomanip>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/hae/HaeAboutData.h>
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
    BasicControllerCommands::OnCmdDeviceList(commands, cmd);
    int index = ReadIndex();

    ControllerSample* sample = static_cast<ControllerCommands*>(commands)->GetControllerSample();
    FoundDeviceInfo* info = sample->GetFoundDeviceInfo(index);
    if (!info) {
        return;
    }
    cout << "selected device: " << info->deviceName << " (" << info->busName << ")" << endl;
    PrintAboutData(info->aboutData);
    PrintAboutObjectDescription(info->aboutObjectDescription);
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
    } else {
        QStatus status = sample->GetController()->JoinDevice(info->busName,
                info->sessionPort, info->aboutData, info->aboutObjectDescription);
        if (ER_OK != status) {
            cout << "Session joining is failed." << endl;
        }
    }
}

void BasicControllerCommands::PrintAboutData(ajn::services::HaeAboutData& aboutData)
{
    cout << "About Data" << endl;
    size_t count = aboutData.GetFields();
    const char** fields = new const char*[count];
    aboutData.GetFields(fields, count);
    for (size_t i = 0; i < count; ++i) {
        cout << "\tKey: " << fields[i];

        MsgArg* tmp;
        aboutData.GetField(fields[i], tmp);
        cout << "\t";
        if (tmp->Signature() == "s") {
            const char* tmp_s;
            tmp->Get("s", &tmp_s);
            cout << tmp_s;
        } else if (tmp->Signature() == "as") {
            size_t las;
            MsgArg* as_arg;
            tmp->Get("as", &las, &as_arg);
            for (size_t j = 0; j < las; ++j) {
                const char* tmp_s;
                as_arg[j].Get("s", &tmp_s);
                cout << tmp_s;
            }
        } else if (tmp->Signature() == "ay") {
            size_t lay;
            uint8_t* pay;
            tmp->Get("ay", &lay, &pay);
            for (size_t j = 0; j < lay; ++j) {
                cout << hex << setfill('0') << setw(2) << (int)pay[j] << " ";
            }
            cout << dec;
        } else if (tmp->Signature() == "a(uo)") {
            MsgArg* elemArg = NULL;
            size_t elemSize = 0;
            tmp->Get("a(uo)", &elemSize, &elemArg);

            for(size_t i = 0; i < elemSize; ++i) {
                DeviceType type;
                char* objectPath = NULL;

                elemArg[i].Get("(uo)", &type, &objectPath);
                cout << "[" << type << ", " << objectPath << "]";
            }
        } else {
            cout << "User Defined Value\tSignature: " << tmp->Signature().c_str();
        }
        cout << endl;
    }
    delete [] fields;
}

void BasicControllerCommands::PrintAboutObjectDescription(ajn::AboutObjectDescription& aboutObjectDesc)
{
    cout << "About Object Description" << endl;
    size_t path_num = aboutObjectDesc.GetPaths(NULL, 0);
    const char** paths = new const char*[path_num];
    aboutObjectDesc.GetPaths(paths, path_num);
    for (size_t i = 0; i < path_num; ++i) {
        size_t intf_num = aboutObjectDesc.GetInterfaces(paths[i], NULL, 0);
        const char** intfs = new const char*[intf_num];
        aboutObjectDesc.GetInterfaces(paths[i], intfs, intf_num);
        cout << "\t" << paths[i] << " :" << endl;
        for (size_t j = 0; j < intf_num; ++j) {
            cout << "\t\t" << intfs[j] << endl;
        }
        delete [] intfs;
    }
    delete [] paths;
}
