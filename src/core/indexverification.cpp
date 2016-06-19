#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "indexverification.h"
#include "../entity/queryexplain.h"

IndexVerification::IndexVerification(MistProject project, QObject *parent) :
    QThread(parent), m_project(project), m_solutionBuilder(m_project)
{
    m_db = QSqlDatabase::database();
}

void IndexVerification::run()
{
    QList<CandidateIndex> candidates = m_project.getCandidates();
    int i = 1, size = candidates.size();

    foreach (CandidateIndex ci, candidates) {
        emit log(QString("Testing candidate index #%1 on table %2").arg(i).arg(ci.getTable()));

        testCandidate(ci);

        writeLog("------------------------------------");
        emit progress(100 * i++ / size);
    }

    writeLog("Calculating best solution...");
    QSet<CandidateIndex> solution = m_solutionBuilder.getBestSolution();
    foreach (CandidateIndex index, solution) {
        writeLog("SOLUTION: " + index.getTable() + "(" + index.getColumnNames().join(", ") + ")");
    }

    emit resultReady();
}

QList<CandidateIndex> IndexVerification::getSolution()
{
    return m_solutionBuilder.getBestSolution().toList();
}

void IndexVerification::testCandidate(CandidateIndex &candidate)
{
    createIndex(candidate);

    QList<int> queries = candidate.getAffectedQueries();
    foreach (int id, queries) {
        Query *query = m_project.getQuery(id);
        writeLog(QString("EXPLAIN query #%1").arg(query->getId()));

        QSqlQuery res = m_db.exec("EXPLAIN format=json " + query->getSql());
        if (m_db.lastError().isValid()) {
            writeLog(m_db.lastError().text());
        }

        if (res.next()) {
            QByteArray json = res.value(0).toByteArray();
            QJsonDocument doc = QJsonDocument::fromJson(json);
            double cost = doc.object().take("query_block").toObject().take("cost_info").toObject().take("query_cost").toString().toDouble();
            writeLog(QString("Query cost: %1").arg(cost));

            m_solutionBuilder.setCost(candidate.getId(), id, cost);
        }
    }

    dropIndex(candidate);
}

void IndexVerification::createIndex(CandidateIndex &candidate)
{
    QString dml = QString("ALTER TABLE %1 ADD INDEX __mist__index__ (%2)")
            .arg(candidate.getTable())
            .arg(candidate.getColumnNames().join(", "));

    writeLog(dml);
    m_db.exec(dml);
    if (m_db.lastError().isValid()) {
        writeLog(m_db.lastError().text());
    }
}

void IndexVerification::dropIndex(CandidateIndex &candidate)
{
    QString dml = QString("ALTER TABLE %1 DROP INDEX __mist__index__")
            .arg(candidate.getTable());

    writeLog(dml);
    m_db.exec(dml);
    if (m_db.lastError().isValid()) {
        writeLog(m_db.lastError().text());
    }
}


void IndexVerification::writeLog(QString msg)
{
    qDebug() << "[IndexVerification]" << msg;
    emit log(msg);
}
