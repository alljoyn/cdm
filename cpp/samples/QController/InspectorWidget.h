#ifndef QCONTROLLER_INSPECTORWIDGET_H
#define QCONTROLLER_INSPECTORWIDGET_H

#include <QWidget>
#include <QItemSelection>
#include "commoncontrollerimpl.h"

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    InspectorWidget(QWidget* parent);
    ~InspectorWidget();

public slots:
    void deviceSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    void generateUi();
    void generateUi(CommonControllerDevice *);
    void generateUi(CommonControllerInterface *);
    void generateUi(CommonControllerPath *);
};

#endif //QCONTROLLER_INSPECTORWIDGET_H
