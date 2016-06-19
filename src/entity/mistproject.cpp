#include "mistproject.h"

MistProject::MistProject()
{
}

MistProject::MistProject(MistProject &other)
{
    setTables(other.getTables());
    setQueries(other.getQueries());
    setCandidates(other.getCandidates());
}

QList<Table> MistProject::getTables() const
{
    return m_mapTables.values();
}

void MistProject::setTables(const QList<Table> &tables)
{
    foreach (Table table, tables) {
        m_mapTables[table.getName()] = table;
    }
}

void MistProject::addTable(Table &table)
{
    m_mapTables[table.getName()] = table;
}

Table* MistProject::getTable(const QString name)
{
    return &m_mapTables[name];
}

QList<Query> MistProject::getQueries() const
{
    return m_queries;
}

void MistProject::setQueries(const QList<Query> &queries)
{
    m_queries = queries;
}

void MistProject::addQuery(const Query &query)
{
    m_queries.append(query);
}

Query *MistProject::getQuery(const int id)
{
    for (int i = 0; i < m_queries.size(); ++i) {
        if (m_queries[i].getId() == id) {
            return &m_queries[i];
        }
    }

    return nullptr;
}

QList<CandidateIndex> MistProject::getCandidates() const
{
    return m_candidates;
}

void MistProject::setCandidates(const QList<CandidateIndex> &candidates)
{
    m_candidates = candidates;
}

void MistProject::addCandidate(const CandidateIndex &candidate)
{
    m_candidates.append(candidate);
}

QList<CandidateIndex> MistProject::getCandidatesForQuery(const int id) const
{
    QList<CandidateIndex> list;

    foreach (CandidateIndex candidate, m_candidates) {
        if (candidate.affectsQuery(id)) {
            list.append(candidate);
        }
    }

    return list;
}

QList<CandidateIndex> MistProject::getSolution() const
{
    return m_solution;
}

void MistProject::setSolution(const QList<CandidateIndex> &solution)
{
    m_solution = solution;
}

QDebug operator<<(QDebug debug, const MistProject &project)
{
    debug << project.getTables();

    return debug;
}
