#ifndef GENERATECANDIDATEINDEXES_H
#define GENERATECANDIDATEINDEXES_H

#include <QThread>

#include "../entity/schema.h"
#include "../entity/candidateindex.h"

class GenerateCandidateIndexes : public QThread
{
    Q_OBJECT

public:
    GenerateCandidateIndexes(Schema &schema, QList<Query> &queries);

    void run() Q_DECL_OVERRIDE;

    QList<CandidateIndex> getGeneratedIndexes();

signals:
    void resultReady();
    void progress(const int percent);

private:
    Schema schema;
    QList<Query> queries;

    QList<CandidateIndex> possibleCandidates;

    int percentProgress;

    QList<CandidateIndex> getIndexesForQuery(const Query *query);
    QList<FilterCondition> getFiltersForTable(const Query *query, const QString tableName) const;
    void mergeUniqueIndexes(QList<CandidateIndex> &indexes);
};

#endif // GENERATECANDIDATEINDEXES_H
