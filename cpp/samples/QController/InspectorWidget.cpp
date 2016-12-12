#include <QLabel>
#include "InspectorWidget.h"

/*  We don't delete interfaces that we create because we could then have
    AJ messages arriving for ProxyBusObjects that have been deleted.
    (This may well be an AJ bug).

*/


InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);
    generateUi();
}



InspectorWidget::~InspectorWidget()
{
}



void InspectorWidget::deviceSelectionChanged(const QItemSelection &updated, const QItemSelection &)
{
    hideAll();

    if (updated.indexes().isEmpty())
    {
        generateUi();
    }
    else
    {
        QModelIndex index = updated.indexes().first();
        QObject* obj = reinterpret_cast<QObject*>(index.internalPointer());

        // Fake multiple dispatch
        if (CommonControllerDevice *node = qobject_cast<CommonControllerDevice*>(obj))
        {
            generateUi(node);
        }
        else
        if (CommonControllerInterface *node = qobject_cast<CommonControllerInterface*>(obj))
        {
            generateUi(node);
        }
        else
        if (CommonControllerPath *node = qobject_cast<CommonControllerPath*>(obj))
        {
            generateUi(node);
        }
        else
        {
            generateUi();
        }
    }


}



void InspectorWidget::generateUi()
{
    LockGuard lock(emptyMutex_);

    if (!empty_)
    {
        empty_ = new QLabel("Empty");
        layout_->addWidget(empty_);
    }

    empty_->show();
}



void InspectorWidget::generateUi(CommonControllerDevice *device)
{
    LockGuard lock(devMutex_);

    auto iter = devices_.find(device);
    QWidget* box = 0;

    if (iter == devices_.end())
    {
        box = new QWidget(this);
        layout_->addWidget(box);

        auto* lay = new QVBoxLayout();
        lay->addWidget(new QLabel("Device"));
        lay->addWidget(new QLabel(device->name()));
        lay->addStretch(2);

        box->setLayout(lay);
        devices_[device] = box;
    }
    else
    {
        box = iter->second;
    }

    box->show();
}



static QWidget* createWidgetFromInterfaceName(CommonControllerInterface* iface)
{
    qRegisterMetaType<CommonControllerInterface*>();

    // Convert interface name into the class name of the expected widget
    // "com.example.MyInterface" -> "CDMQtWidgets::com_example_MyInterface"
    QString classname = "CDMQtWidgets::" + iface->name() + "*";
    classname.replace(".", "_");

    int id = QMetaType::type(classname.toUtf8().constData());
    if (id == QMetaType::UnknownType)
    {
        qInfo() << classname << ": Unknown QMetaType";
        return NULL;
    }

    const QMetaObject* meta = QMetaType::metaObjectForType(id);
    if (!meta)
    {
        qInfo() << classname << ": Failed to get QMetaObject";
        return NULL;
    }

    QObject *obj = meta->newInstance(Q_ARG(CommonControllerInterface*, iface));
    if (obj == NULL)
    {
        qInfo() << classname << ": Failed to create new instance";
        return NULL;
    }

    QWidget *widget = qobject_cast<QWidget*>(obj);
    if (widget == NULL)
    {
        delete obj;
        qInfo() << classname << ": Failed to cast to QWidget";
    }

    return widget;
}



QWidget* InspectorWidget::getWidgetFromInterfaceName(CommonControllerInterface* iface)
{
    // See if we already have a widget for this interface object.
    LockGuard lock(ifaceMutex_);
    auto iter = interfaces_.find(iface);

    if (iter != interfaces_.end())
    {
        return iter->second;
    }

    auto w = createWidgetFromInterfaceName(iface);
    interfaces_[iface] = w;
    return w;
}



void InspectorWidget::generateUi(CommonControllerPath *path)
{
    LockGuard lock(pathMutex_);

    QWidget* box = 0;
    auto iter = paths_.find(path);

    if (iter == paths_.end())
    {
        box = new QWidget(this);
        layout_->addWidget(box);

        auto* lay = new QVBoxLayout();
        lay->addWidget(new QLabel("Path"));
        lay->addWidget(new QLabel(QString::fromStdString(path->getObjectPath())));
        lay->addStretch(2);
#if 0 
        /*  This attempted to show all interfaces. But it ended up transferring the interface widgets
            from the other boxes to this box!
        */
        for (int i = 0; i < path->childCount(); i++)
        {
            CommonControllerNode* child = path->child(i);

            if (auto* iface = qobject_cast<CommonControllerInterface*>(child))
            {
                if (i > 0)
                {
                    lay->addStretch(2);
                }

                lay->addWidget(new QLabel(iface->name()));

                if (auto* widget = getWidgetFromInterfaceName(iface))
                {
                    lay->addWidget(widget);
                }
            }
        }
#endif

        box->setLayout(lay);
        paths_[path] = box;
    }
    else
    {
        box = iter->second;
    }

    box->show();
}




void InspectorWidget::generateUi(CommonControllerInterface *iface)
{
    LockGuard lock(wrapMutex_);

    QWidget* box = 0;
    auto iter = wrappers_.find(iface);

    if (iter == wrappers_.end())
    {
        box = new QWidget(this);
        layout_->addWidget(box);

        auto* lay = new QVBoxLayout(box);
        lay->addWidget(new QLabel("Interface"));
        lay->addWidget(new QLabel(iface->name()));
        lay->addStretch(2);

        if (auto* widget = getWidgetFromInterfaceName(iface))
        {
            lay->addWidget(widget);
        }

        box->setLayout(lay);
        wrappers_[iface] = box;
    }
    else
    {
        box = iter->second;
    }

    box->show();
}



void InspectorWidget::hideAll()
{
    for (auto& c : children())
    {
        if (auto* widget = qobject_cast<QWidget*>(c))
        {
            widget->hide();
        }
    }
}