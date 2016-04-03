#ifndef EMBEDDEDDATABASE_H
#define EMBEDDEDDATABASE_H

#include <mysql.h>

class EmbeddedDatabase
{
public:
    EmbeddedDatabase();
    virtual ~EmbeddedDatabase();

    void start(void);
    void stop(void);
    bool connect(const char *database);

private:
    static MYSQL *mysql;
    static bool libraryInitialized;
};

#endif // EMBEDDEDDATABASE_H
