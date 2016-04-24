#ifndef INDEXCOLUMNSBUILDER_H
#define INDEXCOLUMNSBUILDER_H

#include "../entity/schema.h"
#include "../entity/candidateindex.h"

class IndexColumnsBuilder
{
public:
    IndexColumnsBuilder(Schema *schema);

    CandidateIndex getBestCandidateForOrderBy(const QList<OrderByField> &orderBy);
    CandidateIndex getBestCandidateForGroupBy(const QList<GroupByField> &groupBy);

private:
    Schema *schema;
};

#endif // INDEXCOLUMNSBUILDER_H
