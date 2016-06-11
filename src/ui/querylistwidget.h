#ifndef QUERYLISTWIDGET_H
#define QUERYLISTWIDGET_H

#include "ui_querylistwidget.h"
#include "../entity/query.h"

class QueryListWidget : public QWidget, private Ui::QueryListWidget
{
    Q_OBJECT

public:
    explicit QueryListWidget(QWidget *parent = 0);

    void setQueries(const QList<Query> &queries);

private:
    QList<Query> m_queries;
};

#endif // QUERYLISTWIDGET_H
