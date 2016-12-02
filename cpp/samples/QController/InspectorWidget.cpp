#include <QVBoxLayout>
#include <QLabel>
#include "InspectorWidget.h"

InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent) {
    generateUi();
}

InspectorWidget::~InspectorWidget() {
}

void InspectorWidget::deviceSelectionChanged(const QItemSelection &updated, const QItemSelection &) {
    qDeleteAll(children());
    delete layout();

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
            generateUi(node);
        else if (CommonControllerInterface *node = qobject_cast<CommonControllerInterface*>(obj))
            generateUi(node);
        else if (CommonControllerPath *node = qobject_cast<CommonControllerPath*>(obj))
            generateUi(node);
        else
            generateUi();
    }


}

void InspectorWidget::generateUi() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Empty"));
}

void InspectorWidget::generateUi(CommonControllerDevice *device) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Device"));
    layout->addWidget(new QLabel(device->name()));

#if 0
    const std::map<QString, QString>& fields = device->getFields();
    QTableWidget *table = new QTableWidget((int)fields.size(), 2);


    int row = 0;
    for (const auto& i: fields)
    {
        table->setItem(row, 0, new QTableWidgetItem(i.first));
        table->setItem(row, 1, new QTableWidgetItem(i.second));
        row++;
    }
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Key"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));
    table->verticalHeader()->hide();
    table->resizeColumnToContents(0);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    layout->addWidget(table);
#endif
}


static QWidget* createWidgetFromInterfaceName(const QString& interface, CommonControllerInterface* iface)
{
    qRegisterMetaType<CommonControllerInterface*>();

    // Convert interface name into the class name of the expected widget
    // "com.example.MyInterface" -> "CDMQtWidgets::com_example_MyInterface"
    QString classname = "CDMQtWidgets::" + interface + "*";
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


void InspectorWidget::generateUi(CommonControllerPath *path) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    for (int i=0; i<path->childCount(); i++) {
        CommonControllerNode* child = path->child(i);

        CommonControllerInterface *iface = qobject_cast<CommonControllerInterface*>(child);
        if (iface) {
            layout->addWidget(new QLabel(iface->name()));

            QWidget* widget = createWidgetFromInterfaceName(iface->name(), iface);
            if (widget)
            {
                layout->addWidget(widget);
            }
        }
    }
}


void InspectorWidget::generateUi(CommonControllerInterface *iface) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Interface"));
    layout->addWidget(new QLabel(iface->name()));

    QWidget* widget = createWidgetFromInterfaceName(iface->name(), iface);
    if (widget)
    {
        layout->addWidget(widget);
    }
}