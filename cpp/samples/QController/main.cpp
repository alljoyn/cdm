#include "qcontroller.h"
#include <QApplication>
#include <QCommandLineParser>

#include <interfaces/common/operation/AlertsInterface.h>
#include <iostream>

using namespace std;

// Global command line options
bool QControllerDebugLog = false;


Q_DECLARE_METATYPE(Ref<ajn::services::DeviceInfo>)
Q_DECLARE_METATYPE(QStatus)
Q_DECLARE_METATYPE(uint8_t)
Q_DECLARE_METATYPE(uint16_t)
Q_DECLARE_METATYPE(int16_t)
Q_DECLARE_METATYPE(uint32_t)
Q_DECLARE_METATYPE(int32_t)
Q_DECLARE_METATYPE(uint64_t)
Q_DECLARE_METATYPE(int64_t)
Q_DECLARE_METATYPE(qcc::String)


static const char* DefaultStyle =
"#alertsList {\n"
"   background-color: white;\n"
"   border: 1px solid;\n"
"   padding: 2px;\n"
"   }\n"
".alertDescription { margin-left: 5px; margin-right: 5px; }\n"
"*[severity=\"2\"]{ background-color: red }\n"
"*[severity=\"1\"]{ background-color: orange }\n"
;


int main(int argc, char *argv[])
{
    qRegisterMetaType<Ref<ajn::services::DeviceInfo>>();
    qRegisterMetaType<QStatus>("QStatus");
    qRegisterMetaType<uint8_t>("uint8_t");
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<int16_t>("int16_t");
    qRegisterMetaType<uint32_t>("uint32_t");
    qRegisterMetaType<int32_t>("int32_t");
    qRegisterMetaType<uint64_t>("uint64_t");
    qRegisterMetaType<int64_t>("int64_t");
    qRegisterMetaType<qcc::String>();

    QApplication a(argc, argv);

    QCommandLineParser argParser;

    argParser.addOptions({
        {"D", "Show debugging messages on stdout, not in the GUI"}
        });

    argParser.process(a.arguments());

    QControllerDebugLog = argParser.isSet("D");

    if (a.styleSheet().isEmpty())
    {
        a.setStyleSheet(DefaultStyle);
    }

    QController w;
    w.show();

    return a.exec();
}
