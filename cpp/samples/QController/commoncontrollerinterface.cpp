#include "commoncontrollerimpl.h"
#include <qcc/Log.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>

//------------------------------------------------------------
// CommonControllerInterface
//------------------------------------------------------------

CommonControllerInterface::CommonControllerInterface(CommonControllerPath *parent, const std::string &interface) : path(parent), interface(interface)
{
}

CommonControllerInterface::~CommonControllerInterface()
{
}

QString CommonControllerInterface::name() const
{
    return interface.c_str();
}
