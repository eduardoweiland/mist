#include <limits>

#include "solutionbuilder.h"

SolutionBuilder::SolutionBuilder(MistProject project) :
    m_project(project)
{
    foreach (Query query, m_project.getQueries()) {
        foreach (CandidateIndex index, m_project.getCandidates()) {
            m_queryCosts[query.getId()][index.getId()] = 0;
        }
    }
}

void SolutionBuilder::setCost(const int candidate, const int query, const double cost)
{
    m_queryCosts[query][candidate] = cost;
}

double SolutionBuilder::getCost(const int candidate, const int query) const
{
    return m_queryCosts[query][candidate];
}

QList<CandidateIndex> SolutionBuilder::getBestSolution()
{
    QSet<CandidateIndex> solution;

    foreach (Query query, m_project.getQueries()) {
        foreach (QString table, query.getUsedTables()) {
            solution.insert(getBestIndexForQueryAndTable(query.getId(), table));
        }
    }

    return solution.toList();
}

CandidateIndex SolutionBuilder::getBestIndexForQueryAndTable(const int query, const QString table)
{
    QList<CandidateIndex> allCandidates = m_project.getCandidatesForQuery(query);
    CandidateIndex best;
    double minimumCost = std::numeric_limits<double>::max();

    foreach (CandidateIndex candidate, allCandidates) {
        if (candidate.getTable() == table) {
            double cost = getCost(candidate.getId(), query);

            if (cost < minimumCost || (cost == minimumCost && candidate.getAffectedQueries().size() > best.getAffectedQueries().size())) {
                minimumCost = cost;
                best = candidate;
            }
        }
    }

    return best;
}
