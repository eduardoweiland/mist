#include "candidateindex.h"

CandidateIndex::CandidateIndex()
{

}

const Table *CandidateIndex::getTable() const
{
    return table;
}

void CandidateIndex::setTable(const Table *value)
{
    table = value;
}

QList<IndexColumn> CandidateIndex::getColumns() const
{
    return columns;
}

QStringList CandidateIndex::getColumnNames() const
{
    QStringList names;
    foreach (IndexColumn column, columns) {
        names << column.getColumn()->getName();
    }

    return names;
}

void CandidateIndex::setColumns(const QList<IndexColumn> &value)
{
    columns = value;
}

void CandidateIndex::addColumn(const IndexColumn &value)
{
    columns.append(value);
}

void CandidateIndex::addColumns(const QList<IndexColumn> &value)
{
    columns.append(value);
}

QList<Query *> CandidateIndex::getAffectedQueries() const
{
    return affectedQueries;
}

void CandidateIndex::setAffectedQueries(const QList<Query *> &value)
{
    affectedQueries = value;
}

void CandidateIndex::addAffectedQuery(Query *value)
{
    if (!affectedQueries.contains(value)) {
        affectedQueries.append(value);
    }
}

bool CandidateIndex::affectsQuery(const Query *query) const
{
    return affectedQueries.contains(const_cast<Query*>(query));
}

int CandidateIndex::getEntrySize() const
{
    int bytes = 0;

    foreach (IndexColumn col, columns) {
        bytes += col.getColumn()->getSize();
    }

    return bytes;
}

bool CandidateIndex::isValid() const
{
    return ((table != nullptr) && (!columns.isEmpty()));
}

bool CandidateIndex::operator==(CandidateIndex &other) const
{
    return (table == other.table && columns == other.columns);
}

QDebug operator<<(QDebug debug, const CandidateIndex &ci)
{
    debug << ci.getTable()->getName() << ci.getColumns();

    return debug;
}
