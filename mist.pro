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
    src/core/querylogreader.cpp \
    src/core/schemadefinitionreader.cpp \
    src/ui/aboutdialog.cpp \
    src/ui/connectionlistwidget.cpp \
    src/ui/mainwindow.cpp \
    src/ui/createconnectiondialog.cpp \
    src/model/connectionmodel.cpp \
    src/entity/connection.cpp \
    src/entity/filtercondition.cpp \
    src/entity/foreignkey.cpp \
    src/entity/foreignkeycolumn.cpp \
    src/entity/groupbyfield.cpp \
    src/entity/jointable.cpp \
    src/entity/orderbyfield.cpp \
    src/entity/query.cpp \
    src/entity/table.cpp \
    src/entity/tablecolumn.cpp

HEADERS += \
    src/core/embeddeddatabase.h \
    src/core/loghandler.h \
    src/core/querylogreader.h \
    src/core/schemadefinitionreader.h \
    src/ui/aboutdialog.h \
    src/ui/connectionlistwidget.h \
    src/ui/mainwindow.h \
    src/ui/createconnectiondialog.h \
    src/model/connectionmodel.h \
    src/entity/connection.h \
    src/entity/filtercondition.h \
    src/entity/foreignkey.h \
    src/entity/foreignkeycolumn.h \
    src/entity/groupbyfield.h \
    src/entity/jointable.h \
    src/entity/orderbyfield.h \
    src/entity/query.h \
    src/entity/table.h \
    src/entity/tablecolumn.h

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
