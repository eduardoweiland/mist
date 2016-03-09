#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QMetaType>

class Connection
{
public:
    Connection();
    Connection(const Connection &connection);
    virtual ~Connection();

    QString getDisplayName() const;
    void setDisplayName(const QString &value);

    QString getHostName() const;
    void setHostName(const QString &value);

    int getPortNumber() const;
    void setPortNumber(int value);

    QString getUserName() const;
    void setUserName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getDatabase() const;
    void setDatabase(const QString &value);

private:
    QString displayName;
    QString hostName;
    int portNumber;
    QString userName;
    QString password;
    QString database;

    friend QDataStream& operator << (QDataStream& out, const Connection& value) {
        out << value.displayName
            << value.hostName
            << QString::number(value.portNumber)
            << value.userName
            << value.password
            << value.database;

        return out;
    }

    friend QDataStream& operator >> (QDataStream& in, Connection& value) {
        QString portNumber;

        in  >> value.displayName
            >> value.hostName
            >> portNumber
            >> value.userName
            >> value.password
            >> value.database;

        value.portNumber = portNumber.toInt();

        return in;
    }
};

Q_DECLARE_METATYPE(Connection)
QDataStream& operator << (QDataStream& out, const Connection& value);
QDataStream& operator >> (QDataStream& in, Connection& value);

#endif // CONNECTION_H
