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
    src/core/abstractxmlreader.cpp \
    src/core/generatecandidateindexes.cpp \
    src/core/indexcolumnsbuilder.cpp \
    src/core/indexverification.cpp \
    src/core/querylogreader.cpp \
    src/core/schemadefinitionreader.cpp \
    src/core/solutionbuilder.cpp \
    src/entity/candidateindex.cpp \
    src/entity/filtercondition.cpp \
    src/entity/foreignkey.cpp \
    src/entity/foreignkeycolumn.cpp \
    src/entity/groupbyfield.cpp \
    src/entity/indexcolumn.cpp \
    src/entity/jointable.cpp \
    src/entity/mistproject.cpp \
    src/entity/orderbyfield.cpp \
    src/entity/query.cpp \
    src/entity/queryexplain.cpp \
    src/entity/queryexplainitem.cpp \
    src/entity/table.cpp \
    src/entity/tablecolumn.cpp \
    src/ui/aboutdialog.cpp \
    src/ui/candidateindexespage.cpp \
    src/ui/candidateslistwidget.cpp \
    src/ui/databaseconnectionpage.cpp \
    src/ui/fileopener.cpp \
    src/ui/indexverificationpage.cpp \
    src/ui/mainwizard.cpp \
    src/ui/querylistwidget.cpp \
    src/ui/querylogpage.cpp \
    src/ui/schemadefinitionpage.cpp \
    src/ui/solutionsummarypage.cpp \
    src/ui/tablelistwidget.cpp

HEADERS += \
    src/core/abstractxmlreader.h \
    src/core/generatecandidateindexes.h \
    src/core/indexcolumnsbuilder.h \
    src/core/indexverification.h \
    src/core/querylogreader.h \
    src/core/schemadefinitionreader.h \
    src/core/solutionbuilder.h \
    src/entity/candidateindex.h \
    src/entity/filtercondition.h \
    src/entity/foreignkey.h \
    src/entity/foreignkeycolumn.h \
    src/entity/groupbyfield.h \
    src/entity/indexcolumn.h \
    src/entity/jointable.h \
    src/entity/mistproject.h \
    src/entity/orderbyfield.h \
    src/entity/query.h \
    src/entity/queryexplain.h \
    src/entity/queryexplainitem.h \
    src/entity/table.h \
    src/entity/tablecolumn.h \
    src/ui/aboutdialog.h \
    src/ui/candidateindexespage.h \
    src/ui/candidateslistwidget.h \
    src/ui/databaseconnectionpage.h \
    src/ui/fileopener.h \
    src/ui/indexverificationpage.h \
    src/ui/mainwizard.h \
    src/ui/querylistwidget.h \
    src/ui/querylogpage.h \
    src/ui/schemadefinitionpage.h \
    src/ui/solutionsummarypage.h \
    src/ui/tablelistwidget.h

FORMS += \
    ui/aboutdialog.ui \
    ui/candidateindexespage.ui \
    ui/candidateslistwidget.ui \
    ui/databaseconnectionpage.ui \
    ui/indexverificationpage.ui \
    ui/mainwizard.ui \
    ui/querylistwidget.ui \
    ui/querylogpage.ui \
    ui/schemadefinitionpage.ui \
    ui/solutionsummarypage.ui \
    ui/tablelistwidget.ui

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

doc.files = README.md LICENSE examples/*
doc.path = $$DOCDIR

INSTALLS += target lang conf doc
