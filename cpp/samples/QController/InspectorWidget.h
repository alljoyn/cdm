#ifndef QCONTROLLER_INSPECTORWIDGET_H
#define QCONTROLLER_INSPECTORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QItemSelection>
#include <map>

#include "commoncontrollerimpl.h"
#include "qcTypes.h"

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    InspectorWidget(QWidget* parent = 0);
    ~InspectorWidget();

public slots:
    void deviceSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    void generateUi();
    void generateUi(CommonControllerDevice *);
    void generateUi(CommonControllerInterface *);
    void generateUi(CommonControllerPath *);

    typedef std::map<CommonControllerInterface*, QWidget*>  IfaceMap;
    typedef std::map<CommonControllerPath*, QWidget*>  PathMap;
    typedef std::map<CommonControllerDevice*, QWidget*>  DeviceMap;

    QBoxLayout* layout_;

    Mutex       devMutex_;
    DeviceMap   devices_;

    Mutex       pathMutex_;
    PathMap     paths_;

    Mutex       ifaceMutex_;
    IfaceMap    interfaces_;            // the actual interface widget

    Mutex       wrapMutex_;
    IfaceMap    wrappers_;              // widget that wraps the interface object

    Mutex       emptyMutex_;
    QWidget*    empty_;

    QWidget* getWidgetFromInterfaceName(CommonControllerInterface* iface);

    void    hideAll();
};

#endif //QCONTROLLER_INSPECTORWIDGET_H
