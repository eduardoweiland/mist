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
    QThread(parent), m_project(project), m_solutionBuilder(m_project),
    baseTotalCost(0), optimizedTotalCost(0)
{
    m_db = QSqlDatabase::database();
}

void IndexVerification::run()
{
    QList<CandidateIndex> candidates = m_project.getCandidates();
    int i = 1, size = candidates.size();

    writeLog("Calculating base query cost...");
    foreach (Query q, m_project.getQueries()) {
        baseTotalCost += getQueryCost(&q);
    }

    foreach (CandidateIndex ci, candidates) {
        writeLog(QString("Testing candidate index #%1 on table %2").arg(i).arg(ci.getTable()));

        testCandidate(ci);

        writeLog("------------------------------------");
        emit progress(100 * i++ / size);
    }

    writeLog("Calculating best solution...");
    QList<CandidateIndex> solution = m_solutionBuilder.getBestSolution();
    foreach (CandidateIndex index, solution) {
        writeLog("SOLUTION: " + index.getTable() + "(" + index.getColumnNames().join(", ") + ")");
    }

    writeLog("Calculating optimized query cost...");
    createIndexes(solution);
    foreach (Query q, m_project.getQueries()) {
        optimizedTotalCost += getQueryCost(&q);
    }
    dropIndexes(solution);

    emit resultReady();
}

QList<CandidateIndex> IndexVerification::getSolution()
{
    return m_solutionBuilder.getBestSolution();
}

double IndexVerification::getBaseTotalCost() const
{
    return baseTotalCost;
}

double IndexVerification::getOptimizedTotalCost() const
{
    return optimizedTotalCost;
}

void IndexVerification::testCandidate(CandidateIndex &candidate)
{
    createIndex(candidate);

    QList<int> queries = candidate.getAffectedQueries();
    foreach (int id, queries) {
        Query *query = m_project.getQuery(id);
        writeLog(QString("EXPLAIN query #%1").arg(query->getId()));

        double cost = getQueryCost(query);
        writeLog(QString("Query cost: %1").arg(cost));
        m_solutionBuilder.setCost(candidate.getId(), id, cost);
    }

    dropIndex(candidate);
}

void IndexVerification::createIndexes(QList<CandidateIndex> &candidates)
{
    foreach (CandidateIndex ci, candidates) {
        createIndex(ci);
    }
}

void IndexVerification::createIndex(CandidateIndex &candidate)
{
    QString dml = QString("ALTER TABLE %1 ADD INDEX __mist__index__%2__ (%3)")
            .arg(candidate.getTable())
            .arg(candidate.getId())
            .arg(candidate.getColumnNames().join(", "));

    writeLog(dml);
    m_db.exec(dml);
    if (m_db.lastError().isValid()) {
        writeLog(m_db.lastError().text());
    }
}

void IndexVerification::dropIndexes(QList<CandidateIndex> &candidates)
{
    foreach (CandidateIndex ci, candidates) {
        dropIndex(ci);
    }
}

void IndexVerification::dropIndex(CandidateIndex &candidate)
{
    QString dml = QString("ALTER TABLE %1 DROP INDEX __mist__index__%2__")
            .arg(candidate.getTable())
            .arg(candidate.getId());

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

double IndexVerification::getQueryCost(const Query *query)
{
    double cost = 0;
    QSqlQuery res = m_db.exec("EXPLAIN format=json " + query->getSql());

    if (m_db.lastError().isValid()) {
        writeLog(m_db.lastError().text());
    }
    else if (res.next()) {
        QByteArray json = res.value(0).toByteArray();
        QJsonDocument doc = QJsonDocument::fromJson(json);
        cost = doc.object().take("query_block").toObject().take("cost_info").toObject().take("query_cost").toString().toDouble();
    }

    return cost;
}
