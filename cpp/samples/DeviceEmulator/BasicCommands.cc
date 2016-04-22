#include <iomanip>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/hae/HaeAboutData.h>
#include "BasicCommands.h"
#include "ControlleeSample.h"
#include "VirtualDevice.h"

BasicCommands::BasicCommands(ControlleeSample* sample)
: ControlleeCommands(sample)
{
}

BasicCommands::~BasicCommands()
{
}

void BasicCommands::Init()
{
    RegisterCommand(&BasicCommands::OnCmdDeviceInfo, "di", "show device info");
    RegisterCommand(&BasicCommands::OnCmdSelectInterface, "si", "select interface");
}

void BasicCommands::OnCmdDeviceInfo(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();

    if (sample) {
        PrintAboutData(*(sample->GetAboutData()));
    }
}

void BasicCommands::OnCmdSelectInterface(Commands* commands, std::string& cmd)
{
    VirtualDevice* device = static_cast<VirtualDevice*>(static_cast<ControlleeCommands*>(commands)->GetControlleeSample());

    if (device) {
        InterfaceList* list = device->GetInterfaceList();

        if (list) {
            string objPath;
            int count = 0;

            for(InterfaceList::const_iterator citr = list->begin(); citr != list->end(); ++citr) {
                if (citr->second != objPath) {
                    cout << citr->second << endl;
                    objPath = citr->second;
                }
                cout << ++count << " : " << HaeInterface::GetInterfaceName(citr->first) << endl;
            }

            int index = ReadIndex();
            char buf[1024];
            pair<HaeInterfaceType, string> intf = list->at(index-1);
            sprintf(buf, "%u:%s", intf.first, intf.second.c_str());
            string key(buf);
            Commands* selected = device->GetCurrentCommands()->GetChild(key);
            device->PushCommands(selected);
        }
    }
}


void BasicCommands::PrintAboutData(ajn::services::HaeAboutData& aboutData)
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

void BasicCommands::PrintAboutObjectDescription(ajn::AboutObjectDescription& aboutObjectDesc)
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
