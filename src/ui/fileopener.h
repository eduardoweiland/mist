#ifndef FILEOPENER_H
#define FILEOPENER_H

#include <QFile>

#include "../core/abstractxmlreader.h"

class FileOpener
{
public:
    static bool selectFile(QWidget *parent, const QString &title, const QString &filter, QFile *file);
    static bool selectXmlFile(QWidget *parent, const QString &title, const QString &filter, AbstractXmlReader *parser);

private:
    FileOpener();
};

#endif // FILEOPENER_H
