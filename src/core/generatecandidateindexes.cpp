#include <QHash>
#include <QDebug>

#include "generatecandidateindexes.h"
#include "indexcolumnsbuilder.h"

GenerateCandidateIndexes::GenerateCandidateIndexes(Schema &schema, QList<Query> &queries) :
    schema(schema), queries(queries)
{
}

void GenerateCandidateIndexes::run()
{
    int size = queries.size();
    int i;

    sleep(1);

    for (i = 0; i < size; ++i) {
        QList<CandidateIndex> indexes = getIndexesForQuery(&queries[i]);
        mergeUniqueIndexes(indexes);

        qInfo() << "Gerados " << indexes.size() << " índices candidatos para a consulta " << queries[i].getId();

        emit progress((int)((i + 1) / size));
    }

    emit resultReady();
}

QList<CandidateIndex> GenerateCandidateIndexes::getGeneratedIndexes()
{
    return possibleCandidates;
}

QList<CandidateIndex> GenerateCandidateIndexes::getIndexesForQuery(const Query *query)
{
    IndexColumnsBuilder builder(&schema);
    QList<CandidateIndex> candidates;

    CandidateIndex orderByCandidate;
    if (!query->getOrderBy().isEmpty()) {
        orderByCandidate = builder.getBestCandidateForOrderBy(query->getOrderBy());
    }

    CandidateIndex groupByCandidate;
    if (!query->getGroupBy().isEmpty()) {
        groupByCandidate = builder.getBestCandidateForGroupBy(query->getGroupBy());
    }

    QStringList tables = query->getUsedTables();
    foreach (QString tableName, tables) {
        Table *table = schema.getTable(tableName);
        QList<FilterCondition> filters = getFiltersForTable(query, tableName);

        if (orderByCandidate.getTable() == table) {
            candidates << builder.combineOrderByIndexes(table, orderByCandidate, filters);
        }
        else if (groupByCandidate.getTable() == table) {
            candidates << builder.combineGroupByIndexes(table, groupByCandidate, filters);
        }
        else {
            candidates << builder.combineIndexes(table, filters);
        }
    }

    QList<CandidateIndex> finalCandidates;
    for (int i = 0; i < candidates.size(); ++i) {
        if (!candidates[i].isPrefixOf(candidates[i].getTable()->getPrimaryKey())) {
            candidates[i].addAffectedQuery(query);
            finalCandidates << candidates[i];
        }
    }

    return finalCandidates;
}

QList<FilterCondition> GenerateCandidateIndexes::getFiltersForTable(const Query *query, const QString tableName) const
{
    QList<FilterCondition> allFilters = query->getWhere();
    foreach (JoinTable jt, query->getJoins()) {
        allFilters << jt.getConditions();
    }

    QList<FilterCondition> tableFilters;
    foreach (FilterCondition cond, allFilters) {
        if (cond.getTable() == tableName) {
            tableFilters << cond;
        }
    }

    return tableFilters;
}

void GenerateCandidateIndexes::mergeUniqueIndexes(QList<CandidateIndex> &indexes)
{
    foreach (CandidateIndex ni, indexes) {
        bool found = false;

        for (int i = 0; i < possibleCandidates.size(); ++i) {
            if (possibleCandidates[i] == ni) {
                foreach (Query *q, ni.getAffectedQueries()) {
                    possibleCandidates[i].addAffectedQuery(q);
                }
                found = true;
                break;
            }
        }

        if (!found) {
            possibleCandidates.append(ni);
        }
    }
}
