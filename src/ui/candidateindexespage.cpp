#include <QProgressDialog>

#include "candidateindexespage.h"
#include "mainwizard.h"

CandidateIndexesPage::CandidateIndexesPage(QWidget *parent) :
    QWizardPage(parent), generator(nullptr)
{
    setupUi(this);
    setCommitPage(true);
}

void CandidateIndexesPage::generateCandidates()
{
    if (generator != nullptr) {
        return;
    }

    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());

    QProgressDialog *progress = new QProgressDialog(
        tr("Generating candidates..."),
        tr("Cancel"),
        0,
        100,
        this
    );

    progress->setModal(true);
    progress->setValue(0);
    progress->setMinimumDuration(0);

    generator = new GenerateCandidateIndexes(mainWizard->project);
    connect(generator, SIGNAL(finished()), progress, SLOT(accept()));
    connect(generator, SIGNAL(progress(int)), progress, SLOT(setValue(int)));
    connect(generator, SIGNAL(resultReady()), this, SLOT(candidatesGenerated()));
    connect(progress, SIGNAL(canceled()), generator, SLOT(terminate()));
    generator->start();
}

void CandidateIndexesPage::candidatesGenerated()
{
    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());

    tableCandidates->setCandidates(generator->getGeneratedIndexes());
    mainWizard->project.setCandidates(generator->getGeneratedIndexes());
    delete generator;
    generator = nullptr;
}
