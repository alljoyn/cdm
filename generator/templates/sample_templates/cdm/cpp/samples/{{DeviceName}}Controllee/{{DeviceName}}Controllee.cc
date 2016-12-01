#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>

#include "ControlleeSample.h"

{{#interfaces}}
#include "{{InterfaceName}}Listener.h"
{{/interfaces}}

{{#interfaces}}
#include <alljoyn/cdm/interfaces/{{InterfaceCategory}}/{{InterfaceName}}IntfControllee.h>
{{/interfaces}}

using namespace std;
using namespace qcc;

class {{DeviceName}}Controllee : public ControlleeSample
{
private:
    {{#interfaces}}
    {{InterfaceName}}Listener* m_{{InterfaceName}}Listener;
    {{/interfaces}}

    {{#interfaces}}
    {{InterfaceName}}IntfControllee* m_{{InterfaceName}}IntfControllee;
    {{/interfaces}}

public:
    {{DeviceName}}Controllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~{{DeviceName}}Controllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

{{DeviceName}}Controllee::{{DeviceName}}Controllee(BusAttachment* bus, CdmAboutData* aboutData)
        : ControlleeSample(bus, aboutData),
          {{#interfaces}}
          m_{{InterfaceName}}Listener(NULL),
          {{/interfaces}}
          {{#interfaces}}
          m_{{InterfaceName}}IntfControllee(NULL){{^last}},{{/last}}
          {{/interfaces}}
{
    {{#interfaces}}
    m_{{InterfaceName}}Listener = new {{InterfaceName}}Listener;
    {{/interfaces}}
}

{{DeviceName}}Controllee::~{{DeviceName}}Controllee()
{
    {{#interfaces}}
    if (m_{{InterfaceName}}Listener) {
        delete m_{{InterfaceName}}Listener;
    }
    {{/interfaces}}
}

void {{DeviceName}}Controllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    {{#interfaces}}
    intf = cdmControllee->CreateInterface({{InterfaceName.upper_snake}}_INTERFACE, "/Cdm/{{DeviceName}}", *m_{{InterfaceName}}Listener);
    m_{{InterfaceName}}IntfControllee = static_cast<{{InterfaceName}}IntfControllee*>(intf);
    {{/interfaces}}
}

void {{DeviceName}}Controllee::SetInitialProperty()
{
   // Set any defaults for interface properties here
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "{{about_data.DefaultLanguage}}";
    String device_id = "{{about_data.DeviceId}}";
    String app_id = "{{about_data.AppId}}";
    String app_name = "{{about_data.AppName}}";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>(defaultLanguage, "{{about_data.DeviceName}}"));

    if (!app_id.empty()) {
        aboutData->SetAppId(app_id.c_str());
    }

    if (device_id != "") {
        aboutData->SetDeviceId(device_id.c_str());
    }

    vector<String> languages(1);
    languages[0] = defaultLanguage;

    for (size_t i = 0; i < languages.size(); i++) {
        aboutData->SetSupportedLanguage(languages[i].c_str());
    }

    if (defaultLanguage != "") {
        aboutData->SetDefaultLanguage(defaultLanguage.c_str());
    }

    if (app_name != "") {
        aboutData->SetAppName(app_name.c_str(), languages[0].c_str());
    }

    aboutData->SetModelNumber("{{about_data.ModelNumber}}");
    aboutData->SetDateOfManufacture("{{about_data.DateOfManufacture}}");
    aboutData->SetSoftwareVersion("{{about_data.SoftwareVersion}}");
    aboutData->SetHardwareVersion("{{about_data.HardwareVersion}}");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("{{about_data.DeviceName}}", defaultLanguage.c_str());
    }

    aboutData->SetDescription("{{about_data.Description}}", defaultLanguage.c_str());
    aboutData->SetManufacturer("{{about_data.Manufacturer}}", defaultLanguage.c_str());
    aboutData->SetSupportUrl("{{about_data.SupportUrl}}");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("{{about_data.CountryOfProduction}}", defaultLanguage.c_str());
    aboutData->SetCorporateBrand("{{about_data.CorporateBrand}}", defaultLanguage.c_str());
    aboutData->SetProductBrand("{{about_data.ProductBrand}}", defaultLanguage.c_str());
    aboutData->SetLocation("{{about_data.Location}}", defaultLanguage.c_str());

    DeviceTypeDescription description;
    description.AddDeviceType(static_cast<DeviceType>({{about_data.DeviceTypeDescription.data.device_type}}), "{{about_data.DeviceTypeDescription.data.object_path}}");
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
    QCC_SetLogLevels("CDM_MODULE_LOG_NAME=15;");

    BusAttachment* bus = new BusAttachment("{{DeviceName}}Controllee", true);
    if (!bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    CdmAboutData* aboutData = new CdmAboutData();
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

    {{DeviceName}}Controllee controllee(bus, aboutData);

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
