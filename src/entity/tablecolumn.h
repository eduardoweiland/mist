#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QString>

class TableColumn
{
public:
    TableColumn();

    enum Type {
        VARCHAR,
        CHAR,
        TEXT,
        INTEGER,
        SMALLINT,
        BIGINT,
        BOOLEAN,
        DECIMAL,
        DATE,
        TIME,
        DATETIME,
        FLOAT,
        BLOB
    };

    QString getName() const;
    void setName(const QString &value);

    Type getType() const;
    void setType(const Type &value);

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
    Type type;
    bool nullable;
    int length;
    int precision;
    int distinctValues;
};

#endif // TABLECOLUMN_H
