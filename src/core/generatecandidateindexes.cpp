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
        qDebug() << "Gerando índices candidatos para consulta " << queries[i].getId();

        QList<CandidateIndex> indexes = getIndexesForQuery(&queries[i]);
        mergeUniqueIndexes(indexes);

        qInfo() << "Gerados " << indexes.size() << " índices candidatos para a consulta " << queries[i].getId();

        emit progress((int)((i + 1) / size));
    }
}

QList<CandidateIndex> GenerateCandidateIndexes::getIndexesForQuery(const Query *query)
{
    IndexColumnsBuilder builder(&schema);
    QList<CandidateIndex> candidates;

    QList<FilterCondition> filters = query->getWhere();
    foreach (JoinTable jt, query->getJoins()) {
        filters << jt.getConditions();
    }

    if (!query->getOrderBy().isEmpty()) {
        CandidateIndex orderByCandidate = builder.getBestCandidateForOrderBy(query->getOrderBy());
        qDebug() << "Melhor candidato para order by" << orderByCandidate;
        candidates << orderByCandidate;
    }

    if (!query->getGroupBy().isEmpty()) {
        CandidateIndex groupByCandidate = builder.getBestCandidateForGroupBy(query->getGroupBy());
        qDebug() << "Melhor candidato para group by" << groupByCandidate;
        candidates << groupByCandidate;
    }

    return candidates;
}

QList<CandidateIndex> GenerateCandidateIndexes::combineIndexes(QList<CandidateIndex> &indexes)
{
    // Gerar novos candidatos combinando índices candidatos existentes
}

void GenerateCandidateIndexes::mergeUniqueIndexes(QList<CandidateIndex> &indexes)
{
    foreach (CandidateIndex ni, indexes) {
        bool found = false;

        foreach (CandidateIndex ei, possibleCandidates) {
            if (ei == ni) {
                found = true;
                break;
            }
        }

        if (!found) {
            possibleCandidates.append(ni);
        }
    }
}
