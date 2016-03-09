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
    src/ui/aboutdialog.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    src/ui/aboutdialog.h \
    src/ui/mainwindow.h

FORMS += \
    ui/aboutdialog.ui \
    ui/mainwindow.ui

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
