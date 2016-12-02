#ifndef COMMONCONTROLLERROOT_H
#define COMMONCONTROLLERROOT_H

#include "commoncontrollermodel.h"
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/CdmController.h>
#include <alljoyn/cdm/common/DeviceListener.h>

#include <set>
#include <mutex>

using ajn::services::Ref;


class CommonControllerRoot;
class CommonControllerDevice;
class CommonControllerPath;
class CommonControllerInterface;

class CommonControllerRoot final : public CommonControllerChildrenNode<CommonControllerDevice*>, public ajn::services::DeviceListener {
    Q_OBJECT
public:
    CommonControllerRoot(CommonControllerModel *model);
    ~CommonControllerRoot();

    // CommonControllerNode:
    CommonControllerNode *parent() const override { return NULL; }
    QString name() const override;

    // DeviceListener:
    void OnDeviceAdded(const char* busname, ajn::SessionPort port, const ajn::services::CdmAboutData& data, const ajn::AboutObjectDescription& description) override;
    void OnDeviceRemoved(const char* busname) override;
    void OnDeviceSessionJoined(const Ref<ajn::services::DeviceInfo> info) override;
    void OnDeviceSessionLost(ajn::SessionId sessionId) override;

    ajn::services::CdmController* getController() const { return controller; }

public slots:
    void addSession(Ref<ajn::services::DeviceInfo> info);
    void removeSession(unsigned int sessionId);

private:
    ajn::services::CdmController* controller;
    ajn::BusAttachment* bus;
    CommonControllerModel *model;
};

class CommonControllerDevice : public CommonControllerChildrenNode<CommonControllerPath*> {
    Q_OBJECT
public:

    CommonControllerDevice(CommonControllerRoot *parent, Ref<ajn::services::DeviceInfo> device_info);
    ~CommonControllerDevice();

    // CommonControllerNode:
    CommonControllerNode *parent() const override { return root; }
    QString name() const override;

    Ref<ajn::services::DeviceInfo> getDeviceInfo() const { return device_info; };
    ajn::services::CdmController* getController() const { return root->getController(); }


private:
    CommonControllerRoot *root;
    Ref<ajn::services::DeviceInfo> device_info;
};

class CommonControllerPath : public CommonControllerChildrenNode<CommonControllerInterface*> {
    Q_OBJECT
public:

    CommonControllerPath(CommonControllerDevice *parent, const char* pathname, const std::vector<const char*>& interfaces);
    ~CommonControllerPath();

    // CommonControllerNode:
    CommonControllerNode *parent() const override { return device; }
    QString name() const override;
    const std::string& getObjectPath() const { return pathname; }

    CommonControllerDevice *getDevice() const { return device; }

private:
    CommonControllerDevice *device;
    std::string pathname;
};


class CommonControllerInterface : public CommonControllerChildlessNode {
    Q_OBJECT
public:

    CommonControllerInterface(CommonControllerPath *parent, const std::string &interfacename);
    ~CommonControllerInterface();

    // CommonControllerNode:
    CommonControllerNode *parent() const override { return path; }
    QString name() const override;

    const std::string& getBusName() const { return path->getDevice()->getDeviceInfo()->GetBusName(); }
    const std::string& getObjectPath() const { return path->getObjectPath(); }
    ajn::SessionId getSessionId() const { return path->getDevice()->getDeviceInfo()->GetSessionId(); }

    template<typename T>
    std::shared_ptr<T> CreateInterface(Ref<ajn::services::InterfaceControllerListener> listener)
    {
        return path->getDevice()->getController()->CreateInterface<T>(
            path->getDevice()->getDeviceInfo()->GetBusName(),
            path->getObjectPath(),
            path->getDevice()->getDeviceInfo()->GetSessionId(),
            listener);
    }


private:
    CommonControllerPath *path;
    std::string interface;
};



#endif // COMMONCONTROLLERROOT_H
