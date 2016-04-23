#ifndef CANDIDATEINDEX_H
#define CANDIDATEINDEX_H

#include "indexcolumn.h"
#include "query.h"
#include "table.h"

class CandidateIndex
{
public:
    CandidateIndex();

    const Table *getTable() const;
    void setTable(const Table *value);

    QList<IndexColumn> getColumns() const;
    void setColumns(const QList<IndexColumn> &value);

    QList<Query *> getAffectedQueries() const;
    void setAffectedQueries(const QList<Query *> &value);
    void addAffectedQuery(Query *value);
    bool affectsQuery(const Query *query) const;

    /*! \brief Get the estimated size in bytes for one entry in the index */
    int getEntrySize() const;

    bool operator==(CandidateIndex &other) const;

private:
    /*! \brief The table in which the index shall be created */
    const Table *table;

    /*! \brief The list of columns in this index */
    QList<IndexColumn> columns;

    /*! \brief List of queries that may be affected by this candidate index */
    QList<Query *> affectedQueries;
};

QDebug operator<<(QDebug debug, const CandidateIndex &ic);

#endif // CANDIDATEINDEX_H
