#
# Main project file for building MIST MySQL Index Suggestion Tool
#

# Qt config
include(mist.pri)

TARGET = mist
TEMPLATE = app

# Source files
SOURCES += \
    src/main.cpp \
    src/core/embeddeddatabase.cpp \
    src/core/loghandler.cpp \
    src/ui/aboutdialog.cpp \
    src/ui/connectionlistwidget.cpp \
    src/ui/mainwindow.cpp \
    src/ui/createconnectiondialog.cpp \
    src/model/connectionmodel.cpp \
    src/entity/connection.cpp

HEADERS += \
    src/core/embeddeddatabase.h \
    src/core/loghandler.h \
    src/ui/aboutdialog.h \
    src/ui/connectionlistwidget.h \
    src/ui/mainwindow.h \
    src/ui/createconnectiondialog.h \
    src/model/connectionmodel.h \
    src/entity/connection.h

FORMS += \
    ui/aboutdialog.ui \
    ui/connectionlistwidget.ui \
    ui/mainwindow.ui \
    ui/createconnectiondialog.ui

RESOURCES += \
    res/paomedia-small-n-flat/iconset.qrc \
    res/mist.qrc

# Configure translations
TRANSLATIONS = \
    lang/pt_BR.ts

CODECFORTR = UTF8


# Deployment settings
target.path = $$BINDIR

lang.files = lang/*.qm
lang.path = $$LANGDIR

conf.files = conf/*
conf.path = $$CONFDIR

doc.files = README.md LICENSE
doc.path = $$DOCDIR

INSTALLS += target lang conf doc
