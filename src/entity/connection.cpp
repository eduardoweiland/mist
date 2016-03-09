#include "connection.h"

Connection::Connection()
{
}

Connection::Connection(const Connection &connection)
{
    displayName = connection.getDisplayName();
    hostName = connection.getHostName();
    portNumber = connection.getPortNumber();
    userName = connection.getUserName();
    password = connection.getPassword();
    database = connection.getDatabase();
}

Connection::~Connection()
{
}

QString Connection::getDisplayName() const
{
    return displayName;
}

void Connection::setDisplayName(const QString &value)
{
    displayName = value;
}

QString Connection::getHostName() const
{
    return hostName;
}

void Connection::setHostName(const QString &value)
{
    hostName = value;
}

int Connection::getPortNumber() const
{
    return portNumber;
}

void Connection::setPortNumber(int value)
{
    portNumber = value;
}

QString Connection::getUserName() const
{
    return userName;
}

void Connection::setUserName(const QString &value)
{
    userName = value;
}

QString Connection::getPassword() const
{
    return password;
}

void Connection::setPassword(const QString &value)
{
    password = value;
}

QString Connection::getDatabase() const
{
    return database;
}

void Connection::setDatabase(const QString &value)
{
    database = value;
}
