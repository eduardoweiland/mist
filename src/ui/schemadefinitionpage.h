#ifndef SCHEMADEFINITIONPAGE_H
#define SCHEMADEFINITIONPAGE_H

#include "ui_schemadefinitionpage.h"

class SchemaDefinitionPage : public QWizardPage, private Ui::SchemaDefinitionPage
{
    Q_OBJECT

public:
    explicit SchemaDefinitionPage(QWidget *parent = 0);
    bool isComplete() const;

private slots:
    void loadSchemaFile();

private:
    bool completed;
};

#endif // SCHEMADEFINITIONPAGE_H
