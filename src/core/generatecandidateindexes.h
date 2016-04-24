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

signals:
    void resultReady(const QList<CandidateIndex> &indexes);
    void progress(const int percent);

private:
    Schema schema;
    QList<Query> queries;

    QList<CandidateIndex> possibleCandidates;

    int percentProgress;

    QList<CandidateIndex> getIndexesForQuery(const Query *query);
    QList<CandidateIndex> combineIndexes(QList<CandidateIndex> &indexes);
    void mergeUniqueIndexes(QList<CandidateIndex> &indexes);
};

#endif // GENERATECANDIDATEINDEXES_H
