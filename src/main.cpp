#include <QApplication>
#include <QTranslator>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("MIST");
    app.setApplicationDisplayName("MIST MySQL Index Suggestion Tool");
    app.setApplicationVersion("0.0.1");
    app.setOrganizationName("UNISC Universidade de Santa Cruz do Sul");
    app.setOrganizationDomain("unisc.br");

    QTranslator translator;
    QString locale = QLocale::system().name();
    translator.load(locale, LANGDIR);
    app.installTranslator(&translator);

    MainWindow win;
    win.show();

    return app.exec();
}
