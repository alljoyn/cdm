#ifndef COMMONCONTROLLERMODEL_H
#define COMMONCONTROLLERMODEL_H

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QtDebug>

#include "qcTypes.h"

class CommonControllerNode : public QObject {
    Q_OBJECT
public:
    virtual ~CommonControllerNode() {}
    virtual CommonControllerNode *parent() const = 0;
    virtual int childIndex(const CommonControllerNode *child) const = 0;
    virtual int childCount() const = 0;
    virtual CommonControllerNode *child(int row) const = 0;
    virtual QString name() const = 0;

};

class CommonControllerChildlessNode : public CommonControllerNode {
    Q_OBJECT
public:
    int childIndex(const CommonControllerNode *) const override final
    {
        return 0;
    }

    int childCount() const override final
    {
        return 0;
    }

    virtual CommonControllerNode *child(int) const override final
    {
        return NULL;
    }
};

template<typename T>
class CommonControllerChildrenNode : public CommonControllerNode {
public:
    int childIndex(const CommonControllerNode *child) const override final
    {
        LockGuard lock(childrenMutex);
        for (size_t i=0; i<children.size(); i++)
        {
            if (children[i] == child) {
                return i;
            }
        }
        return 0;
    }

    int childCount() const override final
    {
        LockGuard lock(childrenMutex);
        return children.size();
    }

    virtual CommonControllerNode *child(int row) const override final
    {
        LockGuard lock(childrenMutex);
        if (row<0 || row>=children.size())
        {
            return NULL;
        }
        return children[row];
    }

protected:
    std::vector<T> children;
    mutable Mutex childrenMutex;
};


class CommonControllerModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit CommonControllerModel(QAbstractItemView *view);
    virtual ~CommonControllerModel();
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex nodeToIndex(CommonControllerNode *node) const;

    void beginInsertChild(CommonControllerNode *node, int index)
    {
        beginInsertRows(nodeToIndex(node), index, index);
    }

    void endInsertChild()
    {
        endInsertRows();
        view->reset();
    }

    void beginRemoveChild(CommonControllerNode *node, int index)
    {
        beginRemoveRows(nodeToIndex(node), index, index);
    }

    void endRemoveChild()
    {
        endRemoveRows();
        view->reset();
    }

private:
    QAbstractItemView *view;
    CommonControllerNode *root;
};



#endif // COMMONCONTROLLERMODEL_H
