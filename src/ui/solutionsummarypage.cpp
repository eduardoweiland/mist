#include "mainwizard.h"
#include "solutionsummarypage.h"

SolutionSummaryPage::SolutionSummaryPage(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);
}

void SolutionSummaryPage::initializePage()
{
    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());
    indexesWidget->setCandidates(mainWizard->project.getSolution());
    labelCostWithoutIndexes->setText(QString::number(mainWizard->project.getBaseTotalCost(), 'g', 10));
    labelCostSuggestedIndexes->setText(QString::number(mainWizard->project.getOptimizedTotalCost(), 'g', 10));
}
