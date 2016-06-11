#include "querylistwidget.h"

QueryListWidget::QueryListWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void QueryListWidget::setQueries(const QList<Query> &queries)
{
    m_queries = queries;

    queriesWidget->setRowCount(queries.size());

    int row = 0;
    for (row = 0; row < queries.size(); row++) {
        queriesWidget->setItem(row, 0, new QTableWidgetItem(QString::number(queries[row].getId())));
        queriesWidget->setItem(row, 1, new QTableWidgetItem(QString::number(queries[row].getCount())));
        // TODO: 2 - Fields
        queriesWidget->setItem(row, 3, new QTableWidgetItem(queries[row].getFrom().join(", ")));

        QStringList joins;
        foreach (JoinTable join, queries[row].getJoins()) {
            joins << QString("%1(%2)").arg(join.getTable()).arg(join.getConditionFields().join(", "));
        }
        queriesWidget->setItem(row, 4, new QTableWidgetItem(joins.join(", ")));

        QStringList where;
        foreach (FilterCondition fc, queries[row].getWhere()) {
            where << QString("%1.%2").arg(fc.getTable()).arg(fc.getField());
        }
        queriesWidget->setItem(row, 5, new QTableWidgetItem(where.join(", ")));

        QStringList order;
        foreach (OrderByField of, queries[row].getOrderBy()) {
            order << QString("%1.%2 %3").arg(of.getTable()).arg(of.getField()).arg(of.getDirName());
        }
        queriesWidget->setItem(row, 6, new QTableWidgetItem(order.join(", ")));

        QStringList group;
        foreach (OrderByField gf, queries[row].getOrderBy()) {
            group << QString("%1.%2").arg(gf.getTable()).arg(gf.getField());
        }
        queriesWidget->setItem(row, 7, new QTableWidgetItem(group.join(", ")));
    }
}
