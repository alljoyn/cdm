#ifndef QCONTROLLER_LOGMODEL_H
#define QCONTROLLER_LOGMODEL_H

#include <QDebug>
#include <QAbstractListModel>
#include <qcc/Debug.h>
#include <mutex>


class AJLogHandler : public QObject
{
    Q_OBJECT
public:
    AJLogHandler(QObject *parent);
    virtual ~AJLogHandler();

    // For handling messages from AllJoyn (QCC)
    static void ajCallback(DbgMsgType type, const char* module, const char* message, void* context);
    void ajHandler(DbgMsgType type, const char* module, const char* message);

signals:
    void logReceived(const QString &type, const QString &module, const QString &message);

private:
    static AJLogHandler *s_handler;
};

class LogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    LogModel(size_t max = 1024);
    ~LogModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parents) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public slots:
    void logEntry(const QString &type, const QString &module, const QString &message);

private:

    struct LogEntry
    {
        QString type;
        QString module;
        QString message;
    };
    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> LockGuard;

    std::vector<LogEntry> entries;
    const size_t maxSize;
    size_t startIndex;
    mutable Mutex mutex;
};

#endif //QCONTROLLER_LOGMODEL_H
