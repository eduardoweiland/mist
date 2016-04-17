#include "schemacreator.h"

SchemaCreator::SchemaCreator()
{
}

QString SchemaCreator::getCreateTable(const Table *table)
{
    Q_ASSERT(table != nullptr);

    QStringList tableDefinition;

    QString colDef = getColumnsDefinition(table);
    if (!colDef.isNull()) {
        tableDefinition.append(colDef);
    }

    QString pkDef = getPrimaryKeyDefinition(table);
    if (!pkDef.isNull()) {
        tableDefinition.append(pkDef);
    }

    QString fkDef = getForeignKeysDefinition(table);
    if (!fkDef.isNull()) {
        tableDefinition.append(fkDef);
    }

    QString query = QString("CREATE TABLE %1 (%2);")
            .arg(table->getName())
            .arg(tableDefinition.join(", "));

    return query;
}

QString SchemaCreator::getColumnsDefinition(const Table *table)
{
    Q_ASSERT(table != nullptr);

    QStringList columns;

    foreach (TableColumn column, table->getColumns()) {
        QString columnDefinition = QString("%1 %2")
                .arg(column.getName())
                .arg(getColumnType(&column));

        columns.append(columnDefinition);
    }

    return columns.join(", ");
}

QString SchemaCreator::getColumnType(const TableColumn *column)
{
    Q_ASSERT(column != nullptr);

    QString type;

    switch (column->getType()) {
        case TableColumn::VARCHAR:
            type = QString("VARCHAR(%1)").arg(column->getLength());
            break;
        case TableColumn::CHAR:
            type = QString("CHAR(%1)").arg(column->getLength());
            break;
        case TableColumn::TEXT:
            type = "TEXT";
            break;
        case TableColumn::INTEGER:
            type = "INTEGER";
            break;
        case TableColumn::SMALLINT:
            type = "SMALLINT";
            break;
        case TableColumn::BIGINT:
            type = "BIGINT";
            break;
        case TableColumn::BOOLEAN:
            type = "BOOL";
            break;
        case TableColumn::DECIMAL:
            type = QString("DECIMAL(%1, %2)")
                    .arg(column->getLength())
                    .arg(column->getPrecision());
            break;
        case TableColumn::DATE:
            type = "DATE";
            break;
        case TableColumn::TIME:
            type = "TIME";
            break;
        case TableColumn::DATETIME:
            type = "DATETIME";
            break;
        case TableColumn::FLOAT:
            type = "FLOAT";
            break;
        case TableColumn::BLOB:
            type = "BLOB";
            break;
        default:
            return QString();
    }

    if (!column->getNullable()) {
        type += " NOT NULL";
    }

    return type;
}

QString SchemaCreator::getPrimaryKeyDefinition(const Table *table)
{
    Q_ASSERT(table != nullptr);

    if (table->getPrimaryKey().size() == 0) {
        return QString();
    }

    return QString("PRIMARY KEY (%1)").arg(table->getPrimaryKey().join(", "));
}

QString SchemaCreator::getForeignKeysDefinition(const Table *table)
{
    Q_ASSERT(table != nullptr);

    QStringList fks;

    foreach (ForeignKey fk, table->getForeignKeys()) {
        QStringList localCols, referencedCols;

        foreach (ForeignKeyColumn fkCol, fk.getColumns()) {
            localCols.append(fkCol.getName());
            referencedCols.append(fkCol.getReferenced());
        }

        fks.append(
            QString("FOREIGN KEY (%1) REFERENCES %2 (%3)")
                .arg(localCols.join(", "))
                .arg(fk.getTable())
                .arg(referencedCols.join(", "))
        );
    }

    return fks.join(", ");
}
