CREATE TABLE empresa
(
    empresa_id integer NOT NULL,
    nome_fantasia text NOT NULL,
    razao_social text,
    cnpj bigint,
    telefone varchar(11),
    logradouro text,
    numero text,
    complemento text,
    bairro text,
    cep text,
    cod_municipio integer,
    inscr_municipal varchar(20),
    inscr_estadual char(14),

    PRIMARY KEY(empresa_id)
);

CREATE TABLE forma_pagamento
(
    forma_pagamento_id integer NOT NULL,
    descricao varchar(40),
    codigo char(2),
    caixa boolean NOT NULL,
    banco boolean NOT NULL,

    PRIMARY KEY(forma_pagamento_id)
);

CREATE TABLE categoria
(
    categoria_id integer NOT NULL,
    empresa_id integer NOT NULL,
    entrada_saida char(1) NOT NULL,
    descricao text NOT NULL,

    PRIMARY KEY(categoria_id)
);

CREATE TABLE cadastro
(
    cadastro_id integer NOT NULL,
    empresa_id integer NOT NULL,
    cpf_cnpj char(14),
    inscr_estadual char(14),
    nome text,
    razao text,
    nasc_fundacao date,
    sexo char(1),
    telefones text,
    email text,
    website text,
    endereco text,
    numero text,
    complemento text,
    cod_municipio integer,
    bairro text,
    cep text,
    limite_cred decimal(12, 2),
    vendedor_id integer,
    prioridade integer,
    observacao text,
    situacao char(1),
    rg char(10),
    inscr_municipal char(20),
    pessoa char(2),
    empresa boolean NOT NULL,
    fornecedor boolean NOT NULL,
    vendedor boolean NOT NULL,
    transportador boolean NOT NULL,
    funcionario boolean NOT NULL,
    renda_mensal decimal(12, 2),
    referencias_comerciais text,

    PRIMARY KEY(cadastro_id)
);

CREATE TABLE banco
(
    banco_id integer NOT NULL,
    empresa_id integer NOT NULL,
    cod_febraban integer,
    descricao text,
    removido boolean NOT NULL,

    PRIMARY KEY(banco_id)
);

CREATE TABLE lancamento
(
    lancamento_id integer NOT NULL,
    empresa_id integer NOT NULL,
    versao_lancamento integer NOT NULL,
    num_lancamento integer,
    tipo integer NOT NULL,
    categoria_id integer NOT NULL,
    data datetime NOT NULL,
    observacao text,
    cadastro_id integer,
    desconto decimal(15, 2),
    vendedor_id integer,
    removido boolean NOT NULL,

    PRIMARY KEY(lancamento_id, versao_lancamento)
);

CREATE TABLE parcela
(
    parcela_id integer NOT NULL,
    empresa_id integer NOT NULL,
    tipo varchar(7) NOT NULL,
    lancamento_id integer,
    versao_lancamento integer,
    data_vencimento date NOT NULL,
    data_pagamento date,
    valor decimal(12, 2) NOT NULL,
    juros decimal(12, 2) NOT NULL,
    multa decimal(12, 2) NOT NULL,
    tarifas decimal(12, 2) NOT NULL,
    categoria_id integer,
    observacao text,
    cadastro_id integer,
    banco_id integer,
    forma_pagamento_id integer,
    removido boolean NOT NULL,
    recorrencia integer,

    PRIMARY KEY(parcela_id)
);
