#include <QHash>
#include <QDebug>

#include "generatecandidateindexes.h"
#include "indexcolumnsbuilder.h"

GenerateCandidateIndexes::GenerateCandidateIndexes(MistProject &project) :
    m_project(project)
{
}

void GenerateCandidateIndexes::run()
{
    QList<Query> queries = m_project.getQueries();
    int size = m_project.getQueries().size();
    int i;

    sleep(1);

    for (i = 0; i < size; ++i) {
        QList<CandidateIndex> indexes = getIndexesForQuery(&queries[i]);
        mergeUniqueIndexes(indexes);

        qDebug() << "Gerados " << indexes.size() << " índices candidatos para a consulta " << queries[i].getId();

        emit progress(100 * (i + 1) / size);
    }

    emit resultReady();
}

QList<CandidateIndex> GenerateCandidateIndexes::getGeneratedIndexes()
{
    return generatedCandidates;
}

QList<CandidateIndex> GenerateCandidateIndexes::getIndexesForQuery(const Query *query)
{
    IndexColumnsBuilder builder(&m_project);
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
        Table *table = m_project.getTable(tableName);
        QList<FilterCondition> filters = getFiltersForTable(query, tableName);

        if (orderByCandidate.getTable() == table->getName()) {
            candidates << builder.combineOrderByIndexes(table, orderByCandidate, filters);
        }
        else if (groupByCandidate.getTable() == table->getName()) {
            candidates << builder.combineGroupByIndexes(table, groupByCandidate, filters);
        }
        else {
            candidates << builder.combineIndexes(table, filters);
        }
    }

    QList<CandidateIndex> finalCandidates;
    for (int i = 0; i < candidates.size(); ++i) {
        if (!candidates[i].isPrefixOf(m_project.getTable(candidates[i].getTable())->getPrimaryKey())) {
            candidates[i].addAffectedQuery(query->getId());
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

void GenerateCandidateIndexes::mergeUniqueIndexes(QList<CandidateIndex> indexes)
{
    int i, j;

    for (i = 0; i < indexes.size(); ++i) {
        bool found = false;

        for (j = 0; j < generatedCandidates.size(); ++j) {
            if (generatedCandidates[j] == indexes[i]) {
                foreach (int id, indexes[i].getAffectedQueries()) {
                    generatedCandidates[j].addAffectedQuery(id);
                }
                found = true;
                break;
            }
        }

        if (!found) {
            indexes[i].setId(j);
            generatedCandidates.append(indexes[i]);
        }
    }
}
