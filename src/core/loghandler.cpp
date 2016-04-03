#include <iostream>
#include "loghandler.h"

LogHandler* LogHandler::instance = nullptr;

LogHandler::LogHandler(QObject *parent) : QObject(parent)
{
}

LogHandler* LogHandler::getInstance()
{
    if (instance == nullptr) {
        instance = new LogHandler();
    }

    return instance;
}

void LogHandler::log(const QString &msg)
{
    logMessage(msg);
}

void LogHandler::log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    logMessage(qFormatLogMessage(type, context, msg));
}

void LogHandler::logMessage(const QString &msg)
{
    std::cerr << msg.toStdString() << std::endl;
    emit message(msg);
}

void LogHandler::handle(const QString &msg)
{
    getInstance()->log(msg);
}

void LogHandler::handle(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    getInstance()->log(type, context, msg);
}
