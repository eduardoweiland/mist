#!/bin/sh

if [[ $# -ne 2 && $# -ne 3 ]]
then
    echo " Uso: $0 <código-fonte do MySQL> <destino da compilação> [debug]"
    echo
    echo " <código-fonte do MySQL> : caminho do diretório com o código do MySQL Server"
    echo " <destino da compilação> : caminho do diretório onde o MySQL será compilado"
    echo " debug                   : informar esse parâmetro para compilar o MySQL em modo debug"
    echo
    exit 1
fi

MYSQL_SOURCE="$1"
MYSQL_BUILD="$2"
DEBUG=0

if [[ "$3" -eq "debug" ]]
then
    DEBUG=1
fi

mkdir -p "$MYSQL_BUILD"
pushd "$MYSQL_BUILD"

cmake \
    -DWITH_DEBUG=$DEBUG \
    -DWITH_EMBEDDED_SERVER=1 \
    -DWITH_EMBEDDED_SHARED_LIBRARY=1 \
    "$MYSQL_SOURCE"

make

popd
