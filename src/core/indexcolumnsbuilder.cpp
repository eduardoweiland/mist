#include <QHash>

#include "indexcolumnsbuilder.h"

IndexColumnsBuilder::IndexColumnsBuilder(MistProject *project) :
    m_project(project)
{
}

CandidateIndex IndexColumnsBuilder::getBestCandidateForOrderBy(const QList<OrderByField> &orderBy)
{
    Q_ASSERT(!orderBy.isEmpty());

    CandidateIndex candidate;

    QString tableName = orderBy.first().getTable();
    OrderByField::Direction direction = orderBy.first().getDir();
    candidate.setTable(tableName);

    foreach (OrderByField field, orderBy) {

        // Só é possível utilizar índices na ordenação para campos da mesma
        // tabela. Quando encontrar uma tabela diferente da primeira usada,
        // encerra a listagem de colunas possíveis para índices na ordenação.
        // Além disso, a direção da ordenação dos campos no ORDER BY deve
        // ser igual.
        if (field.getTable() != tableName || field.getDir() != direction) {
            break;
        }

        TableColumn::Type type = m_project->getTable(field.getTable())->getColumn(field.getField())->getType();

        // MIST ainda não suporta geração de índices para colunas BLOB ou TEXT
        // Seria necessário calcular um prefixo para ser utilizado no índice, em vez de utilizar a coluna completa
        // Se um campo desse tipo for utilizado no ORDER BY, nenhum índice poderá ser utilizado para
        // ordernar os campos seguintes
        if (type == TableColumn::BLOB || type == TableColumn::TEXT) {
            break;
        }

        IndexColumn column;
        column.setColumn(field.getField());
        candidate.addColumn(column);
    }

    return candidate;
}

CandidateIndex IndexColumnsBuilder::getBestCandidateForGroupBy(const QList<GroupByField> &groupBy)
{
    Q_ASSERT(!groupBy.isEmpty());

    CandidateIndex candidate;

    QString tableName = groupBy.first().getTable();
    candidate.setTable(tableName);

    foreach (GroupByField field, groupBy) {

        // Só é possível utilizar índices no agrupamento para campos da
        // mesma tabela. Quando encontrar uma tabela diferente da primeira
        // usada, encerra a listagem de colunas possíveis para índices no
        // agrupamento.
        if (field.getTable() != tableName) {
            break;
        }

        TableColumn::Type type = m_project->getTable(field.getTable())->getColumn(field.getField())->getType();

        // MIST ainda não suporta geração de índices para colunas BLOB ou TEXT
        // Seria necessário calcular um prefixo para ser utilizado no índice, em vez de utilizar a coluna completa
        // Se um campo desse tipo for utilizado no GROUP BY, nenhum índice poderá ser utilizado para
        // agrupar os campos seguintes
        if (type == TableColumn::BLOB || type == TableColumn::TEXT) {
            break;
        }

        IndexColumn column;
        column.setColumn(field.getField());
        candidate.addColumn(column);
    }

    return candidate;
}

// Todas as condições no filters devem ser da mesma tabela!
QList<CandidateIndex> IndexColumnsBuilder::combineIndexes(const Table *table, const QList<FilterCondition> filters)
{
    QHash<FilterCondition::Type, QList<FilterCondition>> filtersByType = getFiltersByType(filters);

    QList<IndexColumn> columns = filtersToIndexColumns(filtersByType[FilterCondition::CONST])
                               + filtersToIndexColumns(filtersByType[FilterCondition::MATCH])
                               + filtersToIndexColumns(filtersByType[FilterCondition::RANGE])
                               + filtersToIndexColumns(filtersByType[FilterCondition::LIST])
                               + filtersToIndexColumns(filtersByType[FilterCondition::LIKE]);

    CandidateIndex index;
    index.setTable(table->getName());
    index.setColumns(columns);

    return reduceIndexes(index);
}


// Todas as condições no filters devem ser da mesma tabela!
QList<CandidateIndex> IndexColumnsBuilder::combineOrderByIndexes(const Table *table, const CandidateIndex &orderBy, const QList<FilterCondition> filters)
{
    QHash<FilterCondition::Type, QList<FilterCondition>> filtersByType = getFiltersByType(filters);

    QList<IndexColumn> prefix = filtersToIndexColumns(filtersByType[FilterCondition::CONST]);
    QList<IndexColumn> suffix = filtersToIndexColumns(filtersByType[FilterCondition::MATCH])
                              + filtersToIndexColumns(filtersByType[FilterCondition::RANGE])
                              + filtersToIndexColumns(filtersByType[FilterCondition::LIST])
                              + filtersToIndexColumns(filtersByType[FilterCondition::LIKE]);

    CandidateIndex indexPrefix;
    indexPrefix.setTable(table->getName());
    indexPrefix.setColumns(prefix);
    QList<CandidateIndex> indexPrefixes = reduceIndexes(indexPrefix);

    CandidateIndex indexSuffix;
    indexSuffix.setTable(table->getName());
    indexSuffix.setColumns(suffix);
    QList<CandidateIndex> indexSuffixes = reduceIndexes(indexSuffix);

    QList<CandidateIndex> candidates;
    candidates << indexPrefixes << indexSuffixes << orderBy;

    // COM prefixo e SEM sufixo
    foreach (CandidateIndex prefix, indexPrefixes) {
        prefix.addColumns(orderBy.getColumns());
        candidates << prefix;
    }

    // COM prefixo e COM sufixo
    foreach (CandidateIndex prefix, indexPrefixes) {
        prefix.addColumns(orderBy.getColumns());
        foreach (CandidateIndex suffix, indexSuffixes) {
            prefix.addColumns(suffix.getColumns());
            candidates << prefix;
        }
    }

    return candidates;
}

// Todas as condições no filters devem ser da mesma tabela!
QList<CandidateIndex> IndexColumnsBuilder::combineGroupByIndexes(const Table *table, const CandidateIndex &groupBy, const QList<FilterCondition> filters)
{
    QHash<FilterCondition::Type, QList<FilterCondition>> filtersByType = getFiltersByType(filters);

    QList<IndexColumn> prefix = filtersToIndexColumns(filtersByType[FilterCondition::CONST]);
    QList<IndexColumn> suffix = filtersToIndexColumns(filtersByType[FilterCondition::MATCH])
                              + filtersToIndexColumns(filtersByType[FilterCondition::LIST])
                              + filtersToIndexColumns(filtersByType[FilterCondition::RANGE])
                              + filtersToIndexColumns(filtersByType[FilterCondition::LIKE]);

    CandidateIndex indexPrefix;
    indexPrefix.setTable(table->getName());
    indexPrefix.setColumns(prefix);
    QList<CandidateIndex> indexPrefixes = reduceIndexes(indexPrefix);

    CandidateIndex indexSuffix;
    indexSuffix.setTable(table->getName());
    indexSuffix.setColumns(suffix);
    QList<CandidateIndex> indexSuffixes = reduceIndexes(indexSuffix);

    QList<CandidateIndex> candidates;
    candidates << indexPrefixes << indexSuffixes << groupBy;

    // COM prefixo e SEM sufixo
    foreach (CandidateIndex prefix, indexPrefixes) {
        prefix.addColumns(groupBy.getColumns());
        candidates << prefix;
    }

    // COM prefixo e COM sufixo
    foreach (CandidateIndex prefix, indexPrefixes) {
        prefix.addColumns(groupBy.getColumns());
        foreach (CandidateIndex suffix, indexSuffixes) {
            prefix.addColumns(suffix.getColumns());
            candidates << prefix;
        }
    }

    return candidates;
}

QHash<FilterCondition::Type, QList<FilterCondition>> IndexColumnsBuilder::getFiltersByType(const QList<FilterCondition> &filters) const
{
    QHash<FilterCondition::Type, QList<FilterCondition>> filtersByType;

    foreach (FilterCondition fc, filters) {
        filtersByType[fc.getType()].append(fc);
    }

    return filtersByType;
}

QList<IndexColumn> IndexColumnsBuilder::filtersToIndexColumns(const QList<FilterCondition> &constFilters)
{
    QList<IndexColumn> columns;

    foreach (FilterCondition fc, constFilters) {
        TableColumn::Type type = m_project->getTable(fc.getTable())->getColumn(fc.getField())->getType();

        // MIST ainda não suporta geração de índices para colunas BLOB ou TEXT
        // Seria necessário calcular um prefixo para ser utilizado no índice, em vez de utilizar a coluna completa
        if (type != TableColumn::BLOB && type != TableColumn::TEXT) {
            IndexColumn ic;
            ic.setColumn(fc.getField());
            columns.append(ic);
        }
    }

    return columns;
}

// Gera novos índices reduzidos a partir de um completo, removendo as últimas colunas
QList<CandidateIndex> IndexColumnsBuilder::reduceIndexes(const CandidateIndex &index)
{
    QList<CandidateIndex> indexes;

    CandidateIndex reducedIndex = index;
    while (!reducedIndex.getColumns().isEmpty()) {
        indexes << reducedIndex;
        QList<IndexColumn> cols = reducedIndex.getColumns();
        cols.removeLast();
        reducedIndex.setColumns(cols);
    }

    return indexes;
}
