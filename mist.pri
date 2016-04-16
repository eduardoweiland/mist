#
# Variables and settings for building MIST MySQL Index Suggestion Tool
#
# Based on `pgmodeler.pri' by Raphael Araújo e Silva (https://github.com/pgmodeler/pgmodeler)
#

# General Qt settings
QT += core widgets network xml
CONFIG += ordered qt stl rtti exceptions warn_on c++11


# Forcing the display of some warnings
CONFIG(debug, debug|release): QMAKE_CXXFLAGS += "-Wall -Wextra -Wuninitialized"

# Below, the user can specify where all generated file can be placed
# through a set of variables, being them:
#
# PREFIX        -> the root directory where the files will be placed
# BINDIR        -> where executables accessible by the user resides
# PLUGINSDIR    -> where third party plugins are installed
# SHAREDIR      -> where shared files and resources should be placed
# CONFDIR       -> where the pgModeler's configuration folder (conf) resides
# DOCDIR        -> where documentation related files are placed
# LANGDIR       -> where the UI translation folder (lang) resides
#
# The values of each variable changes between supported platforms and are describe as follow


# Linux custom variables settings
linux {
  CONFIG += x11

  # Default configuration for package MIST.
  # The default prefix is /usr/local
  !defined(PREFIX, var):        PREFIX = /usr/local
  !defined(BINDIR, var):        BINDIR = $$PREFIX/bin
  !defined(SHAREDIR, var):      SHAREDIR = $$PREFIX/share/mist
  !defined(CONFDIR, var):       CONFDIR = $$SHAREDIR/conf
  !defined(DOCDIR, var):        DOCDIR = $$SHAREDIR
  !defined(LANGDIR, var):       LANGDIR = $$SHAREDIR/lang

  # Specifies where to find the libraries at runtime
  QMAKE_RPATHDIR += $$PRIVATELIBDIR
}


# Windows custom variables settings
windows {
  CONFIG += windows

  # The default prefix is ./build
  !defined(PREFIX, var):        PREFIX = $$PWD/build
  !defined(BINDIR, var):        BINDIR = $$PREFIX
  !defined(SHAREDIR, var):      SHAREDIR = $$PREFIX
  !defined(CONFDIR, var):       CONFDIR = $$PREFIX/conf
  !defined(DOCDIR, var):        DOCDIR = $$PREFIX
  !defined(LANGDIR, var):       LANGDIR = $$PREFIX/lang
}


# Creating constants based upon the custom paths so the GlobalAttributes
# namespace can correctly configure the paths inside the code
DEFINES += LANGDIR=\\\"$${LANGDIR}\\\"




###
### Configuração da biblioteca MySQL
###
MYSQL_SOURCE = $$(MYSQL_SOURCE)
MYSQL_BUILD = $$(MYSQL_BUILD)

if (isEmpty(MYSQL_SOURCE)) {
    error(Variável MYSQL_SOURCE não foi especificada. Deve conter o caminho para o código-fonte do MySQL.);
}
if (isEmpty(MYSQL_BUILD)) {
    error(Variável MYSQL_BUILD não foi especificada. Deve indicar o caminho onde o MySQL foi compilado.);
}

QMAKE_CXXFLAGS = -fabi-version=2 -fno-omit-frame-pointer

DEFINES += MYSQL_SERVER=1

INCLUDEPATH += $$MYSQL_SOURCE
INCLUDEPATH += $$MYSQL_SOURCE/include
INCLUDEPATH += $$MYSQL_SOURCE/libbinlogevents/export
INCLUDEPATH += $$MYSQL_SOURCE/libbinlogevents/include
INCLUDEPATH += $$MYSQL_SOURCE/sql

INCLUDEPATH += $$MYSQL_BUILD/include
INCLUDEPATH += $$MYSQL_BUILD/libbinlogevents/include

LIBS += -L$$MYSQL_BUILD/libmysqld -lmysqld -lpthread -lm -lrt -lcrypt -ldl

MYSQL_VERSION = $$system($$MYSQL_BUILD/scripts/mysql_config --version)
MYSQL_VERSION_PARTS = $$split(MYSQL_VERSION, .)
MYSQL_VERSION_MAJOR = $$member(MYSQL_VERSION_PARTS, 0)
MYSQL_VERSION_MINOR = $$member(MYSQL_VERSION_PARTS, 1)

if (lessThan(MYSQL_VERSION_MAJOR, 5)|lessThan(MYSQL_VERSION_MINOR, 7)) {
    error('Versão mínima suportada do MySQL é 5.7, encontrado $$MYSQL_VERSION');
}
