#ifndef TABLELISTWIDGET_H
#define TABLELISTWIDGET_H

#include "ui_tablelistwidget.h"
#include "../entity/table.h"

class TableListWidget : public QWidget, private Ui::TableListWidget
{
    Q_OBJECT

public:
    TableListWidget(QWidget *parent = 0);

    void setTables(const QList<Table> &tables);

private slots:
    void tableSelected();

private:
    QList<Table> m_tables;
};

#endif // TABLELISTWIDGET_H
