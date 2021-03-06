#include "candidateindex.h"

CandidateIndex::CandidateIndex()
{
}

int CandidateIndex::getId() const
{
    return id;
}

void CandidateIndex::setId(const int value)
{
    id = value;
}

QString CandidateIndex::getTable() const
{
    return table;
}

void CandidateIndex::setTable(const QString value)
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
        names << column.getColumn();
    }

    return names;
}

void CandidateIndex::setColumns(const QList<IndexColumn> &value)
{
    columns.clear();

    foreach (IndexColumn col, value) {
        if (!columns.contains(col)) {
            columns.append(col);
        }
    }
}

void CandidateIndex::addColumn(const IndexColumn &value)
{
    if (!columns.contains(value)) {
        columns.append(value);
    }
}

void CandidateIndex::addColumns(const QList<IndexColumn> &value)
{
    foreach (IndexColumn col, value) {
        if (!columns.contains(col)) {
            columns.append(col);
        }
    }
}

QList<int> CandidateIndex::getAffectedQueries() const
{
    return affectedQueries;
}

void CandidateIndex::setAffectedQueries(const QList<int> &value)
{
    affectedQueries = value;
}

void CandidateIndex::addAffectedQuery(const int value)
{
    if (!affectedQueries.contains(value)) {
        affectedQueries.append(value);
    }
}

bool CandidateIndex::affectsQuery(const int query) const
{
    return affectedQueries.contains(query);
}

bool CandidateIndex::isValid() const
{
    return ((table != nullptr) && (!columns.isEmpty()));
}

bool CandidateIndex::isPrefix(const CandidateIndex &other) const
{
    return isPrefix(other.getColumns());
}

bool CandidateIndex::isPrefix(const QList<IndexColumn> &columns) const
{
    if (columns.size() > this->columns.size()) {
        return false;
    }

    for (int i = 0, l = columns.size(); i < l; ++i) {
        if (columns[i].getColumn() != this->columns[i].getColumn()) {
            return false;
        }
    }
    return true;
}

bool CandidateIndex::isPrefix(const QList<TableColumn> &columns) const
{
    if (columns.size() > this->columns.size()) {
        return false;
    }

    for (int i = 0, l = columns.size(); i < l; ++i) {
        if (columns[i].getName() != this->columns[i].getColumn()) {
            return false;
        }
    }
    return true;
}

bool CandidateIndex::isPrefix(const QStringList &columns) const
{
    if (columns.size() > this->columns.size()) {
        return false;
    }

    for (int i = 0, l = columns.size(); i < l; ++i) {
        if (columns[i] != this->columns[i].getColumn()) {
            return false;
        }
    }
    return true;
}

bool CandidateIndex::isPrefixOf(const CandidateIndex &other) const
{
    return isPrefixOf(other.getColumns());
}

bool CandidateIndex::isPrefixOf(const QList<IndexColumn> &columns) const
{
    if (this->columns.size() > columns.size()) {
        return false;
    }

    for (int i = 0, l = this->columns.size(); i < l; ++i) {
        if (columns[i].getColumn() != this->columns[i].getColumn()) {
            return false;
        }
    }
    return true;
}

bool CandidateIndex::isPrefixOf(const QList<TableColumn> &columns) const
{
    if (this->columns.size() > columns.size()) {
        return false;
    }

    for (int i = 0, l = this->columns.size(); i < l; ++i) {
        if (columns[i].getName() != this->columns[i].getColumn()) {
            return false;
        }
    }
    return true;
}

bool CandidateIndex::isPrefixOf(const QStringList &columns) const
{
    if (this->columns.size() > columns.size()) {
        return false;
    }

    for (int i = 0, l = this->columns.size(); i < l; ++i) {
        if (columns[i] != this->columns[i].getColumn()) {
            return false;
        }
    }
    return true;
}

bool CandidateIndex::operator==(CandidateIndex &other) const
{
    return (table == other.table && columns == other.columns);
}

bool CandidateIndex::operator==(const CandidateIndex &other) const
{
    return (table == other.table && columns == other.columns);
}

QDebug operator<<(QDebug debug, const CandidateIndex &ci)
{
    debug << ci.getTable() << ci.getColumns();

    return debug;
}

uint qHash(const CandidateIndex &candidate)
{
    return qHash(candidate.getTable() + candidate.getColumnNames().join(", "));
}
