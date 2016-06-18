#include <QSqlQuery>
#include <QSqlError>

#include "indexverification.h"

IndexVerification::IndexVerification(MistProject project, QObject *parent) :
    QThread(parent), m_project(project)
{
    m_db = QSqlDatabase::database();
}

void IndexVerification::run()
{
    QList<CandidateIndex> candidates = m_project.getCandidates();
    int i = 1, size = candidates.size();

    foreach (CandidateIndex ci, candidates) {
        emit log(QString("Testing candidate index #%1 on table %2").arg(i).arg(ci.getTable()->getName()));

        testCandidate(ci);

        emit progress(100 * i++ / size);
    }

    emit resultReady();
}

void IndexVerification::testCandidate(CandidateIndex &candidate)
{
    QString dml = candidate.getCreateIndex();

    m_db.exec(dml);
    if (m_db.lastError().isValid()) {
        emit log(m_db.lastError().text());
    }
}
