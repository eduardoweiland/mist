#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QString>

class TableColumn
{
public:
    TableColumn();

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    bool getNullable() const;
    void setNullable(bool value);

    int getLength() const;
    void setLength(int value);

    int getPrecision() const;
    void setPrecision(int value);

    int getDistinctValues() const;
    void setDistinctValues(int value);

private:
    QString name;
    QString type;
    bool nullable;
    int length;
    int precision;
    int distinctValues;
};

#endif // TABLECOLUMN_H
