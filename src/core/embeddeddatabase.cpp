#include <stdlib.h>
#include <string.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "embeddeddatabase.h"

MYSQL *EmbeddedDatabase::mysql = nullptr;
bool EmbeddedDatabase::libraryInitialized = false;

EmbeddedDatabase::EmbeddedDatabase()
{
    if (!libraryInitialized) {
        QDir::home().mkpath(".mist/data");

        QString datadir = QDir(QDir::homePath() + "/.mist/data").absolutePath();
        char *datadirArg = strdup(QString("--datadir=%1").arg(datadir).toStdString().c_str());

        static const char *argv[] = {
            "mist",
            "--character-set-server=utf8",
            "--collation-server=utf8_bin",
            datadirArg,
            NULL
        };

        int argc = (sizeof(argv) / sizeof(char *)) - 1;

        qInfo() << QCoreApplication::tr("Initializing MySQL library");
        if (mysql_library_init(argc, (char**)argv, NULL) != 0) {
            qCritical() << QCoreApplication::tr("Could not initialize MySQL library");
        }
        else {
            libraryInitialized = true;
            qInfo() << QCoreApplication::tr("MySQL library successfully initialized");
        }

        free(datadirArg);
    }
}

EmbeddedDatabase::~EmbeddedDatabase()
{
    if (mysql == nullptr) {
        qDebug() << QCoreApplication::tr("MySQL Server is not running, cleaning up library");
        mysql_library_end();
    }
}

void EmbeddedDatabase::start()
{
    qInfo() << QCoreApplication::tr("Starting MySQL server");

    if (mysql == nullptr) {
        mysql = mysql_init(NULL);
        mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "mist_embedded_server");
        mysql_options(mysql, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);
    }
}

void EmbeddedDatabase::stop()
{
    if (mysql != nullptr) {
        mysql_close(mysql);
        mysql = nullptr;
    }

    qInfo() << QCoreApplication::tr("MySQL server stopped");
}

bool EmbeddedDatabase::connect(const char *database)
{
    qInfo() << QCoreApplication::tr("Connecting to database %1").arg(database);

    if (mysql_real_connect(mysql, NULL, NULL, NULL, database, 0, NULL, 0) == NULL) {
        return false;
    }
    else {
        return true;
    }
}
