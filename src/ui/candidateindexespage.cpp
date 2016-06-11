#include <QProgressDialog>

#include "candidateindexespage.h"
#include "mainwizard.h"
#include "../core/generatecandidateindexes.h"

CandidateIndexesPage::CandidateIndexesPage(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);
}

void CandidateIndexesPage::generateCandidates()
{
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

    GenerateCandidateIndexes *gen = new GenerateCandidateIndexes(mainWizard->schema, mainWizard->queries);
    connect(gen, SIGNAL(finished()), progress, SLOT(accept()));
    connect(gen, SIGNAL(finished()), gen, SLOT(deleteLater()));
    connect(gen, SIGNAL(progress(int)), progress, SLOT(setValue(int)));
    connect(progress, SIGNAL(canceled()), gen, SLOT(terminate()));
    gen->start();
}
