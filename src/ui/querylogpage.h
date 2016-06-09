#ifndef QUERYLOGPAGE_H
#define QUERYLOGPAGE_H

#include "ui_querylogpage.h"

class QueryLogPage : public QWizardPage, private Ui::QueryLogPage
{
    Q_OBJECT

public:
    explicit QueryLogPage(QWidget *parent = 0);
};

#endif // QUERYLOGPAGE_H
