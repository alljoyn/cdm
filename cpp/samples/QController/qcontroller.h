#ifndef QCONTROLLER_H
#define QCONTROLLER_H

#include <QtGlobal>
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QItemSelection>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include "commoncontrollermodel.h"
#include "commoncontrollerimpl.h"

class QController : public QMainWindow
{
    Q_OBJECT

public:
    explicit QController(QWidget *parent = 0);
    ~QController();

public slots:
    void logScrollToBottom();

private:
    QTableView* logView;
};

#endif // QCONTROLLER_H
