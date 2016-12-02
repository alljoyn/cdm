#include <alljoyn/Init.h>
#include "LogModel.h"
#include <QSize>
#include <qcc/Log.h>
#include <QCoreApplication>

AJLogHandler *AJLogHandler::s_handler = NULL;

AJLogHandler::AJLogHandler(QObject *parent) : QObject(parent)
{
    if (s_handler == NULL)
    {
        QStatus status = AllJoynInit();
        if (status != ER_OK) {
            qCritical() << "Failed to initialize alljoyn! " << status;
            return;
        }
        QCC_RegisterOutputCallback(ajCallback, NULL);
        //QCC_SetDebugLevel("ALL", 1);
        s_handler = this;
    }
}


AJLogHandler::~AJLogHandler()
{
    if (s_handler == this)
    {
        s_handler = NULL;
        AllJoynShutdown();
    }
}

void AJLogHandler::ajCallback(DbgMsgType type, const char* module, const char* message, void* context)
{
    if (s_handler != NULL)
    {
        s_handler->ajHandler(type, module, message);
    }
}

void AJLogHandler::ajHandler(DbgMsgType type, const char* module, const char* message)
{
    const char *typeStr = NULL;
    switch (type)
    {
        case DBG_LOCAL_ERROR:  typeStr = "LOCAL_ERROR"; break;
        case DBG_REMOTE_ERROR: typeStr = "REMOTE_ERROR"; break;
        case DBG_HIGH_LEVEL:   typeStr = "HIGH_LEVEL"; break;
        case DBG_GEN_MESSAGE:  typeStr = "GEN_MESSAGE"; break;
        case DBG_API_TRACE:    typeStr = "API_TRACE"; break;
        case DBG_REMOTE_DATA:  typeStr = "REMOTE_DATA"; break;
        case DBG_LOCAL_DATA:   typeStr = "LOCAL_DATA"; break;
        default: typeStr = "UNKNOWN";
    }
    emit logReceived(typeStr, module, message);

    if (type==DBG_LOCAL_ERROR || type==DBG_REMOTE_ERROR)
    {
        fputs(message, stderr);
    }
}


LogModel::LogModel(size_t max) : maxSize(max)
{
    entries.reserve(max);
}

LogModel::~LogModel()
{
}

int LogModel::rowCount(const QModelIndex &parent) const
{
    LockGuard lock(mutex);
    return (int)entries.size();
}

int LogModel::columnCount(const QModelIndex &parents) const
{
    return 3;
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    LockGuard lock(mutex);

    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row()<0 || index.row()>=entries.size())
    {
        return QVariant();
    }

    size_t realIndex = (index.row() + startIndex) % entries.size();

    const LogEntry& entry = entries[realIndex];
    switch (role)
    {
        case Qt::DisplayRole:
        switch (index.column())
        {
            case 0: return entry.type;
            case 1: return entry.module;
            case 2: return entry.message;
            default: return QVariant();
        }
        default: return QVariant();
    }
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
    {
        return QVariant();
    }
    switch (role)
    {
        case Qt::DisplayRole:
        switch (section)
        {
            case 0: return "Type";
            case 1: return "Module";
            case 2: return "Message";
        }
    }
    return QVariant();
}

void LogModel::logEntry(const QString &type, const QString &module, const QString &message) {
    LockGuard lock(mutex);
    if (entries.size() < maxSize)
    {
        beginInsertRows(QModelIndex(), (int)entries.size(), (int)entries.size());
        entries.push_back(LogEntry {type, module, message});
        endInsertRows();
    }
    else
    {
        beginMoveRows(QModelIndex(), 1, (int)maxSize-1, QModelIndex(), 0);
        entries[startIndex] = LogEntry {type, module, message};
        startIndex++;
        if (startIndex >= maxSize)
        {
            startIndex = 0;
        }
        endMoveRows();
    }
}
