#ifndef GENERATECANDIDATEINDEXES_H
#define GENERATECANDIDATEINDEXES_H

#include <QThread>

#include "../entity/mistproject.h"
#include "../entity/candidateindex.h"

class GenerateCandidateIndexes : public QThread
{
    Q_OBJECT

public:
    GenerateCandidateIndexes(MistProject &project);

    void run() Q_DECL_OVERRIDE;

    QList<CandidateIndex> getGeneratedIndexes();

signals:
    void resultReady();
    void progress(const int percent);

private:
    MistProject m_project;

    QList<CandidateIndex> possibleCandidates;

    int percentProgress;

    QList<CandidateIndex> getIndexesForQuery(const Query *query);
    QList<FilterCondition> getFiltersForTable(const Query *query, const QString tableName) const;
    void mergeUniqueIndexes(QList<CandidateIndex> &indexes);
};

#endif // GENERATECANDIDATEINDEXES_H
