#ifndef SCHEMADEFINITIONPAGE_H
#define SCHEMADEFINITIONPAGE_H

#include "ui_schemadefinitionpage.h"

class SchemaDefinitionPage : public QWizardPage, private Ui::SchemaDefinitionPage
{
    Q_OBJECT

public:
    explicit SchemaDefinitionPage(QWidget *parent = 0);
};

#endif // SCHEMADEFINITIONPAGE_H
