#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QDebug>
#include <QString>

class TableColumn
{
public:
    TableColumn();

    enum Type {
        VARCHAR,
        CHAR,
        TEXT,
        TINYINT,
        SMALLINT,
        MEDIUMINT,
        INTEGER,
        BIGINT,
        BOOLEAN,
        DECIMAL,
        DATE,
        TIME,
        DATETIME,
        FLOAT,
        DOUBLE,
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

    bool operator==(TableColumn &other) const;

    /*! Get the size of the column in bytes */
    int getSize() const;

private:
    QString name;
    Type type;
    bool nullable;
    int length;
    int precision;
    int distinctValues;
};

QDebug operator<<(QDebug debug, const TableColumn &tc);

#endif // TABLECOLUMN_H
