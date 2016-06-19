#ifndef SOLUTIONBUILDER_H
#define SOLUTIONBUILDER_H

#include <QHash>
#include <QSet>

#include "../entity/mistproject.h"

class SolutionBuilder
{
public:
    SolutionBuilder(MistProject project);

    void setCost(const int candidate, const int query, const double cost);
    double getCost(const int candidate, const int query) const;
    QSet<CandidateIndex> getBestSolution();

private:
    MistProject m_project;

    // queryCosts[query id][candidate index]
    QHash<int, QHash<int, double>> m_queryCosts;

    CandidateIndex getBestIndexForQueryAndTable(const int query, const QString table);
};

#endif // SOLUTIONBUILDER_H
