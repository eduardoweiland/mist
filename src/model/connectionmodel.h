#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "../entity/connection.h"

class ConnectionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ConnectionModel(QObject *parent = 0);
    virtual ~ConnectionModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void create(Connection *connection);
    void remove(const QModelIndexList &indexes);

private:
    QList<Connection*> connectionList;

    void load();
    void save();
};

#endif // CONNECTIONMODEL_H
