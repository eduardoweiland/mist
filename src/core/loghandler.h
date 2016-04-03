#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <QObject>
#include <QDebug>

class LogHandler : public QObject
{
    Q_OBJECT

public:
    static LogHandler* getInstance();

    static void handle(const QString &msg);
    static void handle(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
    void message(const QString &msg);

public slots:
    void log(const QString &msg);
    void log(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    explicit LogHandler(QObject *parent = 0);
    void logMessage(const QString &msg);

    static LogHandler *instance;
};

#endif // LOGHANDLER_H
