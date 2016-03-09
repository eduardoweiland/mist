#
# Variables and settings for building MIST MySQL Index Suggestion Tool
#
# Based on `pgmodeler.pri' by Raphael Araújo e Silva (https://github.com/pgmodeler/pgmodeler)
#

# General Qt settings
QT += core widgets network
CONFIG += ordered qt stl rtti exceptions warn_on c++11


# Forcing the display of some warnings
CONFIG(debug, debug|release): QMAKE_CXXFLAGS += "-Wall -Wextra -Wuninitialized"

# Below, the user can specify where all generated file can be placed
# through a set of variables, being them:
#
# PREFIX        -> the root directory where the files will be placed
# BINDIR        -> where executables accessible by the user resides
# PRIVATEBINDIR -> where executables not directly accessible by the user resides
# PRIVATELIBDIR -> where libraries not directly shared through the system resides
# PLUGINSDIR    -> where third party plugins are installed
# SHAREDIR      -> where shared files and resources should be placed
# CONFDIR       -> where the pgModeler's configuration folder (conf) resides
# DOCDIR        -> where documentation related files are placed
# LANGDIR       -> where the UI translation folder (lang) resides
# SAMPLESDIR    -> where the sample models folder (samples) resides
# SCHEMASDIR    -> where the object's schemas folder (schema) resides
#
# The values of each variable changes between supported platforms and are describe as follow


# Linux custom variables settings
linux {
  CONFIG += x11

  # Default configuration for package MIST.
  # The default prefix is /usr/local
  !defined(PREFIX, var):        PREFIX = /usr/local
  !defined(BINDIR, var):        BINDIR = $$PREFIX/bin
  !defined(PRIVATEBINDIR, var): PRIVATEBINDIR = $$PREFIX/lib/mist/bin
  !defined(PRIVATELIBDIR, var): PRIVATELIBDIR = $$PREFIX/lib/mist
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
  !defined(PRIVATEBINDIR, var): PRIVATEBINDIR = $$PREFIX
  !defined(PRIVATELIBDIR, var): PRIVATELIBDIR = $$PREFIX
  !defined(SHAREDIR, var):      SHAREDIR = $$PREFIX
  !defined(CONFDIR, var):       CONFDIR = $$PREFIX/conf
  !defined(DOCDIR, var):        DOCDIR = $$PREFIX
  !defined(LANGDIR, var):       LANGDIR = $$PREFIX/lang
}


# Creating constants based upon the custom paths so the GlobalAttributes
# namespace can correctly configure the paths inside the code
DEFINES += BINDIR=\\\"$${BINDIR}\\\" \
           PLUGINSDIR=\\\"$${PLUGINSDIR}\\\" \
           PRIVATEBINDIR=\\\"$${PRIVATEBINDIR}\\\" \
           CONFDIR=\\\"$${CONFDIR}\\\" \
           DOCDIR=\\\"$${DOCDIR}\\\" \
           LANGDIR=\\\"$${LANGDIR}\\\" \




###
### Configuração da biblioteca MySQL
###
MYSQL_CONFIG = $$(MYSQL_CONFIG)

if (isEmpty(MYSQL_CONFIG)) {
    error(Variável MYSQL_CONFIG não foi especificada. Deve conter o caminho para o script mysql_config);
} else {
    message(Usando MYSQL_CONFIG = $$MYSQL_CONFIG);
}

QMAKE_CXXFLAGS += $$system($$MYSQL_CONFIG --cxxflags)
LIBS += $$system($$MYSQL_CONFIG --libmysqld-libs)

MYSQL_VERSION = $$system($$MYSQL_CONFIG --version)
MYSQL_VERSION_PARTS = $$split(MYSQL_VERSION, .)
MYSQL_VERSION_MAJOR = $$member(MYSQL_VERSION_PARTS, 0)
MYSQL_VERSION_MINOR = $$member(MYSQL_VERSION_PARTS, 1)

if (lessThan(MYSQL_VERSION_MAJOR, 5)|lessThan(MYSQL_VERSION_MINOR, 7)) {
    error('Versão mínima suportada do MySQL é 5.7, encontrado $$MYSQL_VERSION');
}
