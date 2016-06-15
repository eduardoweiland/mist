#ifndef CANDIDATEINDEX_H
#define CANDIDATEINDEX_H

#include <QDebug>

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
    QStringList getColumnNames() const;
    void setColumns(const QList<IndexColumn> &value);
    void addColumn(const IndexColumn &value);
    void addColumns(const QList<IndexColumn> &value);

    QList<Query *> getAffectedQueries() const;
    void setAffectedQueries(const QList<Query *> &value);
    void addAffectedQuery(const Query *value);
    bool affectsQuery(const Query *query) const;

    /*! \brief Get the estimated size in bytes for one entry in the index */
    int getEntrySize() const;

    bool isValid() const;

    bool operator==(CandidateIndex &other) const;

    /*! \brief Check if other is a prefix of this index */
    bool isPrefix(const CandidateIndex &other) const;
    /*! \brief Check if columns form a prefix of this index */
    bool isPrefix(const QList<IndexColumn> &columns) const;
    /*! \brief Check if columns form a prefix of this index */
    bool isPrefix(const QList<TableColumn> &columns) const;
    /*! \brief Check if columns form a prefix of this index */
    bool isPrefix(const QStringList &columns) const;

    /*! \brief Check if this is a prefix of other index */
    bool isPrefixOf(const CandidateIndex &other) const;
    /*! \brief Check if this index is a prefix for columns */
    bool isPrefixOf(const QList<IndexColumn> &columns) const;
    /*! \brief Check if this index is a prefix for columns */
    bool isPrefixOf(const QList<TableColumn> &columns) const;
    /*! \brief Check if this index is a prefix for columns */
    bool isPrefixOf(const QStringList &columns) const;

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
