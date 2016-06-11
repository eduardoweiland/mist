#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include "fileopener.h"

FileOpener::FileOpener()
{
}

bool FileOpener::selectFile(QWidget *parent, const QString &title, const QString &filter, QFile *file)
{
    static QString lastDirectory = QDir::homePath();

    QString filename = QFileDialog::getOpenFileName(parent, title, lastDirectory, filter);

    if (filename.isNull()) {
        // No file selected
        return false;
    }

    qInfo() << QObject::tr("Selected file: %1").arg(filename);

    file->setFileName(filename);
    if (!file->open(QFile::ReadOnly | QFile::Text)) {
        qCritical() << QObject::tr("Error opening selected file %1").arg(filename);

        QMessageBox::critical(
            parent,
            QObject::tr("Error opening file"),
            QObject::tr("There was an error opening the selected schema definition file. "
               "Check if you have permissions to read it.")
        );

        return false;
    }

    lastDirectory = QFileInfo(*file).absolutePath();

    return true;
}

bool FileOpener::selectXmlFile(QWidget *parent, const QString &title, const QString &filter, AbstractXmlReader *parser)
{
    QFile file;
    if (!selectFile(parent, title, filter, &file)) {
        return false;
    }

    if (!parser->parse(&file)) {
        qCritical() << QObject::tr("Error parsing selected file %1: %2")
                       .arg(file.fileName())
                       .arg(parser->getError());

        QMessageBox::critical(
            parent,
            QObject::tr("Error opening file"),
            QObject::tr("There was an error parsing the selected file:\n%1").arg(parser->getError())
        );

        return false;
    }

    return true;
}
