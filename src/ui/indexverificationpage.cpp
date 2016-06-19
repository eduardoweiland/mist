#include "indexverificationpage.h"
#include "mainwizard.h"

IndexVerificationPage::IndexVerificationPage(QWidget *parent) :
    QWizardPage(parent), completed(false)
{
    setupUi(this);
}

void IndexVerificationPage::initializePage()
{
    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());

    m_thread = new IndexVerification(mainWizard->project, this);
    connect(m_thread, SIGNAL(progress(int)), progressBar, SLOT(setValue(int)));
    connect(m_thread, SIGNAL(log(QString)), logViewer, SLOT(append(QString)));
    connect(m_thread, SIGNAL(resultReady()), this, SLOT(verificationFinished()));
    m_thread->start();
}

bool IndexVerificationPage::isComplete() const
{
    return completed;
}

void IndexVerificationPage::verificationFinished()
{
    logViewer->append("Done!");

    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());
    mainWizard->project.setSolution(m_thread->getSolution());
    mainWizard->project.setBaseTotalCost(m_thread->getBaseTotalCost());
    mainWizard->project.setOptimizedTotalCost(m_thread->getOptimizedTotalCost());
    delete m_thread;

    completed = true;
    emit completeChanged();
}
