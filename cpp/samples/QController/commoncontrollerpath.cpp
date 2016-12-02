#include "commoncontrollerimpl.h"
#include <qcc/Log.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>

//------------------------------------------------------------
// CommonControllerInterface
//------------------------------------------------------------

CommonControllerPath::CommonControllerPath(CommonControllerDevice *parent, const char* pathname, const std::vector<const char*>& interfaces) : device(parent), pathname(pathname)
{
    for (size_t i=0; i<interfaces.size(); i++)
    {
        children.push_back(new CommonControllerInterface(this, interfaces[i]));
    }
}

CommonControllerPath::~CommonControllerPath()
{
}

QString CommonControllerPath::name() const
{
    return pathname.c_str();
}
