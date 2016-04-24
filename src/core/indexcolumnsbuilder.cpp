#include "indexcolumnsbuilder.h"

IndexColumnsBuilder::IndexColumnsBuilder(Schema *schema) :
    schema(schema)
{
}

CandidateIndex IndexColumnsBuilder::getBestCandidateForOrderBy(const QList<OrderByField> &orderBy)
{
    Q_ASSERT(!orderBy.isEmpty());

    CandidateIndex candidate;

    QString tableName = orderBy.first().getTable();
    OrderByField::Direction direction = orderBy.first().getDir();
    candidate.setTable(schema->getTable(tableName));

    foreach (OrderByField field, orderBy) {

        // Só é possível utilizar índices na ordenação para campos da mesma
        // tabela. Quando encontrar uma tabela diferente da primeira usada,
        // encerra a listagem de colunas possíveis para índices na ordenação.
        // Além disso, a direção da ordenação dos campos no ORDER BY deve
        // ser igual.
        if (field.getTable() != tableName || field.getDir() != direction) {
            break;
        }

        IndexColumn column;
        column.setColumn(candidate.getTable()->getColumn(field.getField()));
        candidate.addColumn(column);
    }

    return candidate;
}

CandidateIndex IndexColumnsBuilder::getBestCandidateForGroupBy(const QList<GroupByField> &groupBy)
{
    Q_ASSERT(!groupBy.isEmpty());

    CandidateIndex candidate;

    QString tableName = groupBy.first().getTable();
    candidate.setTable(schema->getTable(tableName));

    foreach (GroupByField field, groupBy) {

        // Só é possível utilizar índices no agrupamento para campos da
        // mesma tabela. Quando encontrar uma tabela diferente da primeira
        // usada, encerra a listagem de colunas possíveis para índices no
        // agrupamento.
        if (field.getTable() != tableName) {
            break;
        }

        IndexColumn column;
        column.setColumn(candidate.getTable()->getColumn(field.getField()));
        candidate.addColumn(column);
    }

    return candidate;
}
