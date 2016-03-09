#include <iostream>
#include <QSettings>

#include "connectionmodel.h"

ConnectionModel::ConnectionModel(QObject *parent)
    : QAbstractListModel(parent)
{
    load();
}

ConnectionModel::~ConnectionModel()
{
    qDeleteAll(connectionList);
}

int ConnectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return connectionList.size();
}

QVariant ConnectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    Connection *conn = connectionList.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            return conn->getDisplayName();
    }

    return QVariant();
}

void ConnectionModel::create(Connection *connection)
{
    beginInsertRows(QModelIndex(), connectionList.size(), connectionList.size());
    connectionList.append(connection);
    endInsertRows();
    save();
}

void ConnectionModel::remove(const QModelIndexList &indexes)
{
    foreach (const QModelIndex &index, indexes) {
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        connectionList.removeAt(index.row());
        endRemoveRows();
    }
    save();
}

void ConnectionModel::load()
{
    QSettings settings(this);
    QList<QVariant> list = settings.value("connections").toList();

    foreach (const QVariant &item, list) {
        Connection *conn = new Connection(item.value<Connection>());
        connectionList.append(conn);
    }
}

void ConnectionModel::save()
{
    QSettings settings(this);
    QList<QVariant> list;

    foreach (const Connection *conn, connectionList) {
        list.append(QVariant::fromValue<Connection>(*conn));
    }

    settings.setValue("connections", list);
}
