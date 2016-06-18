#ifndef INDEXVERIFICATION_H
#define INDEXVERIFICATION_H

#include <QList>
#include <QSqlDatabase>
#include <QThread>

#include "../entity/mistproject.h"

class IndexVerification : public QThread
{
    Q_OBJECT

public:
    IndexVerification(MistProject project, QObject *parent = nullptr);

    void run() Q_DECL_OVERRIDE;

signals:
    void resultReady();
    void progress(const int percent);
    void log(const QString msg);

private:
    MistProject m_project;
    QSqlDatabase m_db;

    void testCandidate(CandidateIndex &candidate);
    void createIndex(CandidateIndex &candidate);
    void dropIndex(CandidateIndex &candidate);

    void writeLog(QString msg);
};

#endif // INDEXVERIFICATION_H
