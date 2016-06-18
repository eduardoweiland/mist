#include "candidateslistwidget.h"

CandidatesListWidget::CandidatesListWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void CandidatesListWidget::setCandidates(const QList<CandidateIndex> &candidates)
{
    m_candidates = candidates;

    candidatesWidget->setRowCount(candidates.size());

    int row = 0;
    for (row = 0; row < candidates.size(); row++) {
        candidatesWidget->setItem(row, 0, new QTableWidgetItem(candidates[row].getTable()));
        candidatesWidget->setItem(row, 1, new QTableWidgetItem(candidates[row].getColumnNames().join(", ")));
        candidatesWidget->setItem(row, 2, new QTableWidgetItem(QString::number(candidates[row].getAffectedQueries().size())));
    }
}
