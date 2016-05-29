#include "tablelistwidget.h"

TableListWidget::TableListWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(tablesWidget, SIGNAL(itemSelectionChanged()), this, SLOT(tableSelected()));
    tableColumnsWidget->setVisible(false);
}

void TableListWidget::setTables(const QList<Table> &tables)
{
    m_tables = tables;

    tablesWidget->setRowCount(tables.size());

    int row = 0;
    for (row = 0; row < tables.size(); row++) {
        tablesWidget->setItem(row, 0, new QTableWidgetItem(tables[row].getName()));
        tablesWidget->setItem(row, 1, new QTableWidgetItem(tables[row].getPrimaryKey().join(", ")));
        tablesWidget->setItem(row, 2, new QTableWidgetItem(QString::number(tables[row].getRowCount())));
    }
}

void TableListWidget::tableSelected()
{
    QList<QTableWidgetItem*> selection = tablesWidget->selectedItems();

    if (selection.size() == 0) {
        tableColumnsWidget->setRowCount(0);
        tableColumnsWidget->setVisible(false);
    }
    else {
        Table table = m_tables.at(selection.first()->row());
        QList<TableColumn> columns = table.getColumns();

        tableColumnsWidget->setRowCount(columns.size());
        tableColumnsWidget->setVisible(true);

        int row;
        for (row = 0; row < columns.size(); row++) {
            QTableWidgetItem *checkNullable = new QTableWidgetItem();
            checkNullable->setFlags(checkNullable->flags() & ~Qt::ItemIsUserCheckable);
            checkNullable->setCheckState(columns[row].getNullable() ? Qt::Checked : Qt::Unchecked);

            tableColumnsWidget->setItem(row, 0, new QTableWidgetItem(columns[row].getName()));
            tableColumnsWidget->setItem(row, 1, new QTableWidgetItem(columns[row].getTypeName()));
            tableColumnsWidget->setItem(row, 2, checkNullable);
            tableColumnsWidget->setItem(row, 3, new QTableWidgetItem(QString::number(columns[row].getNullValues())));
            tableColumnsWidget->setItem(row, 4, new QTableWidgetItem(QString::number(columns[row].getDistinctValues())));
        }
    }
}
