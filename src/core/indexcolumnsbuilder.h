#ifndef INDEXCOLUMNSBUILDER_H
#define INDEXCOLUMNSBUILDER_H

#include "../entity/mistproject.h"
#include "../entity/candidateindex.h"

class IndexColumnsBuilder
{
public:
    IndexColumnsBuilder(MistProject *project);

    CandidateIndex getBestCandidateForOrderBy(const QList<OrderByField> &orderBy);
    CandidateIndex getBestCandidateForGroupBy(const QList<GroupByField> &groupBy);

    QList<CandidateIndex> combineIndexes(const Table *table, const QList<FilterCondition> filters);
    QList<CandidateIndex> combineOrderByIndexes(const Table *table, const CandidateIndex &orderBy, const QList<FilterCondition> filters);
    QList<CandidateIndex> combineGroupByIndexes(const Table *table, const CandidateIndex &groupBy, const QList<FilterCondition> filters);

private:
    MistProject *m_project;

    QHash<FilterCondition::Type, QList<FilterCondition>> getFiltersByType(const QList<FilterCondition> &filters) const;
    QList<IndexColumn> filtersToIndexColumns(const QList<FilterCondition> &constFilters);
    QList<CandidateIndex> reduceIndexes(const CandidateIndex &index);
};

#endif // INDEXCOLUMNSBUILDER_H
