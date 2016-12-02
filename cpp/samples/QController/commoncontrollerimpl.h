#ifndef COMMONCONTROLLERROOT_H
#define COMMONCONTROLLERROOT_H

#include "commoncontrollermodel.h"
#include <alljoyn/cdm/CdmController.h>
#include <alljoyn/cdm/DeviceListener.h>

#include <set>
#include <mutex>


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
    void OnDeviceSessionJoined(const ajn::services::DeviceInfoPtr& info) override;
    void OnDeviceSessionLost(ajn::SessionId sessionId) override;

    ajn::services::CdmController* getController() const { return controller; }

public slots:
    void addSession(ajn::services::DeviceInfoPtr info);
    void removeSession(unsigned int sessionId);

private:
    ajn::services::CdmController* controller;
    ajn::BusAttachment* bus;
    CommonControllerModel *model;
};

class CommonControllerDevice : public CommonControllerChildrenNode<CommonControllerPath*> {
    Q_OBJECT
public:

    CommonControllerDevice(CommonControllerRoot *parent, ajn::services::DeviceInfoPtr device_info);
    ~CommonControllerDevice();

    // CommonControllerNode:
    CommonControllerNode *parent() const override { return root; }
    QString name() const override;

    ajn::services::DeviceInfoPtr getDeviceInfo() const { return device_info; };
    ajn::services::CdmController* getController() const { return root->getController(); }


private:
    CommonControllerRoot *root;
    ajn::services::DeviceInfoPtr device_info;
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
    std::shared_ptr<T> CreateInterface(ajn::services::InterfaceControllerListener& listener)
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
