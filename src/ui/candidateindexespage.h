#ifndef CANDIDATEINDEXESPAGE_H
#define CANDIDATEINDEXESPAGE_H

#include "ui_candidateindexespage.h"
#include "../entity/candidateindex.h"
#include "../core/generatecandidateindexes.h"

class CandidateIndexesPage : public QWizardPage, private Ui::CandidateIndexesPage
{
    Q_OBJECT

public:
    explicit CandidateIndexesPage(QWidget *parent = 0);

private slots:
    void generateCandidates(void);
    void candidatesGenerated();

private:
    GenerateCandidateIndexes *generator;
};

#endif // CANDIDATEINDEXESPAGE_H
