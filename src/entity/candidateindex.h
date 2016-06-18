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

    QString getTable() const;
    void setTable(const QString value);

    QList<IndexColumn> getColumns() const;
    QStringList getColumnNames() const;
    void setColumns(const QList<IndexColumn> &value);
    void addColumn(const IndexColumn &value);
    void addColumns(const QList<IndexColumn> &value);

    QList<int> getAffectedQueries() const;
    void setAffectedQueries(const QList<int> &value);
    void addAffectedQuery(const int value);
    bool affectsQuery(const int query) const;

    bool isValid() const;

    QString getCreateIndex() const;

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
    QString table;

    /*! \brief The list of columns in this index */
    QList<IndexColumn> columns;

    /*! \brief List of queries that may be affected by this candidate index */
    QList<int> affectedQueries;
};

QDebug operator<<(QDebug debug, const CandidateIndex &ic);

#endif // CANDIDATEINDEX_H
