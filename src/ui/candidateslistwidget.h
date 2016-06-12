#ifndef CANDIDATESLISTWIDGET_H
#define CANDIDATESLISTWIDGET_H

#include "ui_candidateslistwidget.h"
#include "../entity/candidateindex.h"

class CandidatesListWidget : public QWidget, private Ui::CandidatesListWidget
{
    Q_OBJECT

public:
    explicit CandidatesListWidget(QWidget *parent = 0);

    void setCandidates(const QList<CandidateIndex> &candidates);

private:
    QList<CandidateIndex> m_candidates;
};

#endif // CANDIDATESLISTWIDGET_H
