#include "qcontroller.h"
#include <QApplication>

Q_DECLARE_METATYPE(ajn::services::DeviceInfoPtr)
Q_DECLARE_METATYPE(QStatus)
Q_DECLARE_METATYPE(uint8_t)
Q_DECLARE_METATYPE(uint16_t)
Q_DECLARE_METATYPE(int16_t)
Q_DECLARE_METATYPE(uint32_t)
Q_DECLARE_METATYPE(int32_t)
Q_DECLARE_METATYPE(uint64_t)
Q_DECLARE_METATYPE(int64_t)
Q_DECLARE_METATYPE(qcc::String)


int main(int argc, char *argv[])
{
    qRegisterMetaType<ajn::services::DeviceInfoPtr>();
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
    QController w;
    w.show();

    return a.exec();
}
