#ifndef SOLUTIONSUMMARYPAGE_H
#define SOLUTIONSUMMARYPAGE_H

#include "ui_solutionsummarypage.h"

class SolutionSummaryPage : public QWizardPage, private Ui::SolutionSummaryPage
{
    Q_OBJECT

public:
    explicit SolutionSummaryPage(QWidget *parent = 0);

    void initializePage() Q_DECL_OVERRIDE;
};

#endif // SOLUTIONSUMMARYPAGE_H
