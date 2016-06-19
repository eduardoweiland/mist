#ifndef INDEXVERIFICATIONPAGE_H
#define INDEXVERIFICATIONPAGE_H

#include "ui_indexverificationpage.h"
#include "../core/indexverification.h"

class IndexVerificationPage : public QWizardPage, private Ui::IndexVerificationPage
{
    Q_OBJECT

public:
    explicit IndexVerificationPage(QWidget *parent = 0);
    bool isComplete() const;

    void initializePage() Q_DECL_OVERRIDE;

private slots:
    void verificationFinished();

private:
    IndexVerification *m_thread;
    bool completed;
};

#endif // INDEXVERIFICATIONPAGE_H
