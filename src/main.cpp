#include <QApplication>
#include <QTranslator>

#include "ui/mainwizard.h"

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{time h:mm:ss.zzz t} %{type}: %{message}");

    QApplication app(argc, argv);

    app.setApplicationName("MIST");
    app.setApplicationDisplayName("MIST MySQL Index Suggestion Tool");
    app.setApplicationVersion("0.0.1");
    app.setOrganizationName("UNISC Universidade de Santa Cruz do Sul");
    app.setOrganizationDomain("unisc.br");

    QTranslator translator;
    QString locale = QLocale::system().name();

#ifdef QT_DEBUG
    translator.load(locale, app.applicationDirPath() + "/lang");
#else
    translator.load(locale, LANGDIR);
#endif
    app.installTranslator(&translator);

    MainWizard wizard;
    wizard.open();

    return app.exec();
}
